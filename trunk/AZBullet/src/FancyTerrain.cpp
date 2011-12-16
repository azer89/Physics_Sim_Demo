
#include "Stdafx.h"
#include "FancyTerrain.h"

FancyTerrain::FancyTerrain(void)
{
}

FancyTerrain::~FancyTerrain(void)
{
}

void FancyTerrain::createFancyTerrain(SceneManager* mSceneMgr)
{
	this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	this->mMainNode->setPosition(Ogre::Vector3(0, 0, 0));

	Vector3 sight = Ogre::Vector3(0, 0, 0);
	Vector3 cam = Ogre::Vector3(0, 1250, 0);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("fancyTerrainSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("fancyTerrainCameraNode", cam);

}