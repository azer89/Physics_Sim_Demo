
#include "Stdafx.h"
#include "Robot.h"

static float gMaxEngineForce = 3000.f;

static float gSteeringIncrement = 0.04f;
static float gSteeringClamp = 0.2f;

static float gWheelRadius = 0.5f;
static float gWheelWidth = 0.4f;

static float gWheelFriction = 1e30f;
static float gSuspensionStiffness = 5.f;
static float gSuspensionDamping = 2.3f;
static float gSuspensionCompression = 4.4f;

static float gRollInfluence = 1.0f;
static float gSuspensionRestLength = 0.6;
static float gMaxSuspensionTravelCm = 500.0;
static float gFrictionSlip = 10.5;

//-------------------------------------------------------------------------------------
Robot::Robot(void)
{
	direction = Ogre::Vector3::ZERO;
	speed = 0.2f;
	robotState = RobotState::NOT_MOVE;
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

	//-------------------------------------------------------------------------------------
	Ogre::Entity* robotEntity = mSceneMgr->createEntity("RobotEntity", "mechanimated.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	robotNode = this->mMainNode->createChildSceneNode("RobotNode");	
	robotNode->attachObject(robotEntity);
	robotNode->translate(Ogre::Vector3(-20, 0, -20));
	robotNode->setScale(Ogre::Vector3(2));	
	robotNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(135).valueRadians()));
		
	this->mMainNode->setPosition(Ogre::Vector3(-103, 60, 40));

	Vector3 sight = Ogre::Vector3(0, 25, 0);
	Vector3 cam = Ogre::Vector3(75, 25, 75);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("robotSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("robotCameraNode", cam);

	ani = robotEntity->getAnimationState("walking");
	ani->setEnabled(true);
	//ani->setLength(1.5f);
	//ani->setLoop(true);

	//-------------------------------------------------------------------------------------
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

	mChassis = mSceneMgr->createEntity( "chassis" + StringConverter::toString(mNumEntitiesInstanced++), "delorean.mesh");
	vehicleNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode();

	this->mMainNode = vehicleNode;
	Vector3 pos = this->mMainNode->_getDerivedPosition();

	Vector3 sight =  Vector3(0, 3, 0);
	Vector3 cam = Vector3(0, 6, -10);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("sightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("cameraNode", cam);

	SceneNode *chassisnode = vehicleNode->createChildSceneNode();
	chassisnode->attachObject (mChassis);
	chassisnode->setPosition (chassisShift);
	//chassisnode->rotate(Ogre::Quaternion(0, 0, 1, 0));

	mChassis->setQueryFlags (GEOMETRY_QUERY_MASK);
	mChassis->setQueryFlags (1<<2);
	mChassis->setCastShadows(false);

	CompoundCollisionShape* compound = new CompoundCollisionShape();

	BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	compound->addChildShape(chassisShape, chassisShift); 

	mCarChassis = new WheeledRigidBody("carChassis", mBulletWorld);

	mCarChassis->setShape (vehicleNode, 
		compound, 
		0.6,				// restitution
		0.6,				// friction
		800,				// bodyMass
		CarPosition, 
		Quaternion::IDENTITY);
	mCarChassis->setDamping(0.2, 0.2);

	mCarChassis->disableDeactivation ();
	mTuning = new VehicleTuning( gSuspensionStiffness, gSuspensionCompression, gSuspensionDamping, gMaxSuspensionTravelCm, gFrictionSlip);

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
		mWheels[i] = mSceneMgr->createEntity( "wheel" + StringConverter::toString(mNumEntitiesInstanced++), "wheel.mesh");

		mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
		mWheels[i]->setQueryFlags (1<<2);

		mWheels[i]->setCastShadows(false);

		mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
		mWheelNodes[i]->attachObject (mWheels[i]);

	}

	bool isFrontWheel = true;

	Ogre::Vector3 connectionPointCS0 ( CUBE_HALF_EXTENTS + (0.3*gWheelWidth), connectionHeight, 2.3 * CUBE_HALF_EXTENTS - gWheelRadius);

	mVehicle->addWheel(
		mWheelNodes[0],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3( -CUBE_HALF_EXTENTS - (0.3*gWheelWidth), connectionHeight, 2.3 * CUBE_HALF_EXTENTS - gWheelRadius);

	mVehicle->addWheel(
		mWheelNodes[1],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3( -CUBE_HALF_EXTENTS - (0.3*gWheelWidth), connectionHeight, -2.1 * CUBE_HALF_EXTENTS + gWheelRadius);

	isFrontWheel = false;
	mVehicle->addWheel(
		mWheelNodes[2],
		connectionPointCS0,
		wheelDirectionCS0,
		wheelAxleCS,
		gSuspensionRestLength,
		gWheelRadius,
		isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3( CUBE_HALF_EXTENTS + (0.3*gWheelWidth), connectionHeight, -2.1 * CUBE_HALF_EXTENTS + gWheelRadius);

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
void Robot::updatePerFrame(Real elapsedTime)
{
	if(direction.x == -1)		// left
	{
		mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-speed).valueRadians()));
	}
	else if(direction.x == 1)	// right
	{
		mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(speed).valueRadians()));
	}

	/*
	if(direction.z == -1)		// forward
	{
		mMainNode->translate(
			robotNode->_getDerivedOrientation() *
			Ogre::Quaternion(sqrt(0.5), 0, -sqrt(0.5), 0) *
			Ogre::Vector3(0, 0, -speed));

		//ani->addTime(elapsedTime * 1.1f);
	}
	else if(direction.z == 1)	// backward
	{
		mMainNode->translate(
			robotNode->_getDerivedOrientation() *
			Ogre::Quaternion(sqrt(0.5), 0, -sqrt(0.5), 0) *
			Ogre::Vector3(0, 0, speed));

		//ani->addTime(-elapsedTime * 1.1f);
	
	}
	*/

	if(robotState == RobotState::MOVE_FORWARD)
	{
		mMainNode->translate(
			robotNode->_getDerivedOrientation() *
			Ogre::Quaternion(sqrt(0.5), 0, -sqrt(0.5), 0) *
			Ogre::Vector3(0, 0, -speed));

		ani->addTime(elapsedTime * 1.1f);
	}
	else if (robotState == RobotState::MOVE_BACKWARD)
	{
		mMainNode->translate(
			robotNode->_getDerivedOrientation() *
			Ogre::Quaternion(sqrt(0.5), 0, -sqrt(0.5), 0) *
			Ogre::Vector3(0, 0, speed));

		ani->addTime(-elapsedTime * 1.1f);
	}

	/*
	if (direction.z == 0 && robotState != 0)		// transition 
	{
		Ogre::Real l = ani->getLength();
		Ogre::Real curAni = ani->getTimePosition();

		if(robotState == 1 && (l - curAni) < 0.01f)
		{
			ani->setTimePosition(l);
			robotState = 0;
		}
		else if(robotState == 2 && (curAni) < 0.01f)
		{
			ani->setTimePosition(0);
			robotState = 0;
		}
	}
	*/
	
}

//-------------------------------------------------------------------------------------
// when key pressed
void Robot::keyPressed(const OIS::KeyEvent& arg)
{
	if(!isFocus) return;

	if(arg.key == OIS::KC_LEFT) 
	{ 
		direction.x = -1; 
	}
	else if(arg.key == OIS::KC_RIGHT) 
	{ 
		direction.x = 1; 
	}
	else if(arg.key == OIS::KC_DOWN) 
	{ 
		direction.z = 1;
		robotState = RobotState::MOVE_BACKWARD;
	}
	else if(arg.key == OIS::KC_UP) 
	{ 
		direction.z = -1; 
		robotState = RobotState::MOVE_FORWARD;
	}

}

//-------------------------------------------------------------------------------------
// when key released
void Robot::keyReleased(const OIS::KeyEvent& arg)
{
	if(arg.key == OIS::KC_LEFT) 
	{ 
		direction.x = 0; 
	}
	else if(arg.key == OIS::KC_RIGHT) 
	{ 
		direction.x = 0; 
	}
	else if(arg.key == OIS::KC_DOWN) 
	{ 
		direction.z = 0; 
		robotState = RobotState::NOT_MOVE;
	}
	else if(arg.key == OIS::KC_UP) 
	{ 
		direction.z = 0; 
		robotState = RobotState::NOT_MOVE;
	}
}