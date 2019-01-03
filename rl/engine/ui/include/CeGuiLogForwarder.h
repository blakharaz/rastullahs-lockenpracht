#pragma once

#include <CEGUI/Logger.h>

namespace rl
{
    class Logger;

    class CeGuiLogForwarder : public CEGUI::Logger
    {
    public:
        CeGuiLogForwarder(rl::Logger& logger);

        void logEvent(const CEGUI::String& message, CEGUI::LoggingLevel level) override;
        void setLogFilename(const CEGUI::String& filename, bool append) override;

    private:
        rl::Logger& mRlLogger;
    };
}
