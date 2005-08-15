/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2005 Team Pantheon. http://www.team-pantheon.de
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Perl Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Perl Artistic License for more details.
 *
 *  You should have received a copy of the Perl Artistic License
 *  along with this program; if not you can get it here
 *  http://www.perldoc.com/perl5.6/Artistic.html.
 */
#include <boost/bind.hpp>

#include "UiPrerequisites.h"

#include "UiSubsystem.h"
#include "CoreSubsystem.h"
#include "WindowManager.h"

#include "MainMenuWindow.h"

using namespace CEGUI;
using namespace Ogre;

namespace rl {

	MainMenuWindow::MainMenuWindow(GameObject* actionHolder) :
		CeGuiWindow("mainmenuwindow.xml", WND_ALL_INPUT),
		mActiveModule(""),
		mActionHolder(actionHolder)
	{
		getWindow("MainMenu/Game/Start")->subscribeEvent(
			MenuItem::EventClicked, 
			boost::bind(&MainMenuWindow::handleStart, this));

/*		getWindow("MainMenuWindow/GraphicOptions")->subscribeEvent(
			Window::EventMouseClick, 
			boost::bind(&MainMenuWindow::handleGraphicOptions, this));
		
		getWindow("MainMenuWindow/InputOptions")->subscribeEvent(
			Window::EventMouseClick,
			boost::bind(&UiSubsystem::showInputOptionsMenu, UiSubsystem::getSingletonPtr(), mActionHolder));
*/
		getWindow("MainMenu/Game/Quit")->subscribeEvent(
			MenuItem::EventClicked, 
			boost::bind(&MainMenuWindow::handleQuit, this));
		
		mWindow->subscribeEvent(
			Window::EventKeyUp, 
			boost::bind(&MainMenuWindow::handleKey, this, _1));

		addToRoot(mWindow);

		fillModules();
	}

	void MainMenuWindow::fillModules()
	{
		MenuBase* modulesMenu = getMenu("MainMenu/Modules/Menu");
		WindowFactory* factoryPopupItem = WindowFactoryManager::getSingleton().getFactory("RastullahLook/PopupMenuItem");

		Ogre::StringVector modules = CoreSubsystem::getSingleton().getActivatableModules();
		mActiveModule = CoreSubsystem::getSingleton().getActiveModule();
		if (mActiveModule.length() == 0)
			mActiveModule = *modules.begin();

		for(Ogre::StringVector::iterator mod = modules.begin();	
			mod != modules.end(); mod++)
		{
			MenuItem* it = static_cast<MenuItem*>(
				factoryPopupItem->createWindow(getNamePrefix()+"MainMenu/Modules/" + *mod));
			
			it->setText(*mod);
			modulesMenu->addItem(it);
			if ((*mod) == mActiveModule)
				it->setText(*mod+" *");
			it->subscribeEvent(
				MenuItem::EventClicked,
				boost::bind(&MainMenuWindow::handleChooseModule, this, it, *mod));
		}
	}

	bool MainMenuWindow::handleChooseModule(MenuItem* it, Ogre::String module)
	{
		MenuBase* modulesMenu = getMenu("MainMenu/Modules/Menu");
		
		ItemEntry* itOld = NULL;
		for (size_t i=0; i<modulesMenu->getItemCount(); i++)
		{
			ItemEntry* curr = modulesMenu->getItemFromIndex(i);
			if (curr->getText().compare(mActiveModule+" *") == 0)
			{
				itOld = curr;
				break;
			}
		}
		itOld->setText(mActiveModule);

		mActiveModule = module;
		it->setText(module+" *");	

		return true;
	}

	bool MainMenuWindow::handleStart()
	{
		setVisible(false);
		rl::WindowManager::getSingleton().destroyWindow(this);
		CoreSubsystem::getSingleton().setActiveModule(mActiveModule.c_str());

        this->setVisible( false );
		return true;
	}

	bool MainMenuWindow::handleQuit()
	{
		UiSubsystem::getSingleton().requestExit();
		return true;
	}

	bool MainMenuWindow::handleGraphicOptions()
	{
		return true;
	}
	
	bool MainMenuWindow::handleKey(const EventArgs& evt)
	{
		const KeyEventArgs kevt = static_cast<const KeyEventArgs&>(evt);
		
		UiSubsystem::getSingleton().log(StringConverter::toString(kevt.scancode), "blah");
		
		if (kevt.scancode == Key::Q || kevt.scancode == Key::Escape)
			return handleQuit();

		return false;
	}
}
