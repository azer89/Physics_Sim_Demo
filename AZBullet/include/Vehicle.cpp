
#include "Stdafx.h"
#include "Vehicle.h"

#include "OgreBulletListener.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

static float gMaxEngineForce = 3000.f;

static float gSteeringIncrement = 0.04f;
static float gSteeringClamp = 0.8f;

static float gWheelRadius = 0.5f;
static float gWheelWidth = 0.4f;

static float gWheelFriction = 1e30f;//1000;//1e30f;
static float gSuspensionStiffness = 20.f;
static float gSuspensionDamping = 2.3f;
static float gSuspensionCompression = 4.4f;

static float gRollInfluence = 1.0f;
static float gSuspensionRestLength = 0.6;
static float gMaxSuspensionTravelCm = 500.0;
static float gFrictionSlip = 10.5;

#define CUBE_HALF_EXTENTS 1

//-------------------------------------------------------------------------------------
// constructor
Vehicle::Vehicle(void)
{
	this->CarPosition =  Ogre::Vector3(15, 3,-15);
}
//-------------------------------------------------------------------------------------
// destructor
Vehicle::~Vehicle(void)
{
}

//-------------------------------------------------------------------------------------
// init function to create terrain
void Vehicle::createVehicle(SceneManager* mSceneMgr,
							OgreBulletDynamics::DynamicsWorld *mBulletWorld,
							size_t &mNumEntitiesInstanced,
							Ogre::Vector3 terrain_Shift)
{
	// reset
	for (int i = 0; i < 4; i++)
	{
		mWheelsEngine[i] = 0;
		mWheelsSteerable[i] = 0;
	}

	mWheelsEngineCount = 2;
	mWheelsEngine[0] = 0;
	mWheelsEngine[1] = 1;
	mWheelsEngine[2] = 2;
	mWheelsEngine[3] = 3;

	mWheelsSteerableCount = 2;
	mWheelsSteerable[0] = 0;
	mWheelsSteerable[1] = 1;

	mWheelEngineStyle = 0;
	mWheelSteeringStyle = 0;

	mSteeringLeft = false;
	mSteeringRight = false;

	mEngineForce = 0;
	mSteering = 0;

	const Ogre::Vector3 chassisShift(0, 1.0, 0);
	float connectionHeight = 0.7f;

	mChassis = mSceneMgr->createEntity(
		"chassis" + StringConverter::toString(mNumEntitiesInstanced++),
		"Nissan_1400_Bakkie.mesh");

	vehicleNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();

	SceneNode *chassisnode = vehicleNode->createChildSceneNode ();
	chassisnode->attachObject (mChassis);
	chassisnode->setPosition (chassisShift);

	mChassis->setCastShadows(true);

	CompoundCollisionShape* compound = new CompoundCollisionShape();

	BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	compound->addChildShape(chassisShape, chassisShift); 

	mCarChassis = new WheeledRigidBody("carChassis", mBulletWorld);

	mCarChassis->setShape (vehicleNode, 
		compound, 
		0.6, //restitution
		0.6, //friction
		800, //bodyMass
		CarPosition +  terrain_Shift, 
		Quaternion::IDENTITY);
	mCarChassis->setDamping(0.2, 0.2);

	mCarChassis->disableDeactivation ();
	mTuning = new VehicleTuning(
		gSuspensionStiffness,
		gSuspensionCompression,
		gSuspensionDamping,
		gMaxSuspensionTravelCm,
		gFrictionSlip);

	mVehicleRayCaster = new VehicleRayCaster(mBulletWorld);
	mVehicle = new RaycastVehicle(mCarChassis, mTuning, mVehicleRayCaster);

	int rightIndex = 0;
	int upIndex = 1;
	int forwardIndex = 2;

	mVehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

	Ogre::Vector3 wheelDirectionCS0(0,-1,0);
	Ogre::Vector3 wheelAxleCS(-1,0,0);

	for (size_t i = 0; i < 4; i++)
	{
		mWheels[i] = mSceneMgr->createEntity(
			"wheel" + StringConverter::toString(mNumEntitiesInstanced++),
			"wheel.mesh");

		mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);

		mWheels[i]->setCastShadows(true);

		mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
		mWheelNodes[i]->attachObject (mWheels[i]);

	}

	bool isFrontWheel = true;

	Ogre::Vector3 connectionPointCS0 (
		CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
		connectionHeight,
		2*CUBE_HALF_EXTENTS-gWheelRadius);


	mVehicle->addWheel(
		mWheelNodes[0],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3(
		-CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
		connectionHeight,
		2*CUBE_HALF_EXTENTS-gWheelRadius);


	mVehicle->addWheel(
		mWheelNodes[1],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);


	connectionPointCS0 = Ogre::Vector3(
		-CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
		connectionHeight,
		-2*CUBE_HALF_EXTENTS+gWheelRadius);

	isFrontWheel = false;
	mVehicle->addWheel(
		mWheelNodes[2],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3(
		CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
		connectionHeight,
		-2*CUBE_HALF_EXTENTS+gWheelRadius);

	mVehicle->addWheel(
		mWheelNodes[3],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);
}


//-------------------------------------------------------------------------------------
// update per frame
void Vehicle::updatePerFrame(Real elapsedTime)
{
	// apply engine Force on relevant wheels
	for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++)
	{
		mVehicle->applyEngineForce (mEngineForce, mWheelsEngine[i]);
	}

	if (mSteeringLeft)
	{
		mSteering += gSteeringIncrement;
		if (mSteering > gSteeringClamp)
			mSteering = gSteeringClamp;
	}
	else if (mSteeringRight)
	{
		mSteering -= gSteeringIncrement;
		if (mSteering < -gSteeringClamp)
			mSteering = -gSteeringClamp;
	}

	// apply Steering on relevant wheels
	for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	{
		if (i < 2) mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
		else mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
	}

}

//-------------------------------------------------------------------------------------
// when key pressed
void Vehicle::keyPressed(const OIS::KeyEvent& arg)
{
	bool wheel_engine_style_change = false;
	bool wheel_steering_style_change = false;

	if(arg.key == OIS::KC_PGUP)
	{
		wheel_engine_style_change = true;
		mWheelEngineStyle = (mWheelEngineStyle + 1) % 3;
	}
	else if(arg.key == OIS::KC_PGDOWN)
	{
		wheel_engine_style_change = true;
		mWheelEngineStyle = (mWheelEngineStyle - 1) % 3;
	}
	else if(arg.key == OIS::KC_HOME)
	{
		wheel_steering_style_change = true;
		mWheelSteeringStyle = (mWheelSteeringStyle + 1) % 3;
	}
	else if(arg.key == OIS::KC_END)
	{
		wheel_steering_style_change = true;
		mWheelSteeringStyle = (mWheelSteeringStyle - 1) % 3;;
	}
	else if(arg.key == OIS::KC_LEFT)
	{
		mSteeringLeft = true;
	}
	else if(arg.key == OIS::KC_RIGHT)
	{
		mSteeringRight = true;
	}
	else if(arg.key == OIS::KC_DOWN)
	{
		mEngineForce = -gMaxEngineForce;
	}
	else if(arg.key == OIS::KC_UP)
	{
		mEngineForce = gMaxEngineForce;
	}

	if (wheel_engine_style_change)
	{
		for (int i = 0; i < 4; i++)
			mWheelsEngine[i] = 0;

		if (mWheelEngineStyle < 0)
			mWheelEngineStyle = 2;

		switch (mWheelEngineStyle)
		{
		case 0://front
			mWheelsSteerableCount = 2;
			mWheelsSteerable[0] = 0;
			mWheelsSteerable[1] = 1;  
			break;
		case 1://back
			mWheelsSteerableCount = 2;
			mWheelsSteerable[0] = 2;
			mWheelsSteerable[1] = 3;  
			break;
		case 2://4x4
			mWheelsSteerableCount = 4;
			mWheelsSteerable[0] = 0;
			mWheelsSteerable[1] = 1;  
			mWheelsSteerable[2] = 2;
			mWheelsSteerable[3] = 3; 
			break;
		default:
			assert(0);
			break;
		}
	}

	if (wheel_steering_style_change)
	{
		for (int i = 0; i < 4; i++)
			mWheelsSteerable[i] = 0;

		if (mWheelSteeringStyle < 0)
			mWheelSteeringStyle = 2;

		switch (mWheelSteeringStyle)
		{
		case 0://front
			mWheelsEngineCount = 2;
			mWheelsEngine[0] = 0;
			mWheelsEngine[1] = 1;  
			break;
		case 1://back
			mWheelsEngineCount = 2;
			mWheelsEngine[0] = 2;
			mWheelsEngine[1] = 3;  
			break;
		case 2://4x4
			mWheelsEngineCount = 4;
			mWheelsEngine[0] = 0;
			mWheelsEngine[1] = 1;  
			mWheelsEngine[2] = 2;
			mWheelsEngine[3] = 3; 
			break;
		default:
			assert(0);
			break;
		}
	}
}

//-------------------------------------------------------------------------------------
// when key released
void Vehicle::keyReleased(const OIS::KeyEvent& arg)
{
	if(arg.key == OIS::KC_LEFT) 
	{
		mSteeringLeft = false;
	}
	else if(arg.key == OIS::KC_RIGHT)
	{
		mSteeringRight = false;
	}
	else if(arg.key == OIS::KC_DOWN)
	{
		mEngineForce = 0;
	}
	else if(arg.key == OIS::KC_UP)
	{
		mEngineForce = 0;
	}
}
