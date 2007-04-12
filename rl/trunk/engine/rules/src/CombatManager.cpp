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

#include "CombatManager.h"

#include "Combat.h"
#include "Exception.h"

using namespace Ogre;

template<> rl::CombatManager* Singleton<rl::CombatManager>::ms_Singleton = 0;

namespace rl
{
    CombatManager& CombatManager::getSingleton(void)
    {
        return Singleton<CombatManager>::getSingleton();
    }

    CombatManager* CombatManager::getSingletonPtr(void)
    {
        return Singleton<CombatManager>::getSingletonPtr();
    }

    CombatManager::CombatManager() : mCurrentCombat(NULL)
    {
    }

    CombatManager::~CombatManager()
    {
    }

    void CombatManager::startCombat(Creature* character, Creature* firstOpponent)
    {
        if (mCurrentCombat != NULL)
        {
            Throw(IllegalStateException, "There already is a combat running.");
        }

        mCurrentCombat = new Combat(character);
        mCurrentCombat->addOpponent(firstOpponent);
        // TODO, add further opponents if found
    }

    Combat* CombatManager::getCurrentCombat() const
    {
        return mCurrentCombat;
    }
}
