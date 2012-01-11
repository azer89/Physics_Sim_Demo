
#include "Stdafx.h"
#include "Rocket.h"

//-------------------------------------------------------------------------------------
Rocket::Rocket(void)
{
	isActivated = false;
	curSpeed = 0.0f;
	accel = 0.0005f;
	maxSpeed = 10.0f;
}

//-------------------------------------------------------------------------------------
Rocket::~Rocket(void)
{
}

//-------------------------------------------------------------------------------------
void Rocket::createObject(SceneManager* mSceneMgr)
{
	Ogre::Entity* rocketEntity = mSceneMgr->createEntity("RocketNode", "saturnv.mesh");
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	rocketNode = this->mMainNode->createChildSceneNode("RocketNode");
	rocketNode->attachObject(rocketEntity);
	rocketNode->setScale(Ogre::Vector3(10));
	
	this->mMainNode->setPosition(Ogre::Vector3(375, 115, 375));
	
	rocketSmoke = mSceneMgr->createParticleSystem("RocketSmoke", "Examples/Smoke");
	Ogre::SceneNode* smokeNode = this->mMainNode->createChildSceneNode("SmokeNode");
	smokeNode->attachObject(rocketSmoke);
	rocketSmoke->setVisible(false);

	Vector3 sight = Ogre::Vector3(0, 10, 0);
	Vector3 cam = Ogre::Vector3(100, 350, 100);

	mSightNode = this->mMainNode->createChildSceneNode("rocketSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode("rocketCameraNode", cam);

	//activateRocket();
}

//-------------------------------------------------------------------------------------
void Rocket::activateRocket()
{
	this->isActivated = true;
	rocketSmoke->setVisible(true);
}

//-------------------------------------------------------------------------------------
void Rocket::updatePerFrame(Real elapsedTime)
{
	if(!isActivated)	return;

	mMainNode->translate(0, curSpeed, 0);

	if(curSpeed < maxSpeed)
		curSpeed += accel;
}

//-------------------------------------------------------------------------------------
void Rocket::keyPressed(const OIS::KeyEvent& arg)
{
}

//-------------------------------------------------------------------------------------
void Rocket::keyReleased(const OIS::KeyEvent& arg)
{
}