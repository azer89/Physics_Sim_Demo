
#include "Stdafx.h"
#include "Rocket.h"

//-------------------------------------------------------------------------------------
Rocket::Rocket(void)
{
	isActivated = false;
	curSpeed = 0.0f;
	accel = 0.03f;
	maxSpeed = 10.0f;
	setTimer = false;
	timer = 0.0f;
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

	Ogre::Real shift = 15.0f;
	
	// Main Rocket
	rocketSmoke = mSceneMgr->createParticleSystem("RocketSmoke01", "Examples/Smoke");
	Ogre::SceneNode* smokeNode = this->mMainNode->createChildSceneNode("SmokeNode01");
	smokeNode->attachObject(rocketSmoke);
	rocketSmoke->setVisible(false);

	// up
	rocketSmoke01 = mSceneMgr->createParticleSystem("RocketSmoke02", "Examples/Smoke02");
	Ogre::SceneNode* smokeNode01 = this->mMainNode->createChildSceneNode("SmokeNode02");
	smokeNode01->attachObject(rocketSmoke01);
	smokeNode01->setPosition(0, 0, shift);
	rocketSmoke01->setVisible(false);

	// down
	rocketSmoke02 = mSceneMgr->createParticleSystem("RocketSmoke03", "Examples/Smoke02");
	Ogre::SceneNode* smokeNode02 = this->mMainNode->createChildSceneNode("SmokeNode03");
	smokeNode02->attachObject(rocketSmoke02);
	smokeNode02->setPosition(0, 0, -shift);
	rocketSmoke02->setVisible(false);

	// left
	rocketSmoke03 = mSceneMgr->createParticleSystem("RocketSmoke04", "Examples/Smoke02");
	Ogre::SceneNode* smokeNode03 = this->mMainNode->createChildSceneNode("SmokeNode04");
	smokeNode03->attachObject(rocketSmoke03);
	smokeNode03->setPosition(shift, 0, 0);
	rocketSmoke03->setVisible(false);

	// right
	rocketSmoke04 = mSceneMgr->createParticleSystem("RocketSmoke05", "Examples/Smoke02");
	Ogre::SceneNode* smokeNode04 = this->mMainNode->createChildSceneNode("SmokeNode05");
	smokeNode04->attachObject(rocketSmoke04);
	smokeNode04->setPosition(-shift, 0, 0);
	rocketSmoke04->setVisible(false);

	Vector3 sight = Ogre::Vector3(0, 10, 0);
	Vector3 cam = Ogre::Vector3(100, 350, 100);

	mSightNode = this->mMainNode->createChildSceneNode("rocketSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode("rocketCameraNode", cam);

	//activateRocket();
}

//-------------------------------------------------------------------------------------
void Rocket::activateRocket()
{
	this->setTimer = true;
	//this->isActivated = true;
	//rocketSmoke->setVisible(true);
	//rocketSmoke01->setVisible(true);
	//rocketSmoke02->setVisible(true);
	//rocketSmoke03->setVisible(true);
	//rocketSmoke04->setVisible(true);
}

//-------------------------------------------------------------------------------------
void Rocket::updatePerFrame(Real elapsedTime)
{
	if(setTimer)
	{
		timer += elapsedTime;

		if(timer >= 3.0f)
		{
			this->isActivated = true;
			rocketSmoke->setVisible(true);
			rocketSmoke01->setVisible(true);
			rocketSmoke02->setVisible(true);
			rocketSmoke03->setVisible(true);
			rocketSmoke04->setVisible(true);
		}
	}

	if(!isActivated)	return;

	mMainNode->translate(0, curSpeed, 0);

	if(curSpeed < maxSpeed)
		curSpeed += accel * elapsedTime;
}

//-------------------------------------------------------------------------------------
void Rocket::keyPressed(const OIS::KeyEvent& arg)
{
}

//-------------------------------------------------------------------------------------
void Rocket::keyReleased(const OIS::KeyEvent& arg)
{
}