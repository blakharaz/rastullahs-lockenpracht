/* This source file is part of Rastullahs Lockenpracht.
 * Copyright(C) 2003-2007 Team Pantheon. http://www.team-pantheon.de
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
#include "stdinc.h"

#include "SteeringVehicle.h"

#include "AiSubsystem.h"
#include "AiWorld.h" 
#include "Agent.h"
#include "Actor.h"
#include "Creature.h"
#include "CreatureController.h"
#include "CreatureControllerManager.h"
#include "MeshObject.h"
#include "CreatureController.h"
#include "PhysicalThing.h"

using namespace Ogre;
using namespace OpenSteer;

namespace rl {

SteeringVehicle::SteeringVehicle(Creature* creature)
	: _maxForce(1.0f),
      _maxSpeed(1.0f),
      mSpeed(1.0f),
	  mCurrentForce(Vector3::ZERO), 
	  mCurrentVelocity(Vector3::ZERO),
	  mForwardVector(Vector3::NEGATIVE_UNIT_Z),
	  mCreature(creature),
      mController(NULL),
      mDebugSteer(Vector3::ZERO),
      mDebugWander(Vector3::ZERO),
      mDebugAvoidObstacles(Vector3::ZERO)
{
	initialize();
    mController = CreatureControllerManager::getSingleton().getCreatureController(
        mCreature);
}

SteeringVehicle::~SteeringVehicle()
{
}

void SteeringVehicle::resetLocalSpace()
{
	setForward(mForwardVector);
	setSide(localRotateForwardToSide(getForward()));
    setUp(Vector3::UNIT_Y);
	Vector3 pos = mCreature->getPosition();
	setPosition(pos);
	Vector3 src = mCreature->getOrientation()*Vector3::NEGATIVE_UNIT_Z;

    // regenerate local space(by default: align vehicle's forward axis with
    // new velocity, but this behavior may be overridden by derived classes.)
	regenerateOrthonormalBasisUF(src);
}

void SteeringVehicle::initialize()
{
    // reset LocalSpace state
	resetLocalSpace();
	
    // reset SteerLibraryMixin state
	SimpleVehicle_2::reset();

	setMaxForce(1.0f);   // steering force is clipped to this magnitude
	setMaxSpeed(1.0f);   // velocity is clipped to this magnitude
}

void SteeringVehicle::addForce(const Ogre::Vector3& force)
{
	mCurrentForce += force;
}

void SteeringVehicle::update(const float currentTime, const float elapsedTime)
{
    // from PlayerVehicle
    // since physics schould by handled by movingcreature

	OgreNewt::Body* body = mCreature->getActor()->getPhysicalThing()->_getBody();

	setPosition(mCreature->getPosition());

    //  Get the velocity vector
	mCurrentVelocity = body->getVelocity();
	//  enforce speed limit
	//  newVelocity = newVelocity.truncateLength(maxSpeed());
	//  update speed
	setSpeed(mCurrentVelocity.length());
	Vector3 newVelocity(mCurrentVelocity);

    //  regenerate local space(by default: align vehicle's forward axis with
    //  new velocity, but this behavior may be overridden by derived classes.)
    // use future orientation or not??
    Quaternion orientation(mController->getYaw(), Ogre::Vector3::UNIT_Y);
    Vector3 newUnitForward = orientation*Vector3::NEGATIVE_UNIT_Z;
    regenerateOrthonormalBasisUF(newUnitForward);

    // end of inserting from playervehicle



    // only process if mMovingCreature not NULL
    if (mController == NULL)
    {
        mCurrentForce = Vector3::ZERO;
        return;
    }
    
// calculate the result of the force    
    Vector3 result = mCurrentForce;// + mCurrentVelocity;

     mDebugSteer = mCurrentForce;

    // @todo remove this
    if (mCreature->getAu() <= 6)
        mCreature->modifyAu(20,true);


    AbstractMovement *mov_drehen = mController->getMovementFromId(CreatureController::MT_DREHEN);
    Real vel_drehen(0);
    Radian max_drehen = Degree(0);
    if (mov_drehen->calculateBaseVelocity(vel_drehen))
    {
        max_drehen = Degree(vel_drehen * 360 * elapsedTime);
    }

    Ogre::Quaternion future_orientation(mController->getYaw(), Ogre::Vector3::UNIT_Y);
    Ogre::Vector3 creatureDirection = future_orientation * Ogre::Vector3::NEGATIVE_UNIT_Z;
    Radian yaw(0);
    creatureDirection.y = result.y = 0;
    yaw = creatureDirection.getRotationTo(result, Ogre::Vector3::UNIT_Y).getYaw();
    if (yaw > Radian(0) && yaw > max_drehen)
        yaw = max_drehen;
    if (yaw < Radian(0) && yaw < -max_drehen)
        yaw = -max_drehen;

    Ogre::Vector3 direction(Ogre::Vector3::ZERO);
    Ogre::Vector3 rotation(0,yaw.valueRadians(),0);
    CreatureController::MovementType movement = CreatureController::MT_STEHEN;
    if (result != Ogre::Vector3::ZERO)
    {
        direction.z = -1;
        movement = CreatureController::MT_GEHEN;
    }


    mController->setMovement(movement, direction, rotation);
    LOG_MESSAGE("mController->setMovement",
        Ogre::StringConverter::toString(movement) + ", "
        + Ogre::StringConverter::toString(direction) + ", "
        + Ogre::StringConverter::toString(rotation));

	mCurrentForce = Ogre::Vector3::ZERO;
}

Vector3 SteeringVehicle::calcWander(const float elapsedTime)
{
	Vector3 steering = mForwardVector;
	
    steering += Vec3Utils::setYtoZero(steerForWander(elapsedTime/12.0f));

    mDebugWander = steering;
	return steering;
}

Vector3 SteeringVehicle::calcSeek(const Vector3& target)
{
	Vector3 steering = Vec3Utils::setYtoZero(steerForSeek(target));
	return steering;
}

Vector3 SteeringVehicle::calcFlee(const Vector3& target)
{
	Vector3 steering = Vec3Utils::setYtoZero(steerForFlee(target));
	return steering;
}

Vector3 SteeringVehicle::calcPursuit(Agent* agent)
{
    Vector3 dir = Vec3Utils::setYtoZero(steerForPursuit(*agent));
	return dir;
}

Vector3 SteeringVehicle::calcAvoidObstacles(const float minTimeToCollision)
{
    ObstacleGroup obstacles = getObstacles();
    Vector3 steering = Vec3Utils::setYtoZero(steerToAvoidObstacles(minTimeToCollision, obstacles));
    mDebugAvoidObstacles = steering;
	return steering;
}

Vector3 SteeringVehicle::calcAvoidNeighbors(const float minTimeToCollision)
{
	Vector3 steering = Vec3Utils::setYtoZero(steerToAvoidNeighbors(minTimeToCollision, getNeighbors()));
	return steering;
}
		
Vector3 SteeringVehicle::calcSteerTargetSpeed(const float targetSpeed)
{
	return Vector3();
}

bool SteeringVehicle::isAhead(Agent* agent, const float threshold)
{
    Vector3 target = agent->getControlledCreature()->getPosition();
	//target.y = position.y;
	return SimpleVehicle_2::isAhead(target, threshold);
}

bool SteeringVehicle::needAvoidance(const float minTimeToCollision)
{
	Vector3 rVal = calcAvoidNeighbors(minTimeToCollision) + calcAvoidObstacles(minTimeToCollision);
	if (rVal == Vector3::ZERO)
	{
		return false;
	}
	return true;
}

AVGroup SteeringVehicle::getNeighbors() const
{
	AVGroup group;
	//AgentManager::VehicleList list = AgentManager::getSingleton().getNeighbors(NULL);
	//AgentManager::VehicleList::const_iterator itr = list.begin();
	//for(; itr != list.end(); ++itr)
	//{
	//	if ((*itr) != this)
	//	{
	//		group.push_back((*itr));
	//	}
	//}
	return group;
}

float SteeringVehicle::calcDistance(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 vec = vec1-vec2;
	return vec.length();
}

Vector3 SteeringVehicle::getPosition()
{
	return mCreature->getPosition();
}

float SteeringVehicle::getMass() const 
{
    return mCreature->getMass();
}

float SteeringVehicle::setMass(float m) 
{
	// don't set mass here TODO: throw exception

	return 1;
} 

float SteeringVehicle::getSpeed() const 
{
	return mSpeed;
}

float SteeringVehicle::setSpeed(float s) 
{
	return 1;
}

float SteeringVehicle::getRadius() const 
{
	// this is only the radius in x axis, but i think, this is the value that should be used here
    Ogre::AxisAlignedBox aab = mCreature->getActor()->getPhysicalThing()->_getBody()->getCollision()->getAABB();
    return(aab.getMaximum().x - aab.getMinimum().x)/2;
}

float SteeringVehicle::setRadius(float m) 
{
	// don't set mass here TODO: throw exception
	return 1;
}

float SteeringVehicle::getHeight() const 
{
    Ogre::AxisAlignedBox aab = mCreature->getActor()->getPhysicalThing()->_getBody()->getCollision()->getAABB();
    return aab.getMaximum().y - aab.getMinimum().y;
}

float SteeringVehicle::setHeight(float h) 
{
	// don't set mass here TODO: throw exception
	return 1;
}

const Actor* SteeringVehicle::getActor() const  
{ 
	return mCreature->getActor(); 
}

float SteeringVehicle::getMaxForce() const 
{
	return 10000.0f;
} 

float SteeringVehicle::setMaxForce(float mf) 
{
	 // TODO: should not be set here, throw excpetion or so
	return _maxForce = mf;
}

float SteeringVehicle::getMaxSpeed() const 
{
	return mController->getMaximumSpeed();
}

float SteeringVehicle::setMaxSpeed(float ms) 
{
	 // TODO: should not be set here, throw excpetion or so
	return 1;
}

const ObstacleGroup& SteeringVehicle::getObstacles() const
{
	return AiSubsystem::getSingleton().getWorld()->getSteeringObstacles();
}

Vector3 SteeringVehicle::predictFuturePosition(const float predictionTime) const
{
	//return position() +(velocity() * predictionTime);
	return getVelocity() * predictionTime;
}

Vector3 SteeringVehicle::adjustRawSteeringForce(const Vector3& force)
{
    const float maxAdjustedSpeed = 0.2f * getMaxSpeed();

    if ((getSpeed() > maxAdjustedSpeed) ||(force == Vector3::ZERO))
    {
        return force;
    }
    else
    {
        const float range = getSpeed() / maxAdjustedSpeed;
        // const float cosine = interpolate(pow(range, 6), 1.0f, -1.0f);
        // const float cosine = interpolate(pow(range, 10), 1.0f, -1.0f);
        // const float cosine = interpolate(pow(range, 20), 1.0f, -1.0f);
        // const float cosine = interpolate(pow(range, 100), 1.0f, -1.0f);
        // const float cosine = interpolate(pow(range, 50), 1.0f, -1.0f);
        const float cosine = interpolate(pow(range, 20), 1.0f, -1.0f);
        return limitMaxDeviationAngle(force, cosine, getForward());
    }
}

// methods from debugvisualisable
DebugVisualisableFlag SteeringVehicle::getFlag() const
{
    return DVF_BOT;
}

void SteeringVehicle::updatePrimitive()
{
    if (mSceneNode->getParent() == NULL)
    {
        mCreature->getActor()->_getSceneNode()->addChild(mSceneNode);
    }

    LineSetPrimitive* lineSet = static_cast<LineSetPrimitive*>(mPrimitive);
    lineSet->clear();
    
    if (mDebugSteer != Vector3::ZERO)
    {
        lineSet->addLine(Vector3::UNIT_Y*2, Vector3::UNIT_Y*2 + mDebugSteer.normalisedCopy()*0.5, ColourValue::Black);
        mDebugSteer = Vector3::ZERO;
    }
    if (mDebugWander != Vector3::ZERO)
    {
        lineSet->addLine(Vector3::UNIT_Y*2, Vector3::UNIT_Y*2 + mDebugWander.normalisedCopy()*0.5, ColourValue::Green);
        mDebugWander = Vector3::ZERO;
    }
    if (mDebugAvoidObstacles != Vector3::ZERO)
    {
        lineSet->addLine(Vector3::UNIT_Y*2, Vector3::UNIT_Y*2 + mDebugAvoidObstacles.normalisedCopy()*0.5, ColourValue::Red);
        mDebugAvoidObstacles = Vector3::ZERO;
    }
}

void SteeringVehicle::doCreatePrimitive()
{
    mPrimitive = new LineSetPrimitive();
}

} // namespace rl
