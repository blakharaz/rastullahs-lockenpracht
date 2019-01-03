#include "CeGuiLogForwarder.h"

#include "Logger.h"

namespace rl
{
    namespace
    {
        rl::Logger::LogLevel get_rl_log_level(const CEGUI::LoggingLevel cegui_level)
        {
            switch (cegui_level)
            {
            case CEGUI::LoggingLevel::Errors:
                return rl::Logger::LogLevel::LL_ERROR;
            case CEGUI::LoggingLevel::Warnings:
                return rl::Logger::LogLevel::LL_WARNING;
            case CEGUI::LoggingLevel::Standard:
                return rl::Logger::LogLevel::LL_MESSAGE;
            case CEGUI::LoggingLevel::Informative:
                return rl::Logger::LogLevel::LL_DEBUG;
            case CEGUI::LoggingLevel::Insane:
                return rl::Logger::LogLevel::LL_DEBUG;
            }

            return rl::Logger::LogLevel::LL_DEBUG;
        }
    }

    CeGuiLogForwarder::CeGuiLogForwarder(rl::Logger& logger)
        : mRlLogger(logger)
    {
    }

    void CeGuiLogForwarder::logEvent(const CEGUI::String& message, CEGUI::LoggingLevel level)
    {
        mRlLogger.log(get_rl_log_level(level), rl::Logger::UI, message);
    }

    void CeGuiLogForwarder::setLogFilename(const CEGUI::String& /*filename*/, bool /*append*/)
    {
        // uses RL log, so no filename to set
    }
}
