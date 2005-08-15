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

#include "ObjectStateChangeListener.h"

#include "CoreSubsystem.h"
#include "Exception.h"

namespace rl {

    ObjectStateChangeListener::~ObjectStateChangeListener()
    {        
	}

	bool ObjectStateChangeListener::eventRaised(ObjectStateChangeEvent* evt)
	{
        try
        {
            objectStateChanged(evt);
        }
		catch( ScriptInvocationFailedException& sife )
        {
            CoreSubsystem::getSingleton().log( Ogre::LML_CRITICAL, sife.toString() );
        }

        // consumed or not
		return false;
	}
}

