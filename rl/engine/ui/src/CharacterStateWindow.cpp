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

#include "UiPrerequisites.h"
#include <boost/bind.hpp>

#include "Creature.h"
#include "DsaManager.h"
#include "InputManager.h"
#include "Talent.h"

#include "CharacterStateWindow.h"

using namespace CEGUI;
using namespace Ogre;

namespace rl
{

    CharacterStateWindow::CharacterStateWindow()
        : AbstractWindow("characterstatewindow.xml", WIT_NONE, false)
        , mCharacter(NULL)
    {
        mLP = getProgressBar("CharacterStateWindow/LP");
        mAP = getProgressBar("CharacterStateWindow/AP");
        mAU = getProgressBar("CharacterStateWindow/AU");
        mName = getWindow("CharacterStateWindow/Name");
    }

    CharacterStateWindow::~CharacterStateWindow()
    {
        if (mCharacter != NULL)
            mCharacter->removeObjectStateChangeListener(this);
    }

    void CharacterStateWindow::setCharacter(Creature* person)
    {
        if (mCharacter != NULL)
            mCharacter->removeObjectStateChangeListener(this);

        mCharacter = person;
        if (mCharacter)
            mCharacter->addObjectStateChangeListener(this);
        update();
    }

    void CharacterStateWindow::update()
    {
        if (!isVisible() || mCharacter == NULL)
        {
            return;
        }

        mName->setText(mCharacter->getName());

        float lep;
        if (mCharacter->getLeMax() <= 0)
        {
            lep = 0.0;
        }
        else
        {
            lep = (float)mCharacter->getLe() / (float)mCharacter->getLeMax();
        }
        mLP->setProgress(lep);

        float au;
        if (mCharacter->getAuMax() <= 0)
        {
            au = 0.0;
        }
        else
        {
            au = (float)mCharacter->getAu() / (float)mCharacter->getAuMax();
        }
        mAU->setProgress(au);

        if (!mCharacter->isMagic())
        {
            if (mAP->isVisible())
            {
                mAP->setVisible(false);
            }
        }
        else
        {
            if (!mAP->isVisible())
            {
                mAP->setVisible(true);
            }

            float asp;
            if (mCharacter->getAeMax() <= 0)
            {
                asp = 0.0;
            }
            else
            {
                asp = (float)mCharacter->getAe() / (float)mCharacter->getAeMax();
            }
            mAP->setProgress(asp);
        }
    }

    void CharacterStateWindow::objectStateChanged(ObjectStateChangeEvent* evt)
    {
        update();
    }

    void CharacterStateWindow::setVisible(bool visible, bool destroyAfterHide)
    {
        AbstractWindow::setVisible(visible, destroyAfterHide);
        if (visible)
        {
            update();
        }
    }
}
