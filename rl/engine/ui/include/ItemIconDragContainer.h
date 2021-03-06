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
#ifndef __ItemIconDragContainer_H__
#define __ItemIconDragContainer_H__

#include "UiPrerequisites.h"

#include "ItemDragContainer.h"

namespace rl
{
    class Item;

    class ItemIconDragContainer : public ItemDragContainer
    {
    public:
        ItemIconDragContainer(const CeGuiString& type, const CeGuiString& name);
        void setItem(Item* item);
        static const CeGuiString WidgetTypeName; // for CEGUI
    };

} // namespace rl

namespace CEGUI
{

    using rl::ItemIconDragContainer;

    CEGUI_DECLARE_WINDOW_FACTORY(ItemIconDragContainer)
}

#endif //__ItemIconDragContainer_H__
