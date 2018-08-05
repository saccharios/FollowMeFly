
// With the newest firmware for the crazyflie 2.0, the motor need to be unlocked by sending a "thrust = 0" command
// Update SF: I disabled the locking-functionality in the firmware.

#pragma once

#include "QOBJECT"

#include <cmath>
#include "radio_dongle.h"
#include <memory>
#include "math/logic.h"
#include "math/types.h"
#include "toc_log.h"
#include "toc_parameter.h"
#include "text_logger.h"

enum class State
{
    ZERO = 0,
    SETUP_PARAMETERS = 1,
    READ_PARAMETERS = 2,
    SETUP_LOGGER = 3,
    CREATE_LOGGERS = 4,
    APPEND_LOGGERS = 5,
    START_LOGGERS = 6,
    SET_PARAMETERS = 7,
    NORMAL_OPERATION = 8
};

struct SetPoint
{
    float roll;
    float pitch;
    float yaw;
    uint16_t thrust;
    void Print()
    {
        textLogger << "roll = " << roll << " pitch = " << pitch << " yaw = " << yaw << " thrust = " << thrust << "\n";
    }
};

struct Barometer
{
    float asl;
    float aslLong;
    float temperature;
    float pressure;
};

struct Accelerometer
{
    float x;
    float y;
    float z;
    float zw;
};

struct Gyrometer
{
    float x;
    float y;
    float z;
};
struct Battery
{
    double  level;
    float   state;
};

struct Magnetometer
{
    float x;
    float y;
    float z;
};

struct SensorValues
{
    SetPoint stabilizer;
    Barometer barometer;
    Accelerometer acceleration;
    Gyrometer gyrometer;
    Battery battery;
    Magnetometer magnetometer;
};

class Crazyflie : public QObject
{
    Q_OBJECT

public:


    Crazyflie(RadioDongle & _radioDongle);
    ~Crazyflie();

    void SetThrust(int thrust);
    void SetRoll(float roll); // In degree, -180° to 180°
    void SetPitch(float pitch); // In degree, -180° to 180°
    void SetYaw(float yaw); // In degree, -180° to 180°

    void SetSetPoint(SetPoint setPoint);
    void SetSendSetpoints(bool sendSetpoints);
    bool IsSendingSetpoints();

    void SetVelocityCrazyFlieRef(Velocity velocity);
    void SetVelocityWorldRef(Velocity velocity);
    void SetSendingVelocityRef(bool isSendingVelocityRef);
    bool IsSendingVelocityRef();

    void Stop();
    void SendHover(float vx, float vy, float yawrate, float zDistance);

    SensorValues const & GetSensorValues() const {return _sensorValues;}

    void StartConnecting(bool enable);
    void Update();

    bool IsDisconnected();
    bool IsConnecting();
    bool IsConnected();

    Eigen::Vector3f ConvertBodyFrameToIntertialFrame(Eigen::Vector3f const & value_in_body);

    TocLog const & GetLoggerTOC() const {return _logger;}
    TocLog & GetLoggerTOC() {return _logger; }
    TocParameter const & GetParameterTOC() const {return _parameters; }
    TocParameter & GetParameterTOC() {return _parameters;}

    void ResetCrazyflieKalmanFilter(bool enable);


signals:
    void ConnectionTimeout();
    void NotConnecting();

private:
    RadioDongle & _radioDongle;

    int _ackMissTolerance;
    int _ackMissCounter;

    SetPoint _sendSetPoint;
    SetPoint _maxSetPoint;

    Velocity _velocity = {0.0, 0.0, 0.0};

    int _minThrust;

    bool _isSendingSetpoints;
    bool _isSendingVelocityRef;

    bool _startConnecting;
    State _state;

    TocParameter _parameters;
    TocLog _logger;

    Negative_Edge_Detector _leaveConnectingState;

    SensorValues _sensorValues;

    void SendSetpoint(SetPoint setPoint);
    void SendVelocityRef(Velocity velocity);

    void UpateSensorValues();
    float GetSensorValue(std::string name);
};

