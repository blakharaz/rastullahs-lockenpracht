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

#include "stdinc.h" //precompiled header

#include "GameTask.h"

namespace rl
{

    GameTask::GameTask(bool interruptable)
        : mInterruptable(interruptable)
        , mPaused(false)
    {
    }

    bool GameTask::isPaused() const
    {
        return mPaused;
    }

    void GameTask::setPaused(bool isPaused)
    {
        if (mInterruptable)
        {
            mPaused = isPaused;
        }
    }

    bool GameTask::isInterruptable() const
    {
        return mInterruptable;
    }

    void GameTask::setTimeFactor(Ogre::Real timeFactor)
    {
    }
}
