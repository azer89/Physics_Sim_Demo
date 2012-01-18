
#include "Stdafx.h"
#include "Flag.h"

Flag::Flag(void)
{
}

Flag::~Flag(void)
{
}

void Flag::createObject(OgreBulletListener *bulletListener)
{
	Ogre::Entity* flagEnt01 = bulletListener->mBulletSceneMgr->createEntity("Flag01Entity", "flag.mesh");
	Ogre::SceneNode* flag01Node = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode("Flag01Node");
	flag01Node->attachObject(flagEnt01);
	flag01Node->setScale(Vector3(7));
	flag01Node->translate(-450 - 30, 119, -60);

	ani01 = flagEnt01->getAnimationState("wave");
	ani01->setEnabled(true);


	Ogre::Entity* flagEnt02 = bulletListener->mBulletSceneMgr->createEntity("Flag02Entity", "flag.mesh");
	Ogre::SceneNode* flag02Node = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode("Flag02Node");
	flag02Node->attachObject(flagEnt02);
	flag02Node->setScale(Vector3(7));
	flag02Node->translate(-450 + 30, 119, -60);

	ani02 = flagEnt02->getAnimationState("wave");
	ani02->setEnabled(true);
	ani02->addTime(10);
}

void Flag::updatePerFrame(Real elapsedTime)
{
	ani01->addTime(elapsedTime);
	ani02->addTime(elapsedTime);
}