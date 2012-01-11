

#ifndef __Robot_h_
#define __Robot_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

enum RobotState
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	NOT_MOVE
};

class Robot : public Character
{
private:	
	OgreBulletDynamics::WheeledRigidBody        *mCarChassis;
	OgreBulletDynamics::VehicleTuning	        *mTuning;
	OgreBulletDynamics::VehicleRayCaster	    *mVehicleRayCaster;
	OgreBulletDynamics::RaycastVehicle	        *mVehicle;

	Ogre::Entity    *mChassis;
	Ogre::Entity    *mWheels[4];
	Ogre::SceneNode *mWheelNodes[4];	

	int mWheelsEngine[4];
	int mWheelsEngineCount;
	int mWheelsSteerable[4];
	int mWheelsSteerableCount;

	float mEngineForce;
	float mSteering;

	int mWheelEngineStyle;
	int mWheelSteeringStyle;

	bool mSteeringLeft;
	bool mSteeringRight;

protected:
	RobotState robotState;
	Ogre::AnimationState* ani;
	Ogre::Vector3 direction;
	Ogre::Real speed;
	
public:
	SceneNode *robotNode;

	Vector3 CarPosition;
	SceneNode *vehicleNode;
	Ogre::Real speed;

public:
	Robot(void);
	virtual ~Robot(void);

	void createObject(SceneManager* mSceneMgr, 
		OgreBulletDynamics::DynamicsWorld *mBulletWorld,
		size_t &mNumEntitiesInstanced);

	void updatePerFrame(Real elapsedTime);
	void keyPressed(const OIS::KeyEvent& arg);
	void keyReleased(const OIS::KeyEvent& arg);
};

#endif