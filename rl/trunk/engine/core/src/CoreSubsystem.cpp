/* This source file is part of Rastullahs Lockenpracht.
* Copyright (C) 2003-2007 Team Pantheon. http://www.team-pantheon.de
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

#include "XmlResourceManager.h"

#include "CoreSubsystem.h"

#include <OgreStringConverter.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreMeshManager.h>
#include <OgreBillboardParticleRenderer.h>
#include <OgreEnvironment.h>

#include "ActorManager.h"
#include "AnimationManager.h"
#include "ContentModule.h"
#include "ConfigurationManager.h"
#include "CoreEvents.h"
#include "DotSceneOctreeWorld.h"
#include "Exception.h"
#include "GameEventManager.h"
#include "GameLoop.h"
#include "ZoneManager.h"
#include "Logger.h"
#include "PhysicsManager.h"
#include "RubyInterpreter.h"
#include "ScriptWrapper.h"
#include "SoundManager.h"
#include "DebugVisualsManager.h"
#include "JobScheduler.h"

#include <ctime>

using namespace Ogre;

template<> rl::CoreSubsystem* Singleton<rl::CoreSubsystem>::ms_Singleton = 0;

namespace rl
{
    CoreSubsystem::CoreSubsystem()
        : Singleton<CoreSubsystem>(),
        mWorld(NULL),
        mRubyInterpreter(NULL),
        mModules(),
        mActiveAdventureModule(NULL),
        mDefaultActiveModule(""),
        mClockStartTime(),
        mDeveloperMode(false),
        mInitialized(false),
        mCoreEventCaster(),
        mDefaultTechniques(),
        mOgreRoot(NULL),
        mScriptWrapper(NULL),
        mXmlResourceManager(NULL),
        mPhysicsManager(NULL),
        mGameLoop(NULL),
        mAnimationManager(NULL),
        mActorManager(NULL),
        mGameEventManager(NULL),
        mSoundManager(NULL),
        mDebugVisualsManager(NULL),
        mJobScheduler(NULL),
        mRenderWindow(NULL),
		mZoneManager(NULL)
    {
        initializeCoreSubsystem();
    }

    CoreSubsystem::~CoreSubsystem()
    {
        mCoreEventCaster.removeEventListeners();

		delete meshmagick::OgreEnvironment::getSingletonPtr();
        delete mZoneManager;
        delete mGameEventManager;
		delete mWorld;
        delete mGameLoop;
        delete mJobScheduler;
        delete mAnimationManager;
        delete mActorManager;
        delete mPhysicsManager;
        delete mXmlResourceManager;
        delete mScriptWrapper;
        delete mDebugVisualsManager;
		delete ConfigurationManager::getSingletonPtr();
        delete mSoundManager;
        delete mOgreRoot;
        delete mRubyInterpreter;
    }

    void CoreSubsystem::startCore()
    {
        loadPlugins();

        mInitialized = true;

        if (mDefaultActiveModule == "")
        {
            mDefaultActiveModule = "intro"; ///@fixme replace by last active
        }


        ContentModule* mod = getModule(mDefaultActiveModule);
        if (mod == NULL)
        {
            Throw(rl::RuntimeException, "Module "+mDefaultActiveModule+" not found");
        }
        else
        {
            startAdventureModule(mod);
        }

        mGameLoop->loop();

        mWorld->clearScene();
        unloadPlugins();

        //mRubyInterpreter->finalizeInterpreter();
    }

    void CoreSubsystem::renderOneFrame()
    {
        mGameLoop->_executeOneRenderLoop();
    }

    void CoreSubsystem::setDeveloperMode(bool developerMode)
    {
        mDeveloperMode = developerMode;
    }

    bool CoreSubsystem::getDeveloperMode() const
    {
        return mDeveloperMode;
    }

    bool CoreSubsystem::isInitialized() const
    {
        return mInitialized;
    }

    Ogre::RenderWindow* CoreSubsystem::getRenderWindow()
    {
        return mRenderWindow;
    }

	void CoreSubsystem::setPaused(bool paused)
	{
		mGameLoop->setPaused(paused);
	}

    bool CoreSubsystem::initializeCoreSubsystem()
    {
        // By not specifying the first two parameters, OGRE will not try
        // to load plugins.cfg and ogre.cfg
        mOgreRoot = new Root("", "", ConfigurationManager::getSingleton().getOgreLogFile());

        // Load Ogre plugins
        Ogre::StringVector pluginList = ConfigurationManager::getSingleton().getPluginList();

        ///\todo In Windows Ogre now uses a _d suffix for debug plugins. But client application is
        /// responsible for loading the proper vesion. This way to do it is kinda ugly.
        /// We should somehow handle this in the ConfigurationManager.
        Ogre::String pluginSuffix = "";
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#ifdef _DEBUG
        pluginSuffix = "_d";
#endif
#endif

        for (Ogre::StringVector::const_iterator it = pluginList.begin(); it < pluginList.end(); it++)
        {
            mOgreRoot->loadPlugin(*it + pluginSuffix);
        }

        // Find out, what Renderer plugins are available
        RenderSystemList* rsl = mOgreRoot->getAvailableRenderers();
        RenderSystemList::iterator it;

        for (it = rsl->begin(); it < rsl->end(); it++)
        {
            if ((*it)->getName() == ConfigurationManager::getSingleton().getStringSetting(
                "Video", "Render System"))
            {
                // Select and initialise the render system
                mOgreRoot->setRenderSystem(*it);
                mOgreRoot->initialise(false, "");
            }
        }

        //Root::getSingleton().setFrameSmoothingPeriod(0.5f);

        // Muss vor dem Laden der Ressourcen geschehen,
        // weil es sonst sofort angewandt wird.
        MeshManager::getSingleton().setBoundsPaddingFactor(0.0);

        // EDIT:
        LOG_MESSAGE(Logger::CORE,"init");

        std::stringstream name;
        name << "Rastullahs Lockenpracht - ";
        name << getEngineVersionString() << " ";
        name << getEngineVersionName() << " [";
        name << getEngineBuildNumber() << "]";

        // Get width and height of the RenderWindow from the "Video Mode" setting
        Ogre::String VideoMode = ConfigurationManager::getSingleton().getStringSetting(
            "Video", "Video Mode");
        int temp = VideoMode.find("x");
        int width = Ogre::StringConverter::parseInt(VideoMode.substr(0, temp));
        int height = Ogre::StringConverter::parseInt(VideoMode.substr(temp + 1, VideoMode.size()));

        mRenderWindow = mOgreRoot->createRenderWindow(name.str(), width, height,
            ConfigurationManager::getSingleton().getBoolSetting(
                "Video", "Fullscreen"),
                    &ConfigurationManager::getSingleton().getSettings("Video"));

        if (!mRenderWindow)
            return false;

        mGameLoop = new GameLoop();
        LOG_MESSAGE(Logger::CORE,"GameLoopmanager erzeugt");

        mScriptWrapper = new ScriptWrapper();
        LOG_MESSAGE(Logger::CORE,"Skriptwrapper erzeugt");
        // TODO: muss l�schbar werden.
        mRubyInterpreter = new RubyInterpreter();
        LOG_MESSAGE(Logger::CORE,"RubyInterpreter erzeugt");
        mRubyInterpreter->initializeInterpreter();
        LOG_MESSAGE(Logger::CORE,"RubyInterpreter initialisiert");

        mActorManager = new ActorManager();
        LOG_MESSAGE(Logger::CORE,"Aktormanager erzeugt");

        mSoundManager = new SoundManager();
        GameLoop::getSingleton().addTask(mSoundManager, GameLoop::TG_SOUND);
        LOG_MESSAGE(Logger::CORE,"SoundManager erzeugt");

        initializeResources();

        // Set default mipmap level (NB some APIs ignore this)
        //TODO: In Config-Datei verlagern
        TextureManager::getSingleton().setDefaultNumMipmaps(5);
        MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_TRILINEAR);
        MaterialManager::getSingleton().setDefaultAnisotropy(
            ConfigurationManager::getSingleton().getIntSetting(
                "Video", "Max Anisotropy"));


        mWorld = new DotSceneOctreeWorld();
        mActorManager->setWorld(mWorld);

        mPhysicsManager = new PhysicsManager();
        GameLoop::getSingleton().addTask(mPhysicsManager, GameLoop::TG_PHYSICS);
        LOG_MESSAGE(Logger::CORE,"PhysicsManager erzeugt");

        mAnimationManager = new AnimationManager();
        GameLoop::getSingleton().addTask(mAnimationManager, GameLoop::TG_GRAPHICS);
        LOG_MESSAGE(Logger::CORE,"AnimationManager erzeugt");

        mGameEventManager = new GameEventManager();
        GameLoop::getSingleton().addTask(mGameEventManager, GameLoop::TG_LOGIC);
        LOG_MESSAGE(Logger::CORE,"GameEventManager erzeugt");

        mDebugVisualsManager = new DebugVisualsManager();
        GameLoop::getSingleton().addTask(mDebugVisualsManager, GameLoop::TG_GRAPHICS);
        LOG_MESSAGE(Logger::CORE,"DebugVisualsManager erzeugt");

        mJobScheduler = new JobScheduler();
        GameLoop::getSingleton().addTask(mJobScheduler, GameLoop::TG_GRAPHICS);
        LOG_MESSAGE(Logger::CORE,"JobScheduler erzeugt");

		mZoneManager = new ZoneManager();
        LOG_MESSAGE(Logger::CORE,"ZoneManager erzeugt");

		new meshmagick::OgreEnvironment();
		meshmagick::OgreEnvironment::getSingleton().initialize(false, Logger::getSingleton()._getLog());

        return true;
    }

    void CoreSubsystem::initializeResources()
    {
        mXmlResourceManager = new XmlResourceManager();

        // Fuer Configs die keinem Typ zugeordnet sind,
        // und die per kompletten Verezeichnis erfragt werden
        ResourceGroupManager::getSingleton().addResourceLocation(
            ConfigurationManager::getSingleton().
                getModulesRootDirectory(),
            "FileSystem",
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);


        // Initialise the modules
        Ogre::StringVector modulesList = ConfigurationManager::getSingleton().getModuleList();

        for (size_t i = 0; i < modulesList.size(); i++)
        {
            mRubyInterpreter->executeFile(ContentModule::getInitFile(modulesList[i]));

            ContentModule* module = getModule(modulesList[i]);

            if (module == NULL)
            {
                Throw(rl::RuntimeException,
                      ContentModule::getInitFile(modulesList[i]) + " did not register module '" + modulesList[i] + "'");
            }
            //else
            //{
            //    if (module->isCommon())
            //    {
            //        module->initializeTextures();
            //        module->initialize();
            //    }
            //}
        }
    }

    ContentModule* CoreSubsystem::getModule(const String& moduleId) const
    {
        ModuleMap::const_iterator moduleIt = mModules.find(moduleId);

        if (moduleIt != mModules.end())
        {
            return (*moduleIt).second;
        }
        else
        {
            return NULL;
        }
    }

    void CoreSubsystem::registerModule(ContentModule* module)
    {
        mModules[module->getId()] = module;
    }

    void CoreSubsystem::updateDefaultScheme()
    {
        int numTu = mOgreRoot->getRenderSystem()->getCapabilities()->getNumTextureUnits();

        Ogre::String tuScheme;

        if (numTu >= 6)
            tuScheme = "tu6";
        else if (numTu >= 2)
            tuScheme = "tu2";
        else
            tuScheme = "tu1";

        LOG_MESSAGE(Logger::CORE,
            "Found " + Ogre::StringConverter::toString(numTu) + " Texture Units, using "+
            "alphablending scheme " + tuScheme);

        for (ResourceManager::ResourceMapIterator itMat =
            MaterialManager::getSingleton().getResourceIterator();
            itMat.hasMoreElements();)
        {
            MaterialPtr mat = itMat.getNext();
            for (Material::TechniqueIterator itTech =
                mat->getTechniqueIterator();
                itTech.hasMoreElements();)
            {
                Technique* tech = itTech.getNext();
                if (tech->getSchemeName() == tuScheme)
                {
                    tech->setSchemeName(MaterialManager::DEFAULT_SCHEME_NAME);
                    mDefaultTechniques.push_back(tech);
                }
                else if (tech->getSchemeName() == MaterialManager::DEFAULT_SCHEME_NAME)
                {
                    mDefaultTechniques.push_back(tech);
                }
            }
        }
    }

    void CoreSubsystem::setScheme(const Ogre::String& schemeName)
    {
        if (schemeName != MaterialManager::getSingleton().getActiveScheme())
        {
            /*for (std::vector<Technique*>::iterator iter = mDefaultTechniques.begin();
                iter != mDefaultTechniques.end(); ++iter)
            {
                Technique* cur = *iter;
                cur->setSchemeName(schemeName);
            }*/

            MaterialManager::getSingleton().setActiveScheme(schemeName);
        }
    }

    void CoreSubsystem::startAdventureModule(ContentModule* module)
    {
        if (mActiveAdventureModule != NULL)
        {
            mActiveAdventureModule->unload();
        }

        //mCoreEventCaster.dispatchEvent(new DataLoadedEvent(0.0));

        updateDefaultScheme();
        loadModule(module);
        mActiveAdventureModule = module;

        //mCoreEventCaster.dispatchEvent(new DataLoadedEvent(100.0));

        module->start();
    }

    void CoreSubsystem::loadModule(ContentModule* module)
    {
        if (module->getMinimumEngineVersion() > getEngineBuildNumber())
        {
            Throw(
                rl::RuntimeException,
                "Module "
                + Ogre::String(module->getName().c_str())
                + " needs engine >="
                + StringConverter::toString(module->getMinimumEngineVersion())
                + " but engine is "
                + StringConverter::toString(getEngineBuildNumber()));
        }

        StringVector deps = module->getDependencies();
        for (StringVector::const_iterator depsIt = deps.begin(); depsIt != deps.end(); depsIt++)
        {
            String depName = *depsIt;
            ModuleMap::iterator modIt = mModules.find(depName);
            if (modIt == mModules.end())
            {
                Throw(
                    rl::RuntimeException,
                    "Depedency Module " + depName
                    + " needed by " + Ogre::String(module->getName().c_str())
                    + " not found.");
            }

            ContentModule* depMod = (*modIt).second;

            if (!depMod->isLoaded())
            {
                loadModule(depMod);
            }
        }

        LOG_MESSAGE(
            Logger::CORE,
            "Start initializing module " + module->getName());
        module->initializeTextures();
        module->initialize();

        ResourceGroupManager::getSingleton().initialiseResourceGroup(module->getId());
        module->precreateMeshes();

        if (module->isCommon())
        {
            module->start();
        }

        LOG_MESSAGE(
            Logger::CORE,
            "Module " + module->getName() + " initialized.");
    }

    void CoreSubsystem::setDefaultActiveModule(const Ogre::String& module)
    {
        mDefaultActiveModule = module;
    }

    const Ogre::String& CoreSubsystem::getDefaultActiveModule() const
    {
        return mDefaultActiveModule;
    }

    World* CoreSubsystem::getWorld()
    {
        return mWorld;
    }

    unsigned long CoreSubsystem::getClock()
    {
        return mGameLoop->getClock();
    }

    Ogre::String CoreSubsystem::getEngineVersionString() const
    {
        static Ogre::String version = "0.3.0";
        return version;
    }

    Ogre::String CoreSubsystem::getEngineVersionName() const
    {
        static Ogre::String version = "Internal Build";
        return version;
    }

    long CoreSubsystem::getEngineBuildNumber() const
    {
        static const Ogre::String sMonths[] =
        {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
         "Sep", "Oct", "Nov", "Dec"};

        Ogre::String dateStr = Ogre::String(__DATE__);
        Ogre::String monthStr = dateStr.substr(0,3);
        int day = Ogre::StringConverter::parseInt(dateStr.substr(4,2));
        int year = Ogre::StringConverter::parseInt(dateStr.substr(7,4));
        int month = 0;

        while( month < 12 && monthStr.compare(sMonths[month]) != 0 )
            month++;

        return /* Jahr */          year * 100000 +
               /* Monat */     (month+1) * 1000 +
               /* Tag */           day * 10 +
               /* Sub-Version */     0;
    }

    RubyInterpreter* CoreSubsystem::getRubyInterpreter()
    {
        return mRubyInterpreter;
    }

    void CoreSubsystem::makeScreenshot( const String& sName )
    {
        mRenderWindow->writeContentsToTimestampedFile(sName, ".png");
    }

    ContentModule* CoreSubsystem::getActiveAdventureModule() const
    {
        return mActiveAdventureModule;
    }

    const ModuleMap& CoreSubsystem::getAllModules() const
    {
        return mModules;
    }

    void CoreSubsystem::loadMap(const String type, const String filename,
        const String module)
    {
        mWorld->loadScene(filename, module);
    }

    void CoreSubsystem::loadPlugins()
    {
        mSoundManager->applySettings(rl::ConfigurationManager::getSingleton().getSettings("Sound"));
        LOG_MESSAGE(Logger::CORE, "Soundeinstellungen geladen");
    }

    void CoreSubsystem::unloadPlugins()
    {
        mSoundManager->unloadAllDrivers();
        LOG_MESSAGE(Logger::CORE, "Soundtreiber entladen");
    }

    void CoreSubsystem::addCoreEventListener(rl::CoreEventListener *listener)
    {
        mCoreEventCaster.addEventListener(listener);
    }

    void CoreSubsystem::removeCoreEventListener(CoreEventListener* listener)
    {
        mCoreEventCaster.removeEventListener(listener);
    }
}
