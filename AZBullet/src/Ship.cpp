
#include "Stdafx.h"
#include "Ship.h"

Ship::Ship(void)
{
}

Ship::~Ship(void)
{
}

void Ship::createShip(SceneManager* mSceneMgr, Hydrax::Hydrax *mHydrax)
{
	
	Ogre::Entity* rocketEntity = mSceneMgr->createEntity("ShipNode", "yatch.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	shipNode = this->mMainNode->createChildSceneNode("ShipNode");
	shipNode->attachObject(rocketEntity);		
	shipNode->setScale(Ogre::Vector3(5));
	shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-30).valueRadians()));

	this->mMainNode->setPosition(Ogre::Vector3(-80, 50, -50));

	Vector3 sight = Ogre::Vector3(0, 25, 0);
	Vector3 cam = Ogre::Vector3(0, 30, -250);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("shipSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("shipCameraNode", cam);
	
}