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

#ifndef __ScriptSubsystem_H__
#define __ScriptSubsystem_H__

#include "ScriptPrerequisites.h"

namespace rl
{
    class ScriptObjectMarker;
    class TriggerFactory;

    class _RlScriptExport ScriptSubsystem : public Ogre::Singleton<ScriptSubsystem>
    {
    public:
        ScriptSubsystem();
        virtual ~ScriptSubsystem();

        void log(const CeGuiString& message);
        void logError(const CeGuiString& message);
        void setTriggerFactory(TriggerFactory* factory);
        TriggerFactory* getTriggerFactory() const;

    private:
        ScriptObjectMarker* mScriptObjectMarker;
        TriggerFactory* mTriggerFactory;

        void initializeScriptSubsystem();
    };
}
#endif
