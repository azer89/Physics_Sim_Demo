
#include "Stdafx.h"
#include "Robot.h"

Robot::Robot(void)
{
	direction = Ogre::Vector3::ZERO;
	speed = 0.2f;
	robotState = RobotState::NOT_MOVE;
}

Robot::~Robot(void)
{
}

void Robot::createObject(SceneManager* mSceneMgr)
{
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