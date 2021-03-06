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

#include "DialogResponse.h"

#include "Dialog.h"
#include "DialogImplication.h"
#include "DialogOption.h"

namespace rl
{
    DialogResponse::DialogResponse(const CeGuiString& id, const CeGuiString& person)
        : DialogElement(id, person)
    {
    }

    DialogResponse::~DialogResponse()
    {
    }

    void DialogResponse::addOption(rl::DialogOption* option)
    {
        mOptions.push_back(option);
    }

    const DialogResponse::Options& DialogResponse::getOptions(Dialog* dialog) const
    {
        return mOptions;
    }

    const DialogResponse::Options DialogResponse::getAvailableOptions(Dialog* dialog) const
    {
        Options availableOptions;

        Options allOptions = getOptions(dialog);
        for (Options::const_iterator it = allOptions.begin(); it != allOptions.end(); ++it)
        {
            DialogOption* cur = *it;
            if (cur->isAutoSelected())
            {
                availableOptions.push_back(cur);
                break;
            }
            if (cur->isAvailable(dialog))
            {
                availableOptions.push_back(cur);
            }
        }
        return availableOptions;
    }

    void DialogResponse::addImplication(DialogImplication* implication)
    {
        mEffects.push_back(implication);
    }

    void DialogResponse::applyImplications(rl::Dialog* dialog)
    {
        for (Implications::iterator it = mEffects.begin(); it != mEffects.end(); ++it)
        {
            (*it)->apply(dialog);
        }
    }

    const CeGuiString& DialogResponse::getDefaultPerson() const
    {
        static CeGuiString PERSON = "npc";
        return PERSON;
    }

    DialogResponseSelection::DialogResponseSelection(const CeGuiString& id, const CeGuiString& person)
        : DialogSelection<DialogResponse>(id, person)
    {
    }

    const DialogResponse::Options& DialogResponseSelection::getOptions(Dialog* dialog) const
    {
        return getSelectedElement(dialog)->getOptions(dialog);
    }
}
