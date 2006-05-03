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

#include "Exception.h"
#include "MeshObject.h"
#include "Actor.h"
#include "CoreSubsystem.h"
#include "World.h"

#include "MeshAnimation.h"
#include "AnimationManager.h"

#include <OgreMeshManager.h>
#include <OgreAnimationState.h>

using namespace Ogre;

namespace rl {
	MeshObject::MeshObject(const String& name, const String& meshname) : mSize(), mPoseSizes()
    {
		if (meshname.length() > 0)
		{
			Entity* entity = CoreSubsystem::getSingletonPtr()->getWorld()
				->getSceneManager()->createEntity(name, meshname);
            if (entity->isHardwareAnimationEnabled())
            {
                for (unsigned int i = 0; i < entity->getNumSubEntities(); ++i)
                {
                    SubEntity* se = entity->getSubEntity(i);
                    se->setCustomParameter(0, Vector4(0, 0, 0, 0));
                }
            }
            mMovableObject = entity;
			mSize = calculateSize();
		}
    }

	MeshObject::~MeshObject()
	{
        stopAllAnimations();
		CoreSubsystem::getSingletonPtr()->getWorld()
			->getSceneManager()->destroyEntity( getEntity() );		
	}

    Entity* MeshObject::getEntity() const
    {
        return reinterpret_cast<Entity*>(mMovableObject);
    }

    AxisAlignedBox MeshObject::getDefaultSize() const
    {
        return mSize;
    }
    
    AxisAlignedBox MeshObject::getPoseSize(const String& animationName)
	{
		PoseMap::iterator it = mPoseSizes.find(animationName);
		if (it == mPoseSizes.end())
		{
			// Not yet calculated. Do so now and save.
            AxisAlignedBox rval = calculateSizeFromPose(animationName);
			mPoseSizes.insert(make_pair(animationName, rval));
			return rval;
		}
		else
		{
			return it->second;
		}
	}

	/// @todo Exception Handling
	MeshAnimation* MeshObject::getAnimation(const String& animName)
	{
        MeshAnimation* anim = NULL;

		try
		{
			AnimationState* animState = getEntity()->getAnimationState(animName);
			anim = dynamic_cast<MeshAnimation*>
                (AnimationManager::getSingleton().getAnimation(animState));
            if( anim == NULL )
                anim = dynamic_cast<MeshAnimation*>(
                AnimationManager::getSingleton().addMeshAnimation(animState,this,1.0,0,true));
		}
		catch(Ogre::Exception&) 
		{
		}

		return anim;
	}


	MeshAnimation* MeshObject::startAnimation(const String& animName,
		Real speed, unsigned int timesToPlay )
	{
		try
		{
			AnimationState* animState = getEntity()->getAnimationState(animName);
			return AnimationManager::getSingleton().addMeshAnimation(
				animState, this, speed, timesToPlay);
		}
		catch(Ogre::Exception&) 
		{
		}

		return 0;
	}

	MeshAnimation* MeshObject::replaceAnimation(const String& oldAnimName,
		const String& newAnimName, Real speed, unsigned int timesToPlay )
	{
        stopAnimation(oldAnimName);
        return startAnimation( newAnimName, speed, timesToPlay );
	}

	void MeshObject::stopAnimation(const String& animName)
	{
		try
		{
			AnimationState* animState = getEntity()->getAnimationState(animName);
			AnimationManager::getSingleton().removeAnimation(animState);
		}
		catch(Ogre::Exception&) 
		{ 
		}
	}
    
	void MeshObject::stopAllAnimations( )
	{
			AnimationStateSet* animStates = getEntity()->getAllAnimationStates();
			if (animStates != NULL)
			{
				AnimationStateIterator iter = animStates->getAnimationStateIterator();

				while(iter.hasMoreElements()) 
				{
					AnimationState* state = iter.getNext(); 
					stopAnimation( state->getAnimationName() );
				} 
			}
	}


    String MeshObject::getObjectType()
    {
        return "MeshObject";
    }

    bool MeshObject::getBlendCumulative(void) const
    {
        if( getEntity()->hasSkeleton() )
        {
            if( getEntity()->getSkeleton()->getBlendMode() 
                == ANIMBLEND_CUMULATIVE  )
                return true;
            else
                return false;
        }

        return false;
    }
    
    void MeshObject::setBlendCumulative(bool cumulative)
    {
        if( getEntity()->hasSkeleton() )
        {
            if( cumulative )
                getEntity()->getSkeleton()->
                setBlendMode(ANIMBLEND_CUMULATIVE);
            else
                getEntity()->getSkeleton()->
                setBlendMode(ANIMBLEND_AVERAGE);
        }
    }
    
    AxisAlignedBox MeshObject::calculateSize()
    {
        const AxisAlignedBox& aabb = getEntity()->getBoundingBox();
        Vector3 x = aabb.getMaximum();
        Vector3 n = aabb.getMinimum();
        Vector3 scaler = (x - n) * MeshManager::getSingleton().getBoundsPaddingFactor();
        AxisAlignedBox rval = AxisAlignedBox(n + scaler, x - scaler);
        return rval;
    }

    AxisAlignedBox MeshObject::calculateSizeFromPose(const String& animationName)
	{
		Entity* entity = getEntity();
		AnimationStateSet* ass = entity->getAllAnimationStates();

		// Test if wanted anim is available for the entity
		if (!ass->hasAnimationState(animationName))
		{
			Throw(IllegalArgumentException, String("No animation " + animationName +
				" for entity " + entity->getName()));
		}

		// Save current animation state set. We don't want to interfere with the visible anim.
		AnimationStateSet* saveAss = new AnimationStateSet(*ass);

		// Deactivate all anims, save the wanted one.
		AnimationStateIterator it = ass->getAnimationStateIterator();
		while (it.hasMoreElements())
		{
			AnimationState* as = it.peekNextValue();
			as->setEnabled(as->getAnimationName() == animationName);
			it.moveNext();
		}

		// Issue a software skinning request,
		// update the animation and then remove the software request
		// Actually this doesn't work, if animation has been updated already in this frame,
		// but this restriction can't be circumvented easily.
		entity->addSoftwareAnimationRequest(false);
		entity->_updateAnimation();

        AxisAlignedBox aabb = AxisAlignedBox(Vector3::ZERO, Vector3::ZERO);
        if (entity->getMesh()->sharedVertexData)
        {
		    aabb.merge(getAabbFromVertexData(entity->_getSkelAnimVertexData()));
        }
		for (unsigned int i = 0; i < entity->getNumSubEntities(); ++i)
		{
			SubEntity* se = entity->getSubEntity(i);
            if (se->getSubMesh()->vertexData)
            {
			    aabb.merge(getAabbFromVertexData(se->_getSkelAnimVertexData()));
            }
		}

		entity->removeSoftwareAnimationRequest(false);

		return aabb;
	}

	AxisAlignedBox MeshObject::getAabbFromVertexData(VertexData* vd)
	{
        AxisAlignedBox aabb = AxisAlignedBox(Vector3::ZERO, Vector3::ZERO);

		const VertexElement* ve = vd->vertexDeclaration->findElementBySemantic(VES_POSITION);
		HardwareVertexBufferSharedPtr vb = vd->vertexBufferBinding->getBuffer(ve->getSource());

		unsigned char* data = static_cast<unsigned char*>(
			vb->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		
		for (size_t i = 0; i < vd->vertexCount; ++i)
		{
			float* v;
			ve->baseVertexPointerToElement(data, &v);
			aabb.merge(Vector3(v[0], v[1], v[2]));

			data += vb->getVertexSize();
		}
		vb->unlock();

		return aabb;
    }
    
    void MeshObject::setCastShadows (bool enabled)
    {
        getEntity()->setCastShadows(enabled);
    }

    bool MeshObject::getCastShadows (void) const
    {
        return getEntity()->getCastShadows();
    }

    void MeshObject::setHighlighted( bool highlight )
    {
        String nameExtension = "_HighLight";
        Entity* ent = getEntity();
        int numEnts = ent->getNumSubEntities();

        for( int i = 0; i < numEnts; i++ )
        {
            SubEntity* subent = ent->getSubEntity(i);

            if( subent == NULL )
                continue;

            // TODO - optimieren, nur wenn der Typ ver�ndert wird
            //if(StringUtil::endsWith(subent->getMaterialName(),nameExtension)
            // == highlight )
            //  continue;  

            if (ent->isHardwareAnimationEnabled())
            {
                subent->setCustomParameter(0,
                    highlight ? Vector4(1, 1, 1, 1) : Vector4(0, 0, 0, 0));
            }

            MaterialPtr oldMaterial = subent->getMaterial();

            // Highlight setzen
            if( highlight )
            {           	 
                MaterialPtr material = MaterialManager::getSingleton().getByName( oldMaterial->getName()+nameExtension );

                if( material.isNull() )
                {
                    material = oldMaterial->clone( oldMaterial->getName()+nameExtension );

                    material->setAmbient(1.0, 1.0, 1.0);
                    material->setDiffuse(1.0, 1.0, 1.0, 1.0);
                    material->setSelfIllumination(0.4, 0.4, 0.4); 
                }

                subent->setMaterialName(material->getName());
            }
            // Highlight entfernen
            else
            {
                String matName = oldMaterial->getName();
                matName = matName.erase(matName.length() - nameExtension.length(), nameExtension.length() );
                subent->setMaterialName( matName );				
            }


        }
    }

	bool MeshObject::isMeshObject()
	{
		return true;
	}
}
