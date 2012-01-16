
#include "Stdafx.h"
#include "ObstacleForFun.h"

using namespace Ogre;

//-------------------------------------------------------------------------------------
// constructor
ObstacleForFun::ObstacleForFun(void)
{
}
//-------------------------------------------------------------------------------------
// destructor
ObstacleForFun::~ObstacleForFun(void)
{
}

//-------------------------------------------------------------------------------------
// init function to create obstacle
void ObstacleForFun::createObject(OgreBulletListener* listener)
{	
	/*
	// create obstacle in front of car
	listener->addCube("obstacle", Ogre::Vector3(13,  -35.5, 20) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(15,  -35.5, 20) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(17,  -35.5, 20) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	*/
}

