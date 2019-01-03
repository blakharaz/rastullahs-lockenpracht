/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2008 Team Pantheon. http://www.team-pantheon.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Clarified Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Clarified Artistic License for more details.
 *
 *  You should have received a copy of the Clarified Artistic License
 *  along with this program; if not you can get it here
 *  http://www.jpaulmorrison.com/fbp/artistic2.htm.
 */

#include <errno.h>
#include <memory>
#include <stdexcept>

#include "AiSubsystem.h"
#include "CoreSubsystem.h"
#include "GameLoop.h"
#include "RulesSubsystem.h"
#include "ScriptSubsystem.h"
#include "UiSubsystem.h"

#include "ConfigurationManager.h"
#include "Exception.h"
#include "Logger.h"
#include <CEGUI/Exceptions.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <shellapi.h>
#include <windows.h>
#endif

void startupRl(bool developerMode, const Ogre::String& module, const Ogre::String& executable)
{
    std::unique_ptr<rl::CoreSubsystem> core;
    std::unique_ptr<rl::RulesSubsystem> rules;
    std::unique_ptr<rl::AiSubsystem> ai;
    std::unique_ptr<rl::UiSubsystem> ui;
    std::unique_ptr<rl::ScriptSubsystem> script;
    std::unique_ptr<rl::Logger> logger;
    std::unique_ptr<rl::ConfigurationManager> configurationManager;

#ifndef _DEBUG
    try
    {
#endif // #ifndef _DEBUG
        configurationManager = std::make_unique<rl::ConfigurationManager>();

        configurationManager->setExecutable(executable);
        configurationManager->loadConfig();

        Ogre::String logDir = configurationManager->getRastullahLogDirectory();
        Ogre::String ogreLogFile = configurationManager->getOgreLogFile();
        Ogre::String rlLogFile = configurationManager->getRastullahLogFile();

        logger = std::make_unique<rl::Logger>(logDir, ogreLogFile, rlLogFile);
        // @todo in ConfigDatei auslagern/ oder auch Parameter

        rl::Logger::getSingleton().setLogDetail(configurationManager->getLogLevel());

        configurationManager->loadModulesConfig();

        core = std::make_unique<rl::CoreSubsystem>();
        core->setDeveloperMode(developerMode);
        LOG_MESSAGE_SHORT("CoreSubsystem gestartet");

        rules = std::make_unique<rl::RulesSubsystem>();
        LOG_MESSAGE_SHORT("RulesSubsystem gestartet");

        ai = std::make_unique<rl::AiSubsystem>();
        LOG_MESSAGE_SHORT("AiSubsystem gestartet");

        ui = std::make_unique<rl::UiSubsystem>();
        LOG_MESSAGE_SHORT("UiSubsystem gestartet");

        script = std::make_unique<rl::ScriptSubsystem>();
        LOG_MESSAGE_SHORT("ScriptSubsystem gestartet");

        LOG_MESSAGE_SHORT("Starte...");
        if (module != "")
            core->setDefaultActiveModule(module);

        core->startCore();

#ifndef _DEBUG
    }
    catch (Ogre::Exception& oe)
    {
        rl::showError(oe.getFullDescription());
    }
    catch (rl::Exception& re)
    {
        rl::showError(re.what());
    }
    catch (CEGUI::Exception& ce)
    {
        rl::showError(ce.getMessage().c_str());
    }
    catch (fs::filesystem_error& fe)
    {
        rl::showError(fe.what());
    }
    catch (std::runtime_error& rte)
    {
        rl::showError(rte.what());
    }
    catch (std::exception& exp)
    {
        rl::showError(exp.what());
    }
    catch (std::string& err)
    {
        rl::showError(err);
    }
    catch (...)
    {
        rl::showError("Unknown exception occured");
    }

    try
    {
#endif // #ifndef _DEBUG
       // Save the configuration to disk
        configurationManager->saveConfig();
        LOG_MESSAGE_SHORT("Configuration file saved");
#ifndef _DEBUG
    }
    catch (Ogre::Exception& oe)
    {
        rl::showError(oe.getFullDescription());
    }
    catch (rl::Exception& re)
    {
        rl::showError(re.what());
    }
    catch (std::runtime_error& rte)
    {
        rl::showError(rte.what());
    }
    catch (std::exception& exp)
    {
        rl::showError(exp.what());
    }
    catch (std::string& err)
    {
        rl::showError(err);
    }
    catch (...)
    {
        rl::showError("Unknown exception occured");
    }
#endif //#ifndef _DEBUG
}

void analyzeParameters(int argc, char** argv, bool& developerMode, Ogre::String& startModule, Ogre::String& executable)
{
    developerMode = false;
    startModule = "";
    executable = argv[0];

    for (int argIdx = 1; argIdx < argc; argIdx++)
    {
        if (strncmp(argv[argIdx], "--dev", 5) == 0)
            developerMode = true;
        else if (strncmp(argv[argIdx], "--module", 8) == 0 && argc > argIdx + 1) // Naechster Parameter existiert
            startModule = argv[argIdx + 1];
    }
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    int argc;
    LPWSTR* argList = CommandLineToArgvW(GetCommandLineW(), &argc);
    char** argv = new char*[argc];
    for (int argIdx = 0; argIdx < argc; argIdx++)
    {
        size_t len = wcslen(argList[argIdx]) + 1;
        argv[argIdx] = new char[len];
        wcstombs(argv[argIdx], argList[argIdx], len);
        argv[argIdx][len - 1] = '\0';
    }

    bool developer;
    Ogre::String module;
    Ogre::String executable;
    analyzeParameters(argc, argv, developer, module, executable);

    for (int argIdx = 0; argIdx < argc; argIdx++)
    {
        delete[] argv[argIdx];
    }
    delete[] argv;
    LocalFree(argList);

    startupRl(developer, module, executable);

    return 0;
}

#else // if OGRE_PLATFORM != OGRE_PLATFORM_WIN32

int main(int argc, char** argv)
{
    bool developer;
    Ogre::String module;
    Ogre::String executable;

    analyzeParameters(argc, argv, developer, module, executable);
    startupRl(developer, module, executable);

    return 0;
}

#endif