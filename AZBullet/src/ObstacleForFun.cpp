
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
void ObstacleForFun::createObstacle(OgreBulletListener* listener, Vector3 shift)
{	
	// create obstacle in front of car
	listener->addCube("obstacle", Ogre::Vector3(13,  -5.25, -5) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(15,  -5.25, -5) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(17,  -5.25, -5) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	listener->addCube("obstacle", Ogre::Vector3(13,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(15,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(17,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	// create obstacle in back of car
	listener->addCube("obstacle", Ogre::Vector3(15,  -9.25, -45) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(17,  -9.25, -45) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(19,  -9.25, -45) + shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	listener->addCube("obstacle", Ogre::Vector3(13,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(15,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(17,  -5.25, -10) + shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	// create obstacle a bit aside
	listener->addCube("obstacle", Ogre::Vector3(-2,  0, -5) + shift ,  Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(0,  0, -5) + shift ,   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(2,  0, -5) + shift ,   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	listener->addCube("obstacle", Ogre::Vector3(-2,  0, -10) + shift , Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(0,  0, -10) + shift ,  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(2,  0, -10) + shift ,  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

	// create obstacle just for fun
	listener->addCube("obstacle", Ogre::Vector3(25, -10, -25) + shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(25, -10, -27) + shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	listener->addCube("obstacle", Ogre::Vector3(25, -10, -29) + shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
	
}

