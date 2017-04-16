// Copyright (c) 2013, Jan Winkler <winkler@cs.uni-bremen.de>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Universität Bremen nor the names of its
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include "CCrazyflie.h"
#include <chrono>
#include "math/clock_gettime.h"

CCrazyflie::CCrazyflie(CCrazyRadio* crazyRadio)
{
  _crazyRadio = crazyRadio;
  
  // Review these values
  _maxAbsRoll = 45.0f;
  _maxAbsPitch = _maxAbsRoll;
  _maxYaw = 180.0f;
  _maxThrust = 60000;
  _minThrust = 0;//15000;

  _roll = 0;
  _pitch = 0;
  _yaw = 0;
  _thrust = 0;
  
  _sendsSetpoints = false;
  
  _tocParameters = new CTOC(_crazyRadio, 2);
  _tocLogs = new CTOC(_crazyRadio, 5);
  
  _state = STATE_ZERO;
  
  _sendSetpointPeriod = 0.01; // Seconds
  _setpointLastSent = 0;
}

CCrazyflie::~CCrazyflie()
{
  StopLogging();
}

bool CCrazyflie::ReadTOCParameters()
{
    if(_tocParameters->requestMetaData() )
    {
        if(_tocParameters->requestItems())
        {
            return true;
        }
    }

    return false;
}

bool CCrazyflie::ReadTOCLogs()
{
    if(_tocLogs->requestMetaData())
    {
        if(_tocLogs->requestItems())
        {
            return true;
        }
    }

    return false;
}

bool CCrazyflie::SendSetpoint(float roll, float pitch, float yaw, short thrust) {
    pitch = -pitch;

    int nSize = 3 * sizeof(float) + sizeof(short);
    char cBuffer[nSize];
    memcpy(&cBuffer[0 * sizeof(float)], &roll, sizeof(float));
    memcpy(&cBuffer[1 * sizeof(float)], &pitch, sizeof(float));
    memcpy(&cBuffer[2 * sizeof(float)], &yaw, sizeof(float));
    memcpy(&cBuffer[3 * sizeof(float)], &thrust, sizeof(short));

    CCRTPPacket *crtpPacket = new CCRTPPacket(cBuffer, nSize, 3);
    CCRTPPacket *crtpReceived = _crazyRadio->sendPacket(crtpPacket);

    delete crtpPacket;
    if(crtpReceived != NULL)
    {
        delete crtpReceived;
        return true;
    }
    else
    {
        return false;
    }
}

void CCrazyflie::SetThrust(int thrust) {
  _thrust = thrust;
  
  if(_thrust < _minThrust)
  {
    _thrust = _minThrust;
  }
  else if(_thrust > _maxThrust)
  {
    _thrust = _maxThrust;
  }
}

int CCrazyflie::GetThrust()
{
  return this->GetSensorValue("stabilizer.thrust");
}

bool CCrazyflie::Update()
{
  double dTimeNow = this->GetCurrentTime();
  
  switch(_state)
  {
  case STATE_ZERO:
  {
      _state = STATE_READ_PARAMETERS_TOC;
  } break;
    
  case STATE_READ_PARAMETERS_TOC:
  {
    if(this->ReadTOCParameters())
    {
      _state = STATE_READ_LOGS_TOC;
    }
  } break;
    
  case STATE_READ_LOGS_TOC:
  {
    if(this->ReadTOCLogs())
    {
      _state = STATE_START_LOGGING;
    }
  } break;
    
  case STATE_START_LOGGING:
  {
    if(this->StartLogging())
    {
      _state = STATE_ZERO_MEASUREMENTS;
    }
  } break;
    
  case STATE_ZERO_MEASUREMENTS:
  {
    _tocLogs->processPackets(_crazyRadio->popLoggingPackets());
    
    // NOTE(winkler): Here, we can do measurement zero'ing. This is
    // not done at the moment, though. Reason: No readings to zero at
    // the moment. This might change when altitude becomes available.
    
    _state = STATE_NORMAL_OPERATION;
  } break;
    
  case STATE_NORMAL_OPERATION:
  {
    // Shove over the sensor readings from the radio to the Logs TOC.
    _tocLogs->processPackets(_crazyRadio->popLoggingPackets());
    
    if(_sendsSetpoints)
    {
      // Check if it's time to send the setpoint
      if(dTimeNow - _setpointLastSent > _sendSetpointPeriod)
      {
	// Send the current set point based on the previous calculations
    this->SendSetpoint(_roll, _pitch, _yaw, _thrust);
    _setpointLastSent = dTimeNow;
      }
    }
    else
    {
      // Send a dummy packet for keepalive
      _crazyRadio->sendDummyPacket();
    }
  } break;
    
  default:
  {
  } break;
  }
  
  if(_crazyRadio->ackReceived())
  {
    _ackMissCounter = 0;
  }
  else
  {
    _ackMissCounter++;
  }
  
  return _crazyRadio->usbOK();
}

bool CCrazyflie::IsCopterConnected()
{
  return _ackMissCounter < _ackMissTolerance;
}

void CCrazyflie::SetRoll(float roll)
{
  _roll = roll;
  
  if(std::fabs(_roll) > _maxAbsRoll)
  {
    _roll = copysign(_maxAbsRoll, _roll);
  }
}

float CCrazyflie::GetRoll()
{
  return this->GetSensorValue("stabilizer.roll");
}

void CCrazyflie::SetPitch(float fPitch)
{
  _pitch = fPitch;
  
  if(std::fabs(_pitch) > _maxAbsPitch)
  {
    _pitch = copysign(_maxAbsPitch, _pitch);
  }
}

float CCrazyflie::GetPitch()
{
  return this->GetSensorValue("stabilizer.pitch");
}

void CCrazyflie::SetYaw(float yaw)
{
  _yaw = yaw;

  if(std::fabs(_yaw) > _maxYaw){
      _yaw = copysign(_maxYaw, _yaw);
  }
}

float CCrazyflie::GetYaw()
{
  return this->GetSensorValue("stabilizer.yaw");
}

double CCrazyflie::GetCurrentTime()
{
  struct timespec tsTime;
  clock_gettime(&tsTime);
  
  return tsTime.tv_sec + double(tsTime.tv_nsec) / NSEC_PER_SEC;
}

bool CCrazyflie::IsInitialized()
{
  return _state == STATE_NORMAL_OPERATION;
}

bool CCrazyflie::StartLogging()
{
  // Register the desired sensor readings
  this->EnableStabilizerLogging();
  this->EnableGyroscopeLogging();
  this->EnableAccelerometerLogging();
  this->EnableBatteryLogging();
  this->EnableMagnetometerLogging();
  this->EnableAltimeterLogging();
  
  return true;
}

bool CCrazyflie::StopLogging()
{
  this->DisableStabilizerLogging();
  this->DisableGyroscopeLogging();
  this->DisableAccelerometerLogging();
  this->DisableBatteryLogging();
  this->DisableMagnetometerLogging();
  this->DisableAltimeterLogging();
  
  return true;
}

void CCrazyflie::SetSendSetpoints(bool bSendSetpoints)
{
  _sendsSetpoints = bSendSetpoints;
}

bool CCrazyflie::IsSendingSetpoints()
{
  return _sendsSetpoints;
}

double CCrazyflie::GetSensorValue(std::string strName)
{
  return _tocLogs->doubleValue(strName);
}

void CCrazyflie::DisableLogging()
{
  _tocLogs->unregisterLoggingBlock("high-speed");
  _tocLogs->unregisterLoggingBlock("low-speed");
}

void CCrazyflie::EnableStabilizerLogging()
{
  _tocLogs->registerLoggingBlock("stabilizer", 1000);
  
  _tocLogs->startLogging("stabilizer.roll", "stabilizer");
  _tocLogs->startLogging("stabilizer.pitch", "stabilizer");
  _tocLogs->startLogging("stabilizer.yaw", "stabilizer");
}

void CCrazyflie::EnableGyroscopeLogging()
{
  _tocLogs->registerLoggingBlock("gyroscope", 1000);

  _tocLogs->startLogging("gyro.x", "gyroscope");
  _tocLogs->startLogging("gyro.y", "gyroscope");
  _tocLogs->startLogging("gyro.z", "gyroscope");
}

float CCrazyflie::GyroX()
{
  return this->GetSensorValue("gyro.x");
}

float CCrazyflie::GyroY() {
  return this->GetSensorValue("gyro.y");
}

float CCrazyflie::GyroZ() {
  return this->GetSensorValue("gyro.z");
}

void CCrazyflie::EnableAccelerometerLogging()
{
  _tocLogs->registerLoggingBlock("accelerometer", 1000);

  _tocLogs->startLogging("acc.x", "accelerometer");
  _tocLogs->startLogging("acc.y", "accelerometer");
  _tocLogs->startLogging("acc.z", "accelerometer");
  _tocLogs->startLogging("acc.zw", "accelerometer");
}

float CCrazyflie::AccX()
{
  return this->GetSensorValue("acc.x");
}

float CCrazyflie::AccY()
{
  return this->GetSensorValue("acc.y");
}

float CCrazyflie::AccZ()
{
  return this->GetSensorValue("acc.z");
}

float CCrazyflie::AccZW()
{
  return this->GetSensorValue("acc.zw");
}

void CCrazyflie::DisableStabilizerLogging()
{
  _tocLogs->unregisterLoggingBlock("stabilizer");
}

void CCrazyflie::DisableGyroscopeLogging()
{
  _tocLogs->unregisterLoggingBlock("gyroscope");
}

void CCrazyflie::DisableAccelerometerLogging()
{
  _tocLogs->unregisterLoggingBlock("accelerometer");
}

void CCrazyflie::EnableBatteryLogging()
{
  _tocLogs->registerLoggingBlock("battery", 1000);

  _tocLogs->startLogging("pm.vbat", "battery");
  _tocLogs->startLogging("pm.state", "battery");
}

double CCrazyflie::GetBatteryLevel()
{
  return this->GetSensorValue("pm.vbat");
}

float CCrazyflie::GetBatteryState()
{
  return this->GetSensorValue("pm.state");
}

void CCrazyflie::DisableBatteryLogging()
{
  _tocLogs->unregisterLoggingBlock("battery");
}

void CCrazyflie::EnableMagnetometerLogging()
{
  _tocLogs->registerLoggingBlock("magnetometer", 1000);

  _tocLogs->startLogging("mag.x", "magnetometer");
  _tocLogs->startLogging("mag.y", "magnetometer");
  _tocLogs->startLogging("mag.z", "magnetometer");
}
float CCrazyflie::MagX()
{
  return this->GetSensorValue("mag.x");
}
float CCrazyflie::MagY()
{
  return this->GetSensorValue("mag.y");
}
float CCrazyflie::MagZ()
{
  return this->GetSensorValue("mag.z");
}
void CCrazyflie::DisableMagnetometerLogging()
{
  _tocLogs->unregisterLoggingBlock("magnetometer");
}

void CCrazyflie::EnableAltimeterLogging()
{
  _tocLogs->registerLoggingBlock("altimeter", 1000);
  _tocLogs->startLogging("alti.asl", "altimeter");
  _tocLogs->startLogging("alti.aslLong", "altimeter");
  _tocLogs->startLogging("alti.pressure", "altimeter");
  _tocLogs->startLogging("alti.temperature", "altimeter");
}

float CCrazyflie::Asl()
{
  return this->GetSensorValue("alti.asl");
}
float CCrazyflie::AslLong()
{
  return this->GetSensorValue("alti.aslLong");
}
float CCrazyflie::Pressure()
{
  return this->GetSensorValue("alti.pressure");
}
float CCrazyflie::Temperature()
{
  return this->GetSensorValue("alti.temperature");
}

void CCrazyflie::DisableAltimeterLogging()
{
  _tocLogs->unregisterLoggingBlock("altimeter");
}
