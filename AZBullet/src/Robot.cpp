
#include "Stdafx.h"
#include "Robot.h"

Robot::Robot(void)
{
}

Robot::~Robot(void)
{
}

void Robot::createRobot(SceneManager* mSceneMgr)
{
	Ogre::Entity* robotEntity = mSceneMgr->createEntity("RobotEntity", "mechanimated.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	robotNode = this->mMainNode->createChildSceneNode("RobotNode");
	robotNode->attachObject(robotEntity);
	robotNode->setScale(Ogre::Vector3(2));
	robotNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(135).valueRadians()));
	
	this->mMainNode->setPosition(Ogre::Vector3(-123, 60, 20));

	Vector3 sight = Ogre::Vector3(0, 25, 0);
	Vector3 cam = Ogre::Vector3(75, 25, 75);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("robotSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("robotCameraNode", cam);
	
}