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


#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <OgreKeyEvent.h>
#include <OgreRoot.h>

#include "XmlHelper.h"
#include "XmlResource.h"
#include "XmlResourceManager.h"

#if OGRE_PLATFORM != PLATFORM_WIN32
#include "SDL/SDL.h"
#endif

#include "Console.h"
#include "DebugWindow.h"
#include "CommandMapper.h"
#include "Actor.h"
#include "ActorManager.h"

#include "CeGuiWindow.h"
#include "GameLoop.h"
#include "CoreSubsystem.h"

#include "InputManager.h"



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

	InputManager::InputManager() :
		mEventInitialized(false),
		mBuffered(false), 
		mInputInitialized(false),
		mNumActiveWindowsMouseInput(0),
		mNumActiveWindowsKeyboardInput(0),
		mNumActiveWindowsAllInput(0)
	{
		switchMouseToUnbuffered();
		mEventProcessor = new EventProcessor();
		GameLoopManager::getSingleton().addSynchronizedTask(this);
		for(int i=0; i<NUM_KEYS; i++)
			mKeyDown[i] = false;

		mScreenX = Root::getSingleton().getAutoCreatedWindow()->getWidth();
		mScreenY = Root::getSingleton().getAutoCreatedWindow()->getHeight();		
	}

	InputManager::~InputManager()
	{
		mEventQueue.activateEventQueue(false);
		GameLoopManager::getSingleton().removeSynchronizedTask(this);
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
		if (mNumActiveWindowsKeyboardInput == 0)
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

	bool InputManager::sendKeyToCeGui(KeyEvent* e)
	{
		// Wenn kein Fenster mit Tastatureingabe aktiv ist, kriegt CEGUI keine KeyEvents
		if (mNumActiveWindowsKeyboardInput == 0)
			return false;

		// Fenster, die alle Inputs wollen
		if (mNumActiveWindowsAllInput > 0)
			return true;

		// Tastatureingabe gefordert
		// Alle Tasten an CEGUI senden, die ein Zeichen erzeugen
		if (e->getKeyChar() != 0)
			return true;

		if (e->getKey() == KC_RETURN || 
			e->getKey() == KC_HOME || e->getKey() == KC_END ||
			e->getKey() == KC_LEFT || e->getKey() == KC_RIGHT ||
			e->getKey() == KC_BACK || e->getKey() == KC_DELETE ||
			e->getKey() == KC_UP || e->getKey() == KC_DOWN)
			return true;

		return false;
	}

	void InputManager::keyPressed(KeyEvent* e)
	{
		if (sendKeyToCeGui(e)) 
		{   // Send all events to CEGUI
			CEGUI::System& cegui = CEGUI::System::getSingleton();
			cegui.injectKeyDown(e->getKey());
			cegui.injectChar(getKeyChar(e));
			e->consume();
			return;
		}

		mKeyDown[e->getKey()]=true;
		CommandMapper::getSingleton().injectKeyDown(e->getKey());
        std::set<KeyListener*>::iterator i;
        for(i=mKeyListeners.begin(); i!=mKeyListeners.end(); i++)
			(*i)->keyPressed(e);

		e->consume();
	}

	void InputManager::keyReleased(KeyEvent* e)
	{
		if (sendKeyToCeGui(e)) 
		{
			CEGUI::System& cegui = CEGUI::System::getSingleton();
			cegui.injectKeyUp(e->getKey());
			e->consume();

			return;
		}

		mKeyDown[e->getKey()]=false;
		CommandMapper::getSingleton().injectKeyUp(e->getKey());
		std::set<KeyListener*>::iterator i;
		for(i=mKeyListeners.begin(); i!=mKeyListeners.end(); i++)
			(*i)->keyReleased(e);
		e->consume();
	}

	void InputManager::keyClicked(KeyEvent* e) 
	{
		if (sendKeyToCeGui(e)) 
			return;
		
		CommandMapper::getSingleton().injectKeyClicked(e->getKey());
		e->consume();
	}

	void InputManager::mouseDragged(MouseEvent* e)
	{
		mouseMoved(e);
	}

	CeGuiString InputManager::getKeyName(int combinedKeyCode)
	{
		//TODO: Decode key code
		return getKeyName(combinedKeyCode, 0);
	}

	CeGuiString InputManager::getKeyName(int scancode, int syskeys)
	{
		using namespace Ogre; 

		CeGuiString name = mKeyNames.find(scancode)->second;
		if (syskeys & InputEvent::ALT_MASK)
			name = "Alt-"+name;
		if (syskeys & InputEvent::CTRL_MASK)
			name = "Ctrl-"+name;
		if (syskeys & InputEvent::SHIFT_MASK)
			name = "Shift-"+name;
		return name;
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

	void InputManager::registerCeGuiWindow(CeGuiWindow* window)
	{
		if (window->getWindowType() == CeGuiWindow::WND_SHOW)
			return;

		bool active = isCeguiActive();

		if (window->getWindowType() == CeGuiWindow::WND_MOUSE_INPUT)
			mNumActiveWindowsMouseInput++;
		else if (window->getWindowType() == CeGuiWindow::WND_KEYBOARD_INPUT)
			mNumActiveWindowsKeyboardInput++;
		else if (window->getWindowType() == CeGuiWindow::WND_ALL_INPUT)
			mNumActiveWindowsAllInput++;
		
		if (!active && isCeguiActive()) // war nicht aktiv, sollte jetzt aktiv sein -> anschalten
		{
			switchMouseToBuffered();
			CEGUI::MouseCursor::getSingleton().show();
		}
	}

	void InputManager::unregisterCeGuiWindow(CeGuiWindow* window)
	{
		if (window->getWindowType() == CeGuiWindow::WND_SHOW)
			return;

		bool active = isCeguiActive();

		if (window->getWindowType() == CeGuiWindow::WND_MOUSE_INPUT)
			mNumActiveWindowsMouseInput--;
		else if (window->getWindowType() == CeGuiWindow::WND_KEYBOARD_INPUT)
			mNumActiveWindowsKeyboardInput--;
		else if (window->getWindowType() == CeGuiWindow::WND_ALL_INPUT)
			mNumActiveWindowsAllInput--;

		if (active && !isCeguiActive()) // war aktiv, sollte nicht mehr aktiv sein -> ausschalten
		{
			CEGUI::MouseCursor::getSingleton().hide();
			switchMouseToUnbuffered();		
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
		return 
			mNumActiveWindowsKeyboardInput > 0 || 
			mNumActiveWindowsMouseInput > 0 || 
			mNumActiveWindowsAllInput > 0;
	}

	/**
	 * Ermittelt aus einem KeyEvent das zugehörige Zeichen auf der Tastatur
	 * @todo Um andere Sprachen zu ermöglichen, in datengetriebene Lösung umwandeln, 
	 * Locale-Dateien, generischer Ansatz
	 * 
	 * @param ke Ogre-KeyEvent zu verarbeitendes Event
	 * @return Zeichen, das der gedrückten Tastenkombination entspricht
	 */
	CEGUI::utf32 InputManager::getKeyChar(KeyEvent* ke)
	{
		KeyCharMap* keymap;
		if (!ke->isShiftDown() && !ke->isAltDown())
			keymap = &mKeyMapNormal;
		else if (ke->isShiftDown() && !ke->isAltDown())
			keymap = &mKeyMapShift;
		else if (!ke->isShiftDown() && ke->isAltDown())
			keymap = &mKeyMapAlt;
		else
			return ke->getKeyChar();

		KeyCharMap::iterator keyIter = keymap->find(ke->getKey());
		if (keyIter != keymap->end())
			return (*keyIter).second;
			
		return ke->getKeyChar();
	}

	void InputManager::loadKeyMapping(const Ogre::String& filename)
	{
		using namespace XERCES_CPP_NAMESPACE;
		using XERCES_CPP_NAMESPACE::DOMDocument;
		using std::make_pair;

		XMLPlatformUtils::Initialize();
		XmlHelper::initializeTranscoder();

		XercesDOMParser* parser = new XercesDOMParser();
        parser->setValidationScheme(XercesDOMParser::Val_Always);    // optional.
        parser->setDoNamespaces(true);    // optional

/*        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);*/

		XMLCh* ALT = XMLString::transcode("AltChar");
		XMLCh* SHIFT = XMLString::transcode("ShiftChar");
		XMLCh* NORMAL = XMLString::transcode("NormalChar");
		XMLCh* DESCR = XMLString::transcode("KeyDescription");
		XMLCh* CODE = XMLString::transcode("KeyCode");
		XMLCh* KEY = XMLString::transcode("Key");
		
		XmlResourceManager::getSingleton().create(filename)->parseBy(parser);
		DOMDocument* doc = parser->getDocument();
		DOMElement* dataDocumentContent = doc->getDocumentElement();

		DOMNodeList* keymaps = dataDocumentContent->getElementsByTagName(KEY);
		for (unsigned int idx = 0; idx < keymaps->getLength(); idx++)
		{
			DOMElement* key = static_cast<DOMElement*>(keymaps->item(idx));
			int keycode = XMLString::parseInt(key->getAttribute(CODE));

			const XMLCh* xmlch;

			xmlch = key->getAttribute(NORMAL);
			if (xmlch != NULL && XMLString::stringLen(xmlch) > 0)
			{
				CeGuiString s(XmlHelper::transcodeToUtf8(xmlch)); 
				mKeyMapNormal.insert(make_pair(keycode, s[0]));
			}

			xmlch = key->getAttribute(ALT);
			if (xmlch != NULL && XMLString::stringLen(xmlch) > 0)
			{
				CeGuiString s(XmlHelper::transcodeToUtf8(xmlch)); 
				mKeyMapAlt.insert(make_pair(keycode, s[0]));
			}

			xmlch = key->getAttribute(SHIFT);
			if (xmlch != NULL && XMLString::stringLen(xmlch) > 0)
			{
				CeGuiString s(XmlHelper::transcodeToUtf8(xmlch)); 
				mKeyMapShift.insert(make_pair(keycode, s[0]));
			}

			xmlch = key->getAttribute(DESCR);
			mKeyNames.insert(make_pair(keycode, XmlHelper::transcodeToUtf8(xmlch)));
		}

		XMLString::release(&ALT);
		XMLString::release(&SHIFT);
		XMLString::release(&NORMAL);
		XMLString::release(&CODE);
		XMLString::release(&DESCR);
		XMLString::release(&KEY);

		doc->release();
		XMLPlatformUtils::Terminate();
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
        DebugWindow::getSingleton().setText(
            "X="+StringConverter::toString(mouseRelX)+
            "   Y="+StringConverter::toString(mouseRelY)+
            "   - Object("+(a==NULL?"null":a->getName())+")");		

        //mTargetedObject = a->getGameObject();		
    }

	bool InputManager::isKeyDown(KeyCode kc) 
	{ 
		return mKeyDown[kc]; 
	}
	
	bool InputManager::isMouseButtonDown(int iButtonID) 
	{ 
		if (mInputInitialized)
			return mInputReader->getMouseButton(iButtonID); 

		return false;
	}


	Ogre::Real InputManager::getMouseRelativeX(void) 
	{ 
		if (mInputInitialized)
			return mInputReader->getMouseRelativeX(); 

		return 0;
	}

	Ogre::Real InputManager::getMouseRelativeY(void) 
	{ 
		if (mInputInitialized)
			return mInputReader->getMouseRelativeY(); 

		return 0;
	}

	Ogre::Real InputManager::getMouseRelativeZ(void) 
	{ 
		if (mInputInitialized)
			return mInputReader->getMouseRelativeZ(); 

		return 0;
	}


}
