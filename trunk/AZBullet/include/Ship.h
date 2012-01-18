
#ifndef __Ship_h_
#define __Ship_h_

#include "Ogre.h"
#include "Character.h"
#include "CollisionDetectorTool.h"
#include "Hydrax.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"
#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "LinearMath/btVector3.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class Ship : public Character
{
private:	
	OgreBulletDynamics::WheeledRigidBody	*mRobotChassis;
	OgreBulletDynamics::VehicleTuning		*mTuning;
	OgreBulletDynamics::VehicleRayCaster	*mVehicleRayCaster;

	Ogre::Entity    *shipEntity;
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

	RigidBody *shipRigidBody;

protected:
	Ogre::Real defaultHeight;

public:
	Hydrax::Hydrax *mHydrax;
	SceneNode *shipNode;
	Vector3 shipPosition;
	Quaternion shipRotation;
	SceneNode *vehicleNode;
	OgreBulletDynamics::RaycastVehicle		*mVehicle;

	Ship(void);
	virtual ~Ship(void);

	//void createObject(OgreBulletListener *bulletListener, Hydrax::Hydrax *mHydrax, size_t &mNumEntitiesInstanced);
	void createObject(SceneManager* mSceneMgr, OgreBulletDynamics::DynamicsWorld *mBulletWorld,	size_t &mNumEntitiesInstanced);
	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);
};

#endif