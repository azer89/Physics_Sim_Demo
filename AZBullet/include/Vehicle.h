

#ifndef __Vehicle_h_
#define __Vehicle_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class Vehicle : public Character
{
public:
	Vehicle(void);
	virtual ~Vehicle(void);

	void createVehicle(SceneManager* mSceneMgr,
		OgreBulletDynamics::DynamicsWorld *mBulletWorld,
		size_t &mNumEntitiesInstanced,
		Camera* mCamera);

	void setVisible (bool visible);

	void updatePerFrame(Real elapsedTime);
	void keyPressed(const OIS::KeyEvent& arg);
	void keyReleased(const OIS::KeyEvent& arg);

public:
	Vector3 CarPosition;
	SceneNode *vehicleNode;

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

#endif