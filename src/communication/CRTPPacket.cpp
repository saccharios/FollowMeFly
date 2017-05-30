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


#include "CRTPPacket.h"
#include "assert.h"
#include <vector>
#include <iostream>


CRTPPacket:: CRTPPacket(Port port, Channel channel, std::vector<char> && data) :
    _data (data),
    _port (port),
    _channel(channel)
{}

std::vector<char> const & CRTPPacket::GetData() const
{
    return _data;
}

unsigned char * CRTPPacket::SendableData() const
{
    unsigned char* sendable = new unsigned char[GetSendableDataLength()]();

    // Header byte
    sendable[0] = (static_cast<int>(_port) << 4) | 0b00001100 | (static_cast<int>(_channel) & 0x03);

    // Payload
    for(std::size_t i = 0; i < _data.size(); ++i)
    {
        sendable[i+1] = _data[i];
    }
    // Finishing byte
    //sendable[_dataLength + 1] = 0x27;

    return sendable;
}

int CRTPPacket::GetSendableDataLength() const
{
    return _data.size() + 1;//2;
}

Port CRTPPacket::GetPort() const
{
    return _port;
}

Channel CRTPPacket::GetChannel() const
{
    return _channel;
}







