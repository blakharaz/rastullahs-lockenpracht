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

#include "SubtitleWindow.h"

#include "GameObject.h"

namespace rl
{
	SubtitleWindow::SubtitleWindow()
		: CeGuiWindow("subtitlewindow.xml", WND_SHOW, false)
	{
		mSubtitle = getMultiLineEditbox("SubtitleWindow/Text");
	}
	
	SubtitleWindow::~SubtitleWindow()
	{
	}
	
	void SubtitleWindow::show(const CeGuiString& text)
	{
		mSubtitle->setText(text);
		setVisible(true);
        LOG_DEBUG(Logger::UI, 
			"Subtitle: " + text);
	}

	const CeGuiString& SubtitleWindow::getText() const
	{
		return mSubtitle->getText();
	}
	
} // namespace rl
