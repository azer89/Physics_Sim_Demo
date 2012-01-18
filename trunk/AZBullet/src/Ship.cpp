
#include "Stdafx.h"
#include "Ship.h"

static float gMaxEngineForce = 20000.f;

static float gSteeringIncrement = 0.04f;
static float gSteeringClamp = 0.2f;

static float gWheelRadius = 0.5f;
static float gWheelWidth = 0.4f;

static float gWheelFriction = 1e30f; //1000; //1e30f;
static float gSuspensionStiffness = 5.f;
static float gSuspensionDamping = 2.3f;
static float gSuspensionCompression = 4.4f;

static float gRollInfluence = 1.0f;
static float gSuspensionRestLength = 0.6;
static float gMaxSuspensionTravelCm = 500.0;
static float gFrictionSlip = 0.0;

#define CUBE_HALF_EXTENTS 1

//-------------------------------------------------------------------------------------
Ship::Ship(void)
{
	//speed = 1000.0f;

	mSteeringLeft = false;
	mSteeringRight = false;

	mEngineForce = 0;
	mSteering = 0;	

	this->shipPosition = Ogre::Vector3(-90, 7, 20);
	
	Ogre::Real degree = Ogre::Degree(-225).valueRadians();
	this->shipRotation = Quaternion(Math::Cos(degree/2), 0, Math::Sin(degree/2), 0);
}

//-------------------------------------------------------------------------------------
Ship::~Ship(void)
{
}

//-------------------------------------------------------------------------------------
void Ship::createObject(SceneManager* mSceneMgr, 
			 OgreBulletDynamics::DynamicsWorld *mBulletWorld,
			 size_t &mNumEntitiesInstanced)
{
	this->mHydrax = mHydrax;

	mWheelsEngineCount = 4;
	mWheelsEngine[0] = 0; mWheelsEngine[1] = 1; mWheelsEngine[2] = 2; mWheelsEngine[3] = 3;

	mWheelsSteerableCount = 4;
	mWheelsSteerable[0] = 0; mWheelsSteerable[1] = 1; mWheelsSteerable[2] = 2; mWheelsSteerable[3] = 3; 

	mWheelsSteerableCount = 2;
	mWheelsSteerable[0] = 0; mWheelsSteerable[1] = 1;

	const Ogre::Vector3 chassisShift(0, 1.0, 0);
	float connectionHeight = 0.7f;

	shipEntity = mSceneMgr->createEntity( "ShipEntity" + StringConverter::toString(mNumEntitiesInstanced++), "yatch.mesh");
	vehicleNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode();

	this->mMainNode = vehicleNode;
	Vector3 pos = this->mMainNode->_getDerivedPosition();

	SceneNode *chassisNode = vehicleNode->createChildSceneNode();
	chassisNode->setPosition (chassisShift);

	shipNode = chassisNode->createChildSceneNode("ShipNode");	
	shipNode->attachObject(shipEntity);
	shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(180).valueRadians()));
	shipNode->setScale(2.5, 2.5, 2.5);
	shipNode->translate(0, 45, 0);
	shipEntity->setQueryFlags (GEOMETRY_QUERY_MASK);
	shipEntity->setQueryFlags (1<<2);
	shipEntity->setCastShadows(false);

	// set up sight node	
	mSightNode = chassisNode->createChildSceneNode ("ShipSightNode", Vector3(0,50, 0));
	mCameraNode = chassisNode->createChildSceneNode ("ShipCameraNode", Vector3(-90, 175, -120));

	//ani = robotEntity->getAnimationState("walking");
	//ani->setEnabled(true);

	CompoundCollisionShape* compound = new CompoundCollisionShape();
	compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(10.0f, 0.5f, 35.0f)), chassisShift);							// base
	compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(4.0f, 3.0f, 8.0f)), chassisShift + Ogre::Vector3(0, 43.0, 30));
	compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(5.0f, 3.0f, 7.0f)), chassisShift + Ogre::Vector3(0, 43.0, -30));
	compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(11.0f, 3.0f, 25.0f)), chassisShift + Ogre::Vector3(0, 43.0, 0));	// body

	mRobotChassis = new WheeledRigidBody("ShipChassis", mBulletWorld);

	mRobotChassis->setShape (chassisNode, 
		compound, 
		0.0,				// restitution
		0.0f,				// friction
		1500,				// bodyMass
		this->shipPosition, 
		this->shipRotation);

	mRobotChassis->setDamping(0.2, 0.2);		// ratio effect
	mRobotChassis->disableDeactivation ();
		
	mTuning = new VehicleTuning( gSuspensionStiffness, gSuspensionCompression, gSuspensionDamping, gMaxSuspensionTravelCm, gFrictionSlip);

	mVehicleRayCaster = new VehicleRayCaster(mBulletWorld);
	mVehicle = new RaycastVehicle(mRobotChassis, mTuning, mVehicleRayCaster);
	mVehicle->setCoordinateSystem(0, 1, 2);	// rightIndex, upIndex, forwardIndex

	mRobotChassis->getBulletRigidBody()->setLinearFactor(btVector3(1, 1, 1));
	mRobotChassis->getBulletRigidBody()->setAngularFactor(btVector3(0.5, 0.5, 0.5));	

	for (size_t i = 0; i < 4; i++) 
	{ 
		mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();

		/*mWheels[i] = mSceneMgr->createEntity( "wheel" + StringConverter::toString(mNumEntitiesInstanced++), "wheel.mesh");
		mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
		mWheels[i]->setQueryFlags (1<<2);
		mWheels[i]->setCastShadows(false);

		mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
		mWheelNodes[i]->attachObject (mWheels[i]);*/
	
	}

	Ogre::Vector3 wheelDirectionCS0(0, -1, 0);
	Ogre::Vector3 wheelAxleCS(-1, 0, 0);

	mVehicle->addWheel(mWheelNodes[0],
		Ogre::Vector3 ( CUBE_HALF_EXTENTS + (10.0*gWheelWidth), connectionHeight, 20.0 * CUBE_HALF_EXTENTS - gWheelRadius),
		wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, true, gWheelFriction, gRollInfluence);

	mVehicle->addWheel(mWheelNodes[1],
		Ogre::Vector3( -CUBE_HALF_EXTENTS - (10.0*gWheelWidth), connectionHeight, 20.0 * CUBE_HALF_EXTENTS - gWheelRadius),
		wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, true, gWheelFriction, gRollInfluence);

	mVehicle->addWheel(mWheelNodes[2],
		Ogre::Vector3( -CUBE_HALF_EXTENTS - (10.0*gWheelWidth), connectionHeight, -20.0 * CUBE_HALF_EXTENTS + gWheelRadius),
		wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, false, gWheelFriction, gRollInfluence);

	mVehicle->addWheel(mWheelNodes[3],
		Ogre::Vector3( CUBE_HALF_EXTENTS + (10.0*gWheelWidth), connectionHeight, -20.0 * CUBE_HALF_EXTENTS + gWheelRadius),
		wheelDirectionCS0, wheelAxleCS,	gSuspensionRestLength,	gWheelRadius, false, gWheelFriction, gRollInfluence);

	mVehicle->getBulletVehicle()->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));

	this->defaultHeight = shipNode->getPosition().y;
}

//-------------------------------------------------------------------------------------
void Ship::updatePerFrame(Real elapsedTime)
{
	Ogre::Vector3 curPos = this->mMainNode->getPosition();

	if(mHydrax->isVisible())
	{
		Ogre::Real hydraxHeight = mHydrax->getHeigth(Ogre::Vector2(curPos.x, curPos.z));

		Ogre::Real diff = hydraxHeight - defaultHeight;
		Vector3 shipCurPos = shipNode->getPosition();
		shipNode->setPosition(shipCurPos.x, defaultHeight + (diff / 10.0f), shipCurPos.z);
		//std::cout << diff << "\n";

	}
	else
	{		
		Vector3 shipCurPos = shipNode->getPosition();
		shipNode->setPosition(shipCurPos.x, defaultHeight, shipCurPos.z);
	}


	Ogre::Real currentSpeed = mVehicle->getBulletVehicle()->getCurrentSpeedKmHour();

	// apply engine Force on relevant wheels
	for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++) 
	{
		Ogre::Real xFactor = 1.0f;
		if(currentSpeed < 100.0f && currentSpeed >= 0.0f) xFactor = 2.0f;
		if(currentSpeed > -100.0f && currentSpeed <= 0.0f) xFactor = -2.0f;

		mVehicle->applyEngineForce (mEngineForce , mWheelsEngine[i]); 

		if(mEngineForce == 0) 
		{
			if(currentSpeed > 20.0f || currentSpeed < -20.0f) mVehicle->getBulletVehicle()->setBrake(750, mWheelsEngine[i]);
			else if(currentSpeed >= 20.0f && currentSpeed >= -20.0f) mVehicle->getBulletVehicle()->setBrake(100, mWheelsEngine[i]);
			else if(currentSpeed < 2.0f && currentSpeed > -2.0f) mVehicle->getBulletVehicle()->setBrake(0, mWheelsEngine[i]);
		}
	}

	if (mSteeringLeft)
	{
		mSteering += gSteeringIncrement;
		if (mSteering > gSteeringClamp) mSteering = gSteeringClamp;
	}
	else if (mSteeringRight)
	{
		mSteering -= gSteeringIncrement;
		if (mSteering < -gSteeringClamp) mSteering = -gSteeringClamp;
	}
	else if(!mSteeringLeft && !mSteeringRight)
	{
		if(mSteering > 0)mSteering -= 0.01f;
		else if(mSteering < 0) mSteering += 0.01f;

		if(Math::Abs(mSteering) <= 0.1f) mSteering = 0.0f;
	}

	// apply Steering on relevant wheels
	for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	{
		if (i < 2) mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
		else mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
	}
}

//-------------------------------------------------------------------------------------
void Ship::keyPressed(const OIS::KeyEvent& arg)
{
	if(!isFocus) return;

	if(!isFocus)	return;

	bool wheel_engine_style_change = false;
	bool wheel_steering_style_change = false;
	bool isChangeDirection = false;

	if(arg.key == OIS::KC_LEFT)
	{
		mSteeringLeft = true;
		isChangeDirection = true;
	}
	else if(arg.key == OIS::KC_RIGHT)
	{
		mSteeringRight = true;
		isChangeDirection = true;
	}
	else if(arg.key == OIS::KC_DOWN) { mEngineForce = -gMaxEngineForce; }
	else if(arg.key == OIS::KC_UP) { mEngineForce = gMaxEngineForce; }

	if(!isChangeDirection)
	{
		mSteeringRight = false;
		mSteeringLeft = false;
	}
}

//-------------------------------------------------------------------------------------
void Ship::keyReleased(const OIS::KeyEvent& arg)
{
	if(!isFocus) return;

	if(!isFocus) return;

	if(arg.key == OIS::KC_LEFT) { mSteeringLeft = false; }
	else if(arg.key == OIS::KC_RIGHT) { mSteeringRight = false; }
	else if(arg.key == OIS::KC_DOWN) { mEngineForce = 0; }
	else if(arg.key == OIS::KC_UP) { mEngineForce = 0; }
}