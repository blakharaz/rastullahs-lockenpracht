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
#include "stdinc.h" //precompiled header

#include "QuestKnownPredicates.h"

#include "Exception.h"
#include "QuestBook.h"
#include "Quest.h"
#include "RulesSubsystem.h"

namespace rl {

QuestKnownPredicates::QuestKnownPredicates()
{
}

QuestKnownPredicates::~QuestKnownPredicates(void)
{
}

CeGuiString QuestKnownPredicates::getPredicate(const CeGuiString& name) const
{
	Quest* quest = RulesSubsystem::getSingletonPtr()->getQuestBook()
		->getQuest(name);

	if (quest == NULL)
	{
		Throw(
			IllegalArgumentException,
			("Quest '"
			+ name
			+ "' not found").c_str());
	}

	return quest->getKnownName();
}

void QuestKnownPredicates::setPredicate(const CeGuiString& name, const CeGuiString& value)
{
	Quest* quest = RulesSubsystem::getSingletonPtr()->getQuestBook()
		->getQuest(name);

	if (quest == NULL)
	{
		Throw(
			IllegalArgumentException,
			("Quest '"
			+ name
			+ "' not found").c_str());
	}

	quest->setKnown(quest->getKnownFromName(value));
}

CeGuiString QuestKnownPredicates::getType() const
{
	return "questknown";
}

}