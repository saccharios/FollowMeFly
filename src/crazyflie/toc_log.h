#pragma once
#include "crtp_packet.h"
#include "math/types.h"
#include "radio_dongle.h"
#include "toc_shared.h"
#include "protocol.h"
#include <QObject>
class TocLog : public QObject
{
    Q_OBJECT;

    friend class TOC_Log_Test; // Is friend for white-box testing.

    struct LoggingBlock
    {
        enum class State
        {
            idle = 0,
            isCreated = 1,
            hasElements = 2,
            isEnabled = 3,
        };
        std::string name;
        float frequency;
        std::vector<TOCElement*> elements; // Has no ownership over TocLogElements.
        State state = State::idle;
        uint8_t id;
        std::vector<std::string> elements_to_add;
    };

    enum class AppendState
    {
        IDLE = 0,
        REQUEST_ITEM = 1,
        WAIT_ANSWER = 2,
        PREPARE_NEXT = 3,
        DONE = 4
    };

public:
    TocLog(RadioDongle & radioDongle);

    bool Setup() {return _shared_impl.Setup();}

    void ResetLoggingBlocks();
    bool CreateLoggingBlocks();
    void AppendLoggingBlocks();

    bool EnableLogging();
//    void DisableLogging();

    float Value(std::string name);

    std::vector<TOCElement> const & GetElements() const {return _tocElements;}
    bool AppendingBlocksIsDone() {return (_appendingState == AppendState::DONE);}

public slots:
    void ReceivePacket(CRTPPacket packet);

private:
    void EnableLogging(LoggingBlock  & block);
//    void DisableLogging(LoggingBlock const & block);

    RadioDongle & _radioDongle;
    unsigned int _itemCount;
    std::vector<TOCElement> _tocElements; // Contains all elements
    static constexpr unsigned int _numLogBlocks = 16u;
    static constexpr float _frequency = 100.0f; // Max frequency is 100.0 Hz
    std::array<LoggingBlock, _numLogBlocks> _loggingBlocks; // Contains logging blocks which hold pointers to elements of _tocElements.
    TOCShared<Logger::id, Logger::Access> _shared_impl;

    uint32_t  _currentAppendingBlock;
    uint32_t  _currentAppendingElement;
    TOCElement* _elementToAdd;
    AppendState _appendingState = AppendState::IDLE;

    void ProcessControlData(Data const & data);
    void ProcessLoggerData(Data const & data);
    void CreateLoggingBlock(LoggingBlock const & block);
    bool AppendElements(LoggingBlock & block);

};