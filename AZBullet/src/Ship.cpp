
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
	

	this->shipPosition = Ogre::Vector3(-90, 8, 20);
	
	Ogre::Real degree = Ogre::Degree(-225).valueRadians();
	this->shipRotation = Quaternion(Math::Cos(degree/2), 0, Math::Sin(degree/2), 0);
}

//-------------------------------------------------------------------------------------
Ship::~Ship(void)
{
}

//-------------------------------------------------------------------------------------
//void Ship::createObject(OgreBulletListener *bulletListener,
//						Hydrax::Hydrax *mHydrax,
//						size_t &mNumEntitiesInstanced)
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

	//this->addRigidBodyShip(bulletListener,	// bullet listener
	//	"BlueShip",							// instance name
	//	Ogre::Vector3(-80, 50, -50),		// position
	//	Quaternion::IDENTITY,				// orientation
	//	Ogre::Vector3(15, 10, 45),			// size
	//	0.0f,								// restitution
	//	0.6f,								// friction
	//	1500.0f,							// mass
	//	mNumEntitiesInstanced);				// number of instances

	//Ogre::Entity* rocketEntity = mSceneMgr->createEntity("ShipNode", "yatch.mesh");
	//this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	//shipNode = this->mMainNode->createChildSceneNode("ShipNode");
	//shipNode->attachObject(rocketEntity);		
	//shipNode->setScale(Ogre::Vector3(5));
	//shipNode->setFixedYawAxis(true);
	//shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-45).valueRadians()));

	//this->mMainNode->setPosition(Ogre::Vector3(-80, 50, -50));

	//Vector3 sight = Ogre::Vector3(0, 25, 0);
	//Vector3 cam = Ogre::Vector3(-250, 100, 0);

	//// set up sight node	
	//mSightNode = this->mMainNode->createChildSceneNode ("shipSightNode", sight);
	//mCameraNode = this->mMainNode->createChildSceneNode ("shipCameraNode", cam);	
}

//-------------------------------------------------------------------------------------
void Ship::updatePerFrame(Real elapsedTime)
{

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
	
	//Ogre::Vector3 curPos = this->mMainNode->getPosition();

	//if(mHydrax->isVisible())
	//{
	//	Ogre::Real hydraxHeight = mHydrax->getHeigth(Ogre::Vector2(curPos.x, curPos.z));
	//	this->mMainNode->setPosition(Ogre::Vector3(curPos.x, hydraxHeight, curPos.z));
	//}
	//else
	//{
	//	this->mMainNode->setPosition(Ogre::Vector3(curPos.x, 50, curPos.z));
	//}

	//if(direction.x == -1)		// left
	//{
	//	//mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-speed).valueRadians()));
	//}
	//else if(direction.x == 1)	// right
	//{
	//	//mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(speed).valueRadians()));
	//}

	//if(direction.z != 0)
	//{
	//	Vector3 force = mMainNode->_getDerivedOrientation() * Ogre::Vector3(0, 0, speed * direction.z);
	//	//std::cout << force << "\n";
	//	//shipRigidBody->applyForce(force, Vector3::ZERO);
	//	shipRigidBody->setLinearVelocity(force.x, force.y, force.z);
	//}
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

	/*if(arg.key == OIS::KC_LEFT)			{ direction.x = -1; }
	else if(arg.key == OIS::KC_RIGHT)	{ direction.x = 1;  }
	else if(arg.key == OIS::KC_DOWN)	{ direction.z = 1;  }
	else if(arg.key == OIS::KC_UP)		{ direction.z = -1; }*/
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

	/*if(arg.key == OIS::KC_LEFT)			{ direction.x = 0;  }
	else if(arg.key == OIS::KC_RIGHT)	{ direction.x = 0;  }
	else if(arg.key == OIS::KC_DOWN)	{ direction.z = 0;  }
	else if(arg.key == OIS::KC_UP)		{ direction.z = 0;  }*/
}

//-------------------------------------------------------------------------------------
//void Ship::addRigidBodyShip(OgreBulletListener *bulletListener,
//							const Ogre::String instanceName,
//							const Ogre::Vector3 &pos, 
//							const Ogre::Quaternion &q, 
//							const Ogre::Vector3 &size,
//							const Ogre::Real bodyRestitution, 
//							const Ogre::Real bodyFriction, 
//							const Ogre::Real bodyMass,
//							size_t &mNumEntitiesInstanced)
//{
//	Entity *shipEntity = bulletListener->mBulletSceneMgr->createEntity(
//		instanceName + StringConverter::toString(mNumEntitiesInstanced),
//		"yatch.mesh");
//
//	shipEntity->setQueryFlags (GEOMETRY_QUERY_MASK);
//	//rocketEntity->setCastShadows(true);
//
//	BoxCollisionShape *sceneCubeShape = new BoxCollisionShape(size);
//	
//	shipRigidBody = new RigidBody(
//		"shipRigid" + StringConverter::toString(mNumEntitiesInstanced), 
//		bulletListener->mBulletWorld);
//
//	this->mMainNode = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();
//	//shipNode = this->mMainNode->createChildSceneNode("ShipNode");
//	mMainNode->attachObject(shipEntity);		
//	mMainNode->setScale(Ogre::Vector3(5));
//	mMainNode->setFixedYawAxis(true);
//	mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-45).valueRadians()));
//
//	Vector3 sight = Ogre::Vector3(0, 25, 0);
//	Vector3 cam = Ogre::Vector3(-250, 100, 0);
//
//	// set up sight node	
//	mSightNode = this->mMainNode->createChildSceneNode ("shipSightNode", sight);
//	mCameraNode = this->mMainNode->createChildSceneNode ("shipCameraNode", cam);
//	
//	shipRigidBody->setShape (mMainNode,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);
//
//	bulletListener->mEntities.push_back(shipEntity);
//	bulletListener->mShapes.push_back(sceneCubeShape);
//	bulletListener->mBodies.push_back(shipRigidBody);
//
//	shipRigidBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));		// make it float
//	shipRigidBody->setKinematicObject(true);									// set it as kinematic object
//
//	mNumEntitiesInstanced++;
//}