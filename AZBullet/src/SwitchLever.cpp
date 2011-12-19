
#include "Stdafx.h"
#include "SwitchLever.h"

SwitchLever::SwitchLever(void)
{
}

SwitchLever::~SwitchLever(void)
{
}

void SwitchLever::createObject(SceneManager* mSceneMgr)
{
	Ogre::Entity* leverEntity = mSceneMgr->createEntity("SwitchLeverEntity", "lever.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	switchLeverNode = this->mMainNode->createChildSceneNode("SwitchLeverNode");
	switchLeverNode->attachObject(leverEntity);
	switchLeverNode->setScale(Ogre::Vector3(5));

	this->mMainNode->setPosition(Ogre::Vector3(-75, 110, 375));

	Vector3 sight = Ogre::Vector3(0, 25, 0);
	Vector3 cam = Ogre::Vector3(75, 25, 75);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode("SwitchLeverSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode("SwitchLeverCameraNode", cam);	
}

void SwitchLever::updatePerFrame(Real elapsedTime)
{
}