/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2005 Team Pantheon. http://www.team-pantheon.de
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Perl Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Perl Artistic License for more details.
 *
 *  You should have received a copy of the Perl Artistic License
 *  along with this program; if not you can get it here
 *  http://www.perldoc.com/perl5.6/Artistic.html.
 */

#ifndef __ActorManager_H__
#define __ActorManager_H__

#include <map>
#include <vector>

#include "CorePrerequisites.h"
#include "PhysicsManager.h"
#include "LightObject.h"
#include "ParticleSystemObject.h"

#include <OgreOdeSpace.h>
#include <OgreOdeGeometry.h>
#include <OgreOdeCollision.h>

namespace rl {

class World;
class Actor;

typedef std::map<const String,Actor*> ActorPtrMap;
typedef std::pair<const String,Actor*> ActorPtrPair;

class _RlCoreExport ActorManager : protected Singleton<ActorManager>, private OgreOde::CollisionListener
{
    public:
        ActorManager( );
        virtual ~ActorManager( );

        Actor* getActor(const String& name);

        Actor* createLightActor(const String& name, rl::LightObject::LightTypes type );
        Actor* createSoundActor(const String& name, const String& soundfile );
        Actor* createListenerActor(const String& name);
        Actor* createCameraActor(const String& name);
   	    Actor* createMeshActor(const String& name,const String& meshname,
			PhysicsManager::GeometryTypes geomType = PhysicsManager::GT_NONE,
			Ogre::Real density = 1.0);
        Actor* createParticleSystemActor(const String& name, 
            const String& partname);
            
        void destroyActor(Actor* actor);
        
        ///@warning Actors with a camera attached wont be destroyed. 
		///@todo Check for active Viewport, and disable that first
        void destroyAllActors();

        void setWorld(World* world);
		const World* const getWorld() const;

		void collideWithActors(OgreOde::Geometry* geometry, OgreOde::CollisionListener* listener = 0);
		bool collision(OgreOde::Contact* contact);

		Actor* getActorAt(Ogre::Real x, Ogre::Real y, Ogre::Real width, Ogre::Real length, bool infinite = false);

        /** Returns the Singleton */
	    static ActorManager & getSingleton(void);
	    static ActorManager * getSingletonPtr(void);

    private:
        String nextUniqueName(const String& basename);
        ActorPtrMap mActors;
		OgreOde::Space* mActorOdeSpace;
		OgreOde::Geometry* mSelectionCapsule;
		std::vector<Actor*> mSelectableObjects;

        World* mWorld;
};

}
#endif
