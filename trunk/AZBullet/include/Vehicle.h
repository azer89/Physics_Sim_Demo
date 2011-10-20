#include "Stdafx.h"

#include "ClassDefine.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class Vehicle
{
public:
	Vehicle(void);
	virtual ~Vehicle(void);

	void createVehicle(SceneManager* mSceneMgr,
		OgreBulletDynamics::DynamicsWorld *mBulletWorld,
		size_t &mNumEntitiesInstanced,
		Ogre::Vector3 terrain_Shift);

	void updatePerFrame(Real elapsedTime);
	void keyPressed(const OIS::KeyEvent& arg);
	void keyReleased(const OIS::KeyEvent& arg);

public:
	Vector3 CarPosition;

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
	
};