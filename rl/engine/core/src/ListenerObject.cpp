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

#include "Actor.h"
#include "ListenerMovable.h"
#include "ListenerObject.h"
#include "SoundManager.h"

using namespace Ogre;

namespace rl
{

    /**
     * @param listener. Der Listener, Besitz wird uebernommen.
     * @author JoSch
     * @date 03-16-2005
     */
    ListenerObject::ListenerObject(ListenerMovable* listener)
        : ActorControlledObject()
    {
        mMovableObject = dynamic_cast<MovableObject*>(listener);
    }

    /**
     * @author JoSch
     * @date 03-16-2005
     */
    ListenerObject::~ListenerObject()
    {
        if (mMovableObject)
        {
            delete mMovableObject;
        }
    }

    /**
     * @return Immer false, weil kein Meshobjekt.
     * @author JoSch
     * @date 03-16-2005
     */
    bool ListenerObject::isMeshObject()
    {
        return false;
    }

    /**
     * @author JoSch
     * @date 03-16-2005
     */
    void ListenerObject::_update()
    {
        ActorControlledObject::_update();
        ListenerMovable* listener = getListener();
        Actor* actor = getActor();
        if (!listener || !actor) // Einer ist Null
        {
            LOG_DEBUG(Logger::CORE, "Pos Listener: NULL!");
            return;
        }
        listener->setPosition(actor->getWorldPosition());
        listener->setOrientation(actor->getWorldOrientation());
        listener->setVelocity(actor->getVelocity());
        LOG_DEBUG(Logger::CORE,
            "Pos Listener: " + StringConverter::toString(actor->getWorldPosition().x) + " "
                + StringConverter::toString(actor->getWorldPosition().y) + " "
                + StringConverter::toString(actor->getWorldPosition().z) + ", "
                + "Orient Listener: " + StringConverter::toString(actor->getWorldOrientation().w) + " "
                + StringConverter::toString(actor->getWorldOrientation().x) + " "
                + StringConverter::toString(actor->getWorldOrientation().y) + ", "
                + StringConverter::toString(actor->getWorldOrientation().z));
    }

    /**
     * @param Der bewegbare Listener
     * @author JoSch
     * @date 03-16-2005
     */
    ListenerMovable* ListenerObject::getListener() const
    {
        return static_cast<ListenerMovable*>(mMovableObject);
    }

    /**
     * @return Immer "ListenerObject"
     * @author JoSch
     * @date 03-16-2005
     */
    String ListenerObject::getObjectType() const
    {
        return "ListenerObject";
    }
}
