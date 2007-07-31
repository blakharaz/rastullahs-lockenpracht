/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2007 Team Pantheon. http://www.team-pantheon.de
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

#ifndef __DialogCharacterController_H__
#define __DialogCharacterController_H__

#include "UiPrerequisites.h"
#include "ControlState.h"

#include <OgreCamera.h>

namespace rl {

	class Actor;
	class DialogCharacter;
	class DialogResponse;
	class DialogWindow;
	class GameLoggerWindow;
	class MeshAnimation;
	class SoundObject;
	class SubtitleWindow;

	/** Diese Klasse 
	  *  
	  */
	class _RlUiExport DialogControlState : public ControlState
	{
	public:
        enum DialogMode
		{ 
            // Frontperspektive auf Augenh�he, ausgehend von der Mitte zwischen den Redenden
			DM_FRONT = 1,
		};


		/**
		*  @throw NullPointerException if camera or character is NULL.
		*  @throw InvalidArgumentException if character is not placed in the scene.
		*/
		DialogControlState(CommandMapper* cmdMapper, Actor* camera, Person* character);
		/// Dtor 
		virtual ~DialogControlState();

        virtual void pause();
        virtual void resume();

		/// @override
		virtual void run(Ogre::Real elapsedTime);

		/// Setzt den Dialogpartner (Diealogf�hrenden Spieler-Actor)
		void setDialogPartner(Actor* partner);

		/// Antwort eines der Dialogf�hrenden
		void response(Actor* actor, const CeGuiString& text, const Ogre::String& soundFile = "");

        virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

		bool handleDialogSelectOption();	
		bool handleDialogClose();
		bool requestDialogClose();

	private:
		/// Die Zielkameraposition in lokalen Koordinaten
		Ogre::Vector3 mTargetCameraPosition;
		/// Die ben�tigte lokale Drehung der Kamera
		Ogre::Vector3 mTargetCameraDirection;

		/// Die aktuelle Zeit f�r die Textanzeige
		Ogre::Real mCurrFadeTextTime;
        /// Die Zeit bis der Text ausgeblendet wird
        Ogre::Real mTotalFadeTextTime;

        Ogre::Real mSubtitleSpeed;

		/// Der Untertitel Text
		CeGuiString mText;
		/// Es wird gerade Text angezeigt
		bool mTextShown;

		/// Der Spieler der redet
		Actor* mDialogPartner;
		/// Der Besitzer des Dialoges (Der Bauer mit dem der Spieler redet)
		Actor* mCurrentActor;
        /// Die Art der Kamerapositinierung
        DialogMode mDialogMode;

		MeshAnimation* mTalkAnimation;

		DialogWindow* mDialogWindow;
		SubtitleWindow* mSubtitleWindow;
		SoundObject* mSoundObject;
	
		float getShowTextLength(const CeGuiString& text) const;
        void recalculateCamera( Actor* speaker, Actor* listener );

		enum DialogState
		{
			CHOOSING_OPTION = 1,
			TALKING_PARTNER_CHARACTER,
			TALKING_PLAYER_CHARACTER,
			CLOSING_DIALOG
		};

		DialogCharacter* mBot;
		DialogResponse* mCurrentResponse;
		GameLoggerWindow* mGameLogger;
		DialogState mState;
		CeGuiString mCurrentResponseText;
				
		void getOptions(const CeGuiString& question);

		static const CeGuiString DIALOG_START;
		static const CeGuiString DIALOG_EXIT;
		static const CeGuiString DIALOG_END;

		void getResponse(const CeGuiString& msg);
		unsigned int count();
		void setCallback(Ogre::String function);
		int getSelectedOption();

		void initialize(DialogCharacter* bot);
		void textFinished();

        void start();

	};
}
#endif