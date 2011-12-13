
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
	robotNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	robotNode->attachObject(robotEntity);
	robotNode->setScale(Ogre::Vector3(2));
	robotNode->setPosition(Ogre::Vector3(-60, 60, 60));
}