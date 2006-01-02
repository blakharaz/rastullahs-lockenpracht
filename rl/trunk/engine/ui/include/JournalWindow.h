/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2005 Team Pantheon. http://www.team-pantheon.de
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

#ifndef __JOURNALWINDOW_H__
#define __JOURNALWINDOW_H__

#include "UiPrerequisites.h"

#include "CeGuiWindow.h"
#include "QuestStateChangeListener.h"

namespace rl {

	class JournalWindow : public CeGuiWindow, public QuestStateChangeListener {
	public:
		JournalWindow();
		virtual ~JournalWindow();

		virtual bool eventRaised(QuestStateChangeEvent *anEvent);

	private:
		void updateQuests();

		CEGUI::Listbox* mQuests;
		CEGUI::StaticText* mQuestTitle;
		CEGUI::StaticText* mQuestState;
		CEGUI::MultiLineEditbox* mQuestDescription;
	};
}

#endif //__JOURNALWINDOW_H__
