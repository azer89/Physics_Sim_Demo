
#include "Stdafx.h"
#include "Rocket.h"

Rocket::Rocket(void)
{
}

Rocket::~Rocket(void)
{
}

void Rocket::createObject(SceneManager* mSceneMgr)
{
	Ogre::Entity* rocketEntity = mSceneMgr->createEntity("RocketNode", "rocket.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	rocketNode = this->mMainNode->createChildSceneNode("RocketMode");
	rocketNode->attachObject(rocketEntity);
	rocketNode->setScale(Ogre::Vector3(20));
	
	this->mMainNode->setPosition(Ogre::Vector3(375, 112, 375));

	Vector3 sight = Ogre::Vector3(0, 50, 0);
	Vector3 cam = Ogre::Vector3(250, 50, 250);

	mSightNode = this->mMainNode->createChildSceneNode("rocketSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode("rocketCameraNode", cam);
}