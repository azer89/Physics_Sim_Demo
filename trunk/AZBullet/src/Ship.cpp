
#include "Stdafx.h"
#include "Ship.h"

Ship::Ship(void)
{
}

Ship::~Ship(void)
{
}

void Ship::createShip(SceneManager* mSceneMgr)
{
	Ogre::Entity* rocketEntity = mSceneMgr->createEntity("ShipNode", "yatch.mesh");
	shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	shipNode->attachObject(rocketEntity);

	shipNode->setPosition(Ogre::Vector3(-80, 70, -50));
	shipNode->setScale(Ogre::Vector3(5));
	shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-30).valueRadians()));
}