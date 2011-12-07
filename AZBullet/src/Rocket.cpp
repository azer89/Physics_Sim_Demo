
#include "Stdafx.h"
#include "Rocket.h"

Rocket::Rocket(void)
{
}

Rocket::~Rocket(void)
{
}

void Rocket::createRocket(SceneManager* mSceneMgr)
{
	Ogre::Entity* rocketEntity = mSceneMgr->createEntity("RocketNode", "rocket.mesh");
	rocketNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	rocketNode->attachObject(rocketEntity);

	
	rocketNode->setPosition(Ogre::Vector3(375, 90, 375));
	rocketNode->setScale(Ogre::Vector3(20));
}