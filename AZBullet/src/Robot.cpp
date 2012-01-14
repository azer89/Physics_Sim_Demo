
#include "Stdafx.h"
#include "Robot.h"

static float gMaxEngineForce = 10000.f;

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
static float gFrictionSlip = 10.5;

#define CUBE_HALF_EXTENTS 1

//-------------------------------------------------------------------------------------
Robot::Robot(void)
{
	mSteeringLeft = false;
	mSteeringRight = false;

	mEngineForce = 0;
	mSteering = 0;


	// on bridge
	//this->robotPosition = Ogre::Vector3(10, 61, 133);
	//Ogre::Real degree = Ogre::Degree(-135).valueRadians();
	//this->robotRotation = Quaternion(Math::Cos(degree/2), 0, Math::Sin(degree/2), 0);

	// on hill
	this->robotPosition = Ogre::Vector3(-65, 110, 375);
	Ogre::Real degree = Ogre::Degree(180).valueRadians();
	this->robotRotation = Quaternion(Math::Cos(degree/2), 0, Math::Sin(degree/2), 0);
}

//-------------------------------------------------------------------------------------
Robot::~Robot(void)
{
}

//-------------------------------------------------------------------------------------
void Robot::createObject(SceneManager* mSceneMgr, 
						 OgreBulletDynamics::DynamicsWorld *mBulletWorld,
						 size_t &mNumEntitiesInstanced)
{
	//mWheelsEngineCount = 4;
	//mWheelsEngine[0] = 0; mWheelsEngine[1] = 1; mWheelsEngine[2] = 2; mWheelsEngine[3] = 3;

	//mWheelsSteerableCount = 4;
	//mWheelsSteerable[0] = 0; mWheelsSteerable[1] = 1; mWheelsSteerable[2] = 2; mWheelsSteerable[3] = 3; 

	//mWheelsSteerableCount = 2;
	//mWheelsSteerable[0] = 0; mWheelsSteerable[1] = 1;

	//const Ogre::Vector3 chassisShift(0, 1.0, 0);
	//float connectionHeight = 0.7f;

	//robotEntity = mSceneMgr->createEntity( "RobotEntity" + StringConverter::toString(mNumEntitiesInstanced++), "mechanimated.mesh");
	//vehicleNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode();

	//this->mMainNode = vehicleNode;
	//Vector3 pos = this->mMainNode->_getDerivedPosition();

	//SceneNode *chassisNode = vehicleNode->createChildSceneNode();
	//chassisNode->setPosition (chassisShift);
	//
	//robotNode = chassisNode->createChildSceneNode("RobotNode");	
	//robotNode->attachObject(robotEntity);
	//robotNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-90).valueRadians()));
	//robotEntity->setQueryFlags (GEOMETRY_QUERY_MASK);
	//robotEntity->setQueryFlags (1<<2);
	//robotEntity->setCastShadows(false);

	//// set up sight node	
	//mSightNode = chassisNode->createChildSceneNode ("RobotSightNode", Vector3(0, 5, 0));
	//mCameraNode = chassisNode->createChildSceneNode ("RobotCameraNode", Vector3(0, 30, -60));

	//ani = robotEntity->getAnimationState("walking");
	//ani->setEnabled(true);

	//CompoundCollisionShape* compound = new CompoundCollisionShape();
	//compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(4.0f, 0.5f, 4.0f)), chassisShift);								// base
	//compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(2.0f, 2.8f, 3.0f)), chassisShift + Ogre::Vector3(0, 8.0, 0));	// body
	//compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(0.6f, 4.0f, 2.0f)), chassisShift + Ogre::Vector3(-3, 4.0, 0));	// left limb
	//compound->addChildShape(new BoxCollisionShape(Ogre::Vector3(0.6f, 4.0f, 2.0f)), chassisShift + Ogre::Vector3(3, 4.0, 0));	// right limb
	//
	//mRobotChassis = new WheeledRigidBody("RobotChassis", mBulletWorld);
	//
	//mRobotChassis->setShape (chassisNode, 
	//	compound, 
	//	0.0,				// restitution
	//	0.6f,				// friction
	//	1500,				// bodyMass
	//	this->robotPosition, 
	//	this->robotRotation);
	//
	//mRobotChassis->setDamping(0.2, 0.2);		// ratio effect
	//mRobotChassis->disableDeactivation ();

	//mTuning = new VehicleTuning( gSuspensionStiffness, gSuspensionCompression, gSuspensionDamping, gMaxSuspensionTravelCm, gFrictionSlip);

	//mVehicleRayCaster = new VehicleRayCaster(mBulletWorld);
	//mVehicle = new RaycastVehicle(mRobotChassis, mTuning, mVehicleRayCaster);
	//mVehicle->setCoordinateSystem(0, 1, 2);	// rightIndex, upIndex, forwardIndex

	//mRobotChassis->getBulletRigidBody()->setLinearFactor(btVector3(1, 1, 1));
	//mRobotChassis->getBulletRigidBody()->setAngularFactor(btVector3(0.5, 0.5, 0.5));	

	////mCarChassis->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));
	////btVector3 objGravity = mCarChassis->getBulletRigidBody()->getGravity();	//objGravity.
	////mCarChassis->getBulletRigidBody()->setGravity(objGravity);

	////btRigidBody* zeroBody = new btRigidBody(0, NULL, NULL); // Create the body that we attach things to
	////btRigidBody* robot = mRobotChassis->getBulletRigidBody();

	////btGeneric6DofConstraint* constrict = new btGeneric6DofConstraint(*robot, *zeroBody, btTransform::getIdentity(), btTransform::getIdentity(), false);

	////constrict->setLimit(0,1,0); // Disable X axis limits
	////constrict->setLimit(1,1,0); // Disable Y axis limits
	////constrict->setLimit(2,0,0); // Set the Z axis to always be equal to zero
	////constrict->setLimit(3,1,0); // Uncap the rotational axes
	////constrict->setLimit(4,1,0); // Uncap the rotational axes
	////constrict->setLimit(5,1,0); // Uncap the rotational axes

	////constrict->setLinearLowerLimit( btVector3( 1, 1, 1));
	////constrict->setLinearUpperLimit( btVector3(-1, -1,-1));

	////constrict->setAngularLowerLimit( btVector3( 1,  1,  1) );
	////constrict->setAngularUpperLimit( btVector3(-1, -1, -1) );

	////mBulletWorld->getBulletDynamicsWorld()->addConstraint(constrict);	

	//for (size_t i = 0; i < 4; i++) 
	//{ 
	//	mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();

	//	/*mWheels[i] = mSceneMgr->createEntity( "wheel" + StringConverter::toString(mNumEntitiesInstanced++), "wheel.mesh");
	//	mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
	//	mWheels[i]->setQueryFlags (1<<2);
	//	mWheels[i]->setCastShadows(false);

	//	mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
	//	mWheelNodes[i]->attachObject (mWheels[i]);*/

	//}

	//Ogre::Vector3 wheelDirectionCS0(0, -1, 0);
	//Ogre::Vector3 wheelAxleCS(-1, 0, 0);

	//mVehicle->addWheel(mWheelNodes[0],
	//	Ogre::Vector3 ( CUBE_HALF_EXTENTS + (4.0*gWheelWidth), connectionHeight, 4.0 * CUBE_HALF_EXTENTS - gWheelRadius),
	//	wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, true, gWheelFriction, gRollInfluence);

	//mVehicle->addWheel(mWheelNodes[1],
	//	Ogre::Vector3( -CUBE_HALF_EXTENTS - (4.0*gWheelWidth), connectionHeight, 4.0 * CUBE_HALF_EXTENTS - gWheelRadius),
	//	wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, true, gWheelFriction, gRollInfluence);

	//mVehicle->addWheel(mWheelNodes[2],
	//	Ogre::Vector3( -CUBE_HALF_EXTENTS - (4.0*gWheelWidth), connectionHeight, -4.0 * CUBE_HALF_EXTENTS + gWheelRadius),
	//	wheelDirectionCS0, wheelAxleCS, gSuspensionRestLength, gWheelRadius, false, gWheelFriction, gRollInfluence);

	//mVehicle->addWheel(mWheelNodes[3],
	//	Ogre::Vector3( CUBE_HALF_EXTENTS + (4.0*gWheelWidth), connectionHeight, -4.0 * CUBE_HALF_EXTENTS + gWheelRadius),
	//	wheelDirectionCS0, wheelAxleCS,	gSuspensionRestLength,	gWheelRadius, false, gWheelFriction, gRollInfluence);

	//mVehicle->getBulletVehicle()->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
}

//-------------------------------------------------------------------------------------
// update per frame
void Robot::updatePerFrame(Real elapsedTime)
{
	
	//Ogre::Real currentSpeed = mVehicle->getBulletVehicle()->getCurrentSpeedKmHour();
	//
	//// transfer velocity from ship to robot ----------------------------------------------
	//Ogre::Real shipSpeed = ship->mVehicle->getBulletVehicle()->getCurrentSpeedKmHour();
	//btVector3 shipPos = ship->mVehicle->getBulletVehicle()->getRigidBody()->getCenterOfMassPosition();
	//btVector3 robotPos = this->mVehicle->getBulletVehicle()->getRigidBody()->getCenterOfMassPosition();
	//btVector3 shipLinearVelocity = ship->mVehicle->getBulletVehicle()->getRigidBody()->getLinearVelocity();
	//Ogre::Real dist = shipPos.distance(robotPos);
	//
	////std::cout << this->robotNode->_getDerivedPosition() << "\n";

	//bool isGotTransfer = false;
	////std::cout << dist << "\n" ;
	//if((shipSpeed < -5.0f || shipSpeed > 5.0f) && dist <= 55.0f)
	//{
	//	mVehicle->getBulletVehicle()->getRigidBody()->setLinearVelocity(ship->mVehicle->getBulletVehicle()->getRigidBody()->getLinearVelocity());
	//	mVehicle->getBulletVehicle()->getRigidBody()->setAngularVelocity(ship->mVehicle->getBulletVehicle()->getRigidBody()->getAngularVelocity());
	//	isGotTransfer = true;
	//}
	////-------------------------------------------------------------------------------------

	//Ogre::Real animFactor = mVehicle->getBulletVehicle()->getCurrentSpeedKmHour() / 50.0f;
	//if((animFactor > 0.1f || animFactor < -0.1f) && !isGotTransfer)	ani->addTime(elapsedTime * animFactor);

	//// -----------------------------------------------------------------------------------

	//// apply engine Force on relevant wheels
	//for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++) 
	//{
	//	Ogre::Real xFactor = 1.0f;
	//	if(currentSpeed < 100.0f && currentSpeed >= 0.0f) xFactor = 2.0f;
	//	if(currentSpeed > -100.0f && currentSpeed <= 0.0f) xFactor = -2.0f;

	//	mVehicle->applyEngineForce (mEngineForce , mWheelsEngine[i]); 

	//	if(mEngineForce == 0) 
	//	{
	//		if(currentSpeed > 20.0f || currentSpeed < -20.0f) mVehicle->getBulletVehicle()->setBrake(1000, mWheelsEngine[i]);
	//		else if(currentSpeed >= 20.0f && currentSpeed >= -20.0f) mVehicle->getBulletVehicle()->setBrake(100, mWheelsEngine[i]);
	//		else if(currentSpeed < 2.0f && currentSpeed > -2.0f) mVehicle->getBulletVehicle()->setBrake(0, mWheelsEngine[i]);
	//	}
	//}

	//if (mSteeringLeft)
	//{
	//	mSteering += gSteeringIncrement;
	//	if (mSteering > gSteeringClamp) mSteering = gSteeringClamp;
	//}
	//else if (mSteeringRight)
	//{
	//	mSteering -= gSteeringIncrement;
	//	if (mSteering < -gSteeringClamp) mSteering = -gSteeringClamp;
	//}
	//else if(!mSteeringLeft && !mSteeringRight)
	//{
	//	if(mSteering > 0)mSteering -= 0.01f;
	//	else if(mSteering < 0) mSteering += 0.01f;

	//	if(Math::Abs(mSteering) <= 0.1f) mSteering = 0.0f;
	//}

	//// apply Steering on relevant wheels
	//for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	//{
	//	if (i < 2) mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
	//	else mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
	//}
}

//-------------------------------------------------------------------------------------
// when key pressed
void Robot::keyPressed(const OIS::KeyEvent& arg)
{
	/*if(!isFocus)	return;

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
	}*/
}

//-------------------------------------------------------------------------------------
// when key released
void Robot::keyReleased(const OIS::KeyEvent& arg)
{
	/*if(!isFocus) return;

	if(arg.key == OIS::KC_LEFT) { mSteeringLeft = false; }
	else if(arg.key == OIS::KC_RIGHT) { mSteeringRight = false; }
	else if(arg.key == OIS::KC_DOWN) { mEngineForce = 0; }
	else if(arg.key == OIS::KC_UP) { mEngineForce = 0; }*/
}