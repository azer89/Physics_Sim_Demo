

#ifndef __Vehicle_h_
#define __Vehicle_h_

#include "Ogre.h"
#include "Character.h"
#include "LinearMath/btVector3.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"
#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"
#include "OgreBulletDynamicsRigidBody.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

// Car
class Vehicle : public Character
{
public:
	Vehicle(void);
	virtual ~Vehicle(void);

	void createObject(SceneManager* mSceneMgr,
		OgreBulletDynamics::DynamicsWorld *mBulletWorld,
		size_t &mNumEntitiesInstanced,
		Camera* mCamera);

	void setVisible (bool visible);
	Vector3 getObjectPosition();

	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);

public:
	Vector3 CarPosition;
	SceneNode *vehicleNode;
	Ogre::Real speed;

	OgreBulletDynamics::RaycastVehicle	        *mVehicle;

private:	
	OgreBulletDynamics::WheeledRigidBody        *mCarChassis;
	OgreBulletDynamics::VehicleTuning	        *mTuning;
	OgreBulletDynamics::VehicleRayCaster	    *mVehicleRayCaster;

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

#endif