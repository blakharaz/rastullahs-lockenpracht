/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2004 Team Pantheon. http://www.team-pantheon.de
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

#include <OgreKeyEvent.h>
#include <OgreRoot.h>

#include <CEGUI.h>

#include "InputManager.h"
#if OGRE_PLATFORM != PLATFORM_WIN32
#include "SDL/SDL.h"
#endif

#include "CoreSubsystem.h"

#include "Console.h"
#include "DebugWindow.h"
#include "GameLoop.h"
#include "CommandMapper.h"

#include "Actor.h"
#include "ActorManager.h"

template<> rl::InputManager* Singleton<rl::InputManager>::ms_Singleton = 0;
using namespace Ogre;
using CEGUI::System;

namespace rl {

    InputManager& InputManager::getSingleton(void)
	{
		return Singleton<InputManager>::getSingleton();
	}

	InputManager* InputManager::getSingletonPtr(void)
	{
		return Singleton<InputManager>::getSingletonPtr();
	}

	InputManager::InputManager(void):mEventInitialized(false)
	{
		switchMouseToUnbuffered();
		mEventProcessor = new EventProcessor();
		GameLoop::getSingleton().addSynchronizedTask(this);
		for(int i=0; i<NUM_KEYS; i++)
			mKeyDown[i] = false;

		mScreenX = Root::getSingleton().getAutoCreatedWindow()->getWidth();
		mScreenY = Root::getSingleton().getAutoCreatedWindow()->getHeight();
		
	}

	InputManager::~InputManager()
	{
		mEventQueue.activateEventQueue(false);
		GameLoop::getSingleton().removeSynchronizedTask(this);
//		Root::getSingleton().removeFrameListener(this);

		mInputReader->useBufferedInput(NULL, false, false);
		mInputReader->setBufferedInput(false, false);
		delete mEventProcessor;
	}


	void InputManager::addKeyListener(KeyListener *l)
	{
		mKeyListeners.insert(l);
	}

	void InputManager::removeKeyListener(KeyListener *l)
	{
		mKeyListeners.erase(l);
	}

	void InputManager::run(Real elapsedTime)
	{
		if (!isCeguiActive())
		{
			mInputReader->capture();
			while (mEventQueue.getSize() > 0)
			{
				InputEvent* ie = mEventQueue.pop();
				if(ie->getID() == KeyEvent::KE_KEY_PRESSED)
					keyPressed(static_cast<KeyEvent*>(ie));
				else if(ie->getID() == KeyEvent::KE_KEY_RELEASED)
					keyReleased(static_cast<KeyEvent*>(ie));
				else if(ie->getID() == KeyEvent::KE_KEY_CLICKED)
					keyClicked(static_cast<KeyEvent*>(ie));
			}			
		}
	}

	void InputManager::mouseClicked(MouseEvent* e) {}
	void InputManager::mouseEntered(MouseEvent* e) {}
	void InputManager::mouseExited(MouseEvent* e)  {}

	void InputManager::mousePressed(MouseEvent* e)
	{
		if (isCeguiActive())
		{
			System::getSingleton().injectMouseButtonDown(
				convertOgreButtonToCegui(e->getButtonID()));
			e->consume();
		}
	}

	void InputManager::mouseReleased(MouseEvent* e)
	{
		if (isCeguiActive())
		{
			System::getSingleton().injectMouseButtonUp(
				convertOgreButtonToCegui(e->getButtonID()));
			e->consume();
		}	
	}

    void InputManager::mouseMoved(MouseEvent* e)
	{
		if (isCeguiActive())
		{			
			CEGUI::Renderer* renderer  = System::getSingleton().getRenderer();
			System::getSingleton().injectMouseMove(
				e->getRelX() * renderer->getWidth(), 
				e->getRelY() * renderer->getHeight());			

			if (mPickObjects)
				updatePickedObject(e->getX(), e->getY());

			e->consume();
		}
	}

	bool InputManager::processGlobalKeyEvent(KeyEvent* e)
    {
        bool rval = false;
        if (e->getKey() == KC_F11)
        {
            Console::getSingletonPtr()->setVisible(
                !Console::getSingletonPtr()->isVisible());
            rval = true;
        }
        else if (e->getKey() == KC_F5)
        {
            DebugWindow::getSingletonPtr()->setVisible(
                !DebugWindow::getSingletonPtr()->isVisible());
            rval = true;
        }
		else  if (e->getKey() == KC_SYSRQ)
        {
			CoreSubsystem::getSingleton().makeScreenshot("rastullah");
            rval = true;
        }

        return rval;
    }

	void InputManager::keyPressed(KeyEvent* e)
	{
		if (!processGlobalKeyEvent(e) && isCeguiActive()) 
		{   // Send all events to CEGUI
			CEGUI::System& cegui = CEGUI::System::getSingleton();
			cegui.injectKeyDown(e->getKey());
			cegui.injectChar(getKeyChar(e));
			e->consume();
		}
		else
		{
            mKeyDown[e->getKey()]=true;
			CommandMapper::getSingleton().injectKeyDown(e->getKey());
            std::set<KeyListener*>::iterator i;
            for(i=mKeyListeners.begin(); i!=mKeyListeners.end(); i++)
                (*i)->keyPressed(e);
			e->consume();
		}

	}
	void InputManager::keyReleased(KeyEvent* e)
	{
		if (isCeguiActive()) 
		{   // Send all events to CEGUI
			CEGUI::System& cegui = CEGUI::System::getSingleton();
			cegui.injectKeyUp(e->getKey());
			e->consume();
		}
		else
		{
			mKeyDown[e->getKey()]=false;
			CommandMapper::getSingleton().injectKeyUp(e->getKey());
			std::set<KeyListener*>::iterator i;
			for(i=mKeyListeners.begin(); i!=mKeyListeners.end(); i++)
				(*i)->keyReleased(e);
			e->consume();
		}		
	}

	void InputManager::keyClicked(KeyEvent* e) 
	{
		if (!isCeguiActive())
		{
			CommandMapper::getSingleton().injectKeyClicked(e->getKey());
		}
	}

	void InputManager::mouseDragged(MouseEvent* e)
	{
		mouseMoved(e);
	}

	CEGUI::MouseButton InputManager::convertOgreButtonToCegui(int ogre_button_id)
	{
		switch (ogre_button_id)
		{
			default:
			case MouseEvent::BUTTON0_MASK:
				return CEGUI::LeftButton;
			case MouseEvent::BUTTON1_MASK:
				return CEGUI::RightButton;
			case MouseEvent::BUTTON2_MASK:
				return CEGUI::MiddleButton;
			case MouseEvent::BUTTON3_MASK:
				return CEGUI::X1Button;			
		}
	}

	void InputManager::addMouseMotionListener(MouseMotionListener *l)
	{
		if (mEventInitialized)
			mEventProcessor->addMouseMotionListener(l);

		mMouseMotionListeners.insert(l);
	}

	void InputManager::removeMouseMotionListener(MouseMotionListener *l)
	{
		if (mEventInitialized)
			mEventProcessor->removeMouseMotionListener(l);

		mMouseMotionListeners.erase(l);
	}

	void InputManager::registerCeguiWindow(CeGuiWindow* window)
	{
		if (!isCeguiActive())
		{
			switchMouseToBuffered();
			CEGUI::MouseCursor::getSingleton().show();
		}
		mActiveWindows.insert(window);
	}

	void InputManager::unregisterCeguiWindow(CeGuiWindow* window)
	{
		if (isCeguiActive())
		{
			mActiveWindows.erase(window);

			if (!isCeguiActive())
			{
				CEGUI::MouseCursor::getSingleton().hide();
				switchMouseToUnbuffered();		
			}
		}
	}

	void InputManager::switchMouseToBuffered()
	{
		 mBuffered = true;

		// Check to see if input has been initialized
		if (mInputInitialized) {

			// Destroy the input reader.
			//Ogre::Root::getSingleton().removeFrameListener(this);
			//mEventQueue.activateEventQueue(false);
			//mInputReader->useBufferedInput(NULL, false, false);			
			//PlatformManager::getSingleton().destroyInputReader( mInputReader );

			mInputInitialized = false;

		}

		mEventProcessor->initialise(Ogre::Root::getSingleton().getAutoCreatedWindow());

		mInputReader = mEventProcessor->getInputReader();

		mEventProcessor->addKeyListener(this);
		mEventProcessor->addMouseListener(this);
		mEventProcessor->addMouseMotionListener(this);
		mEventProcessor->startProcessingEvents();

		mEventInitialized = true; 
	}

	void InputManager::switchMouseToUnbuffered()
	{
		 mBuffered = false;

		// Check to see if event has been initialized
		if (mEventInitialized) {
			// Stop buffering events

		//	mEventProcessor->stopProcessingEvents();

			mEventProcessor->removeKeyListener(this);
			mEventProcessor->removeMouseListener(this);
			mEventProcessor->removeMouseMotionListener(this);

			mEventInitialized = false;
		}

		mEventQueue.activateEventQueue(true);

		mInputReader = Ogre::PlatformManager::getSingleton().createInputReader();
		mInputReader->useBufferedInput(&mEventQueue, true, false);
		mInputReader->setBufferedInput(true, false);
		mInputReader->initialise(Ogre::Root::getSingleton().getAutoCreatedWindow(), true, true);
		mInputInitialized = true; 
	}

	bool InputManager::isCeguiActive()
	{
		return !mActiveWindows.empty();
	}

	/**
	 * Ermittelt aus einem KeyEvent das zugehörige Zeichen auf der Tastatur
	 * @todo Um andere Sprachen zu ermöglichen, in datengetriebene Lösung umwandeln, 
	 * Locale-Dateien, generischer Ansatz
	 * 
	 * @param ke Ogre-KeyEvent zu verarbeitendes Event
	 * @return Zeichen, das der gedrückten Tastenkombination entspricht
	 */
	CEGUI::utf8 InputManager::getKeyChar(KeyEvent* ke)
	{
		if (!ke->isShiftDown() && !ke->isAltDown())
		{
			switch( ke->getKey() ) 
			{
				case KC_SLASH: return '-';
				case KC_MINUS: return 'ß';
				case KC_EQUALS: return '´';
				case KC_SEMICOLON: return 'ö'; 
				case KC_APOSTROPHE: return 'ä';
				case KC_GRAVE: return '^';
				case KC_COMMA: return ',';	
				case KC_PERIOD: return '.';	
				case KC_MULTIPLY: return '*';
				case KC_LBRACKET: return 'ü';	
				case KC_RBRACKET: return '+';
				case KC_BACKSLASH: return '#';
			}
		}
		else if (ke->isShiftDown() && !ke->isAltDown())
		{
			switch (ke->getKey())
			{
				case KC_1: return '!';
				case KC_2: return '"';
				case KC_3: return '§';
				case KC_4: return '$';
				case KC_5: return '%';
				case KC_6: return '&';
				case KC_7: return '/';
				case KC_8: return '(';
				case KC_9: return ')';
				case KC_0: return '=';
				case KC_SLASH: return '_';
				case KC_MINUS: return '?';
				case KC_EQUALS: return '`';
				case KC_SEMICOLON: return 'Ö';
				case KC_APOSTROPHE:	return 'Ä';
				//case KC_GRAVE: return '?';
				case KC_COMMA: return ';';	
				case KC_PERIOD:	return ':';
				case KC_LBRACKET: return 'Ü';	
				case KC_RBRACKET: return '*';
				case KC_BACKSLASH: return '\'';
			}
		}
		else if (!ke->isShiftDown() && ke->isAltDown())
		{
			switch (ke->getKey())
			{
				case KC_Q: return '@';	
				case KC_2: return '²';
				case KC_3: return '³';
				case KC_7: return '{';
				case KC_8: return '[';
				case KC_9: return ']';
				case KC_0: return '}';
				case KC_MINUS: return '\\';
				case KC_RBRACKET: return '~';
			}
		}

		return ke->getKeyChar();
	}

	void InputManager::setObjectPickingActive(bool active)
	{
		mPickObjects = active;
		if (!mPickObjects)
			mTargetedObject = NULL;
	}

    void InputManager::updatePickedObject(float mouseRelX, float mouseRelY)
    {
        Actor* a = ActorManager::getSingleton().getActorAt(mouseRelX, mouseRelY);
        //DebugWindow::getSingleton().setText(
        //    "X="+StringConverter::toString(mouseRelX)+
        //    "   Y="+StringConverter::toString(mouseRelY)+
        //    "   - Object("+(a==NULL?"null":a->getName())+")");		

        //mTargetedObject = a->getGameObject();		
    }

}
