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

#ifndef __DialogSubsystem_H__
#define __DialogSubsystem_H__

#include <OgreSingleton.h>

#include "DialogPrerequisites.h"

namespace rl
{
	/** Initialise ans manage everything for using dialogs
	 *  @author Philipp Walser
	*/
	class _RlDialogExport DialogSubsystem: public Ogre::Singleton<DialogSubsystem>
	{
	public:
		static DialogSubsystem & getSingleton(void);
        static DialogSubsystem * getSingletonPtr(void);

		DialogSubsystem();
		virtual ~DialogSubsystem();

		void log(const Ogre::LogMessageLevel level, const Ogre::String& msg, const Ogre::String& ident = "");
	private:
		Ogre::Log* mLog;
	};
}
#endif
