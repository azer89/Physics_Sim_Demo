
#include "Stdafx.h"
#include "SwitchLever.h"

SwitchLever::SwitchLever(void)
{
}

SwitchLever::~SwitchLever(void)
{
}

void SwitchLever::createObject(OgreBulletListener *bulletListener, size_t &mNumEntitiesInstanced)
{
	/*Ogre::Entity* leverEntity = bulletListener->mBulletSceneMgr->createEntity("SwitchLeverEntity", "lever.mesh");
	this->mMainNode01 = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();

	switchLeverNode01 = this->mMainNode01->createChildSceneNode("SwitchLeverNode");
	switchLeverNode01->attachObject(leverEntity);
	switchLeverNode01->setScale(Ogre::Vector3(5));

	this->mMainNode01->setPosition(Ogre::Vector3(-75, 110, 375));*/

		
}

void SwitchLever::updatePerFrame(Real elapsedTime)
{
}

//-------------------------------------------------------------------------------------
void SwitchLever::addRigidBodyLadder(RigidBody* mRigidBody,
									 Ogre::AnimationState* ani,
									 OgreBulletListener *bulletListener,
									 const Ogre::String meshFile,
									 const Ogre::Vector3 &pos, 
									 const Ogre::Vector3 &size,
									 const Ogre::Vector3 &translation,
									 const Ogre::Vector3 &scale,
									 const Ogre::Quaternion &q, 
									 size_t &mNumEntitiesInstanced)
{
	Ogre::Real bodyRestitution = 0; 
	Ogre::Real bodyFriction = 0;
	Ogre::Real bodyMass = 0;

	Entity *mEntity = bulletListener->mBulletSceneMgr->createEntity( "SwitchLever" + StringConverter::toString(mNumEntitiesInstanced), meshFile);
	mEntity->setQueryFlags (GEOMETRY_QUERY_MASK);

	BoxCollisionShape* sceneCubeShape = new BoxCollisionShape(size);

	mRigidBody = new RigidBody(
		"SwitchRigidBody" + StringConverter::toString(mNumEntitiesInstanced), 
		bulletListener->mBulletWorld);

	Ogre::SceneNode* ladderMainNode = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* switchLvrNode = ladderMainNode->createChildSceneNode();
	switchLvrNode->attachObject(mEntity);		
	switchLvrNode->translate(translation);
	switchLvrNode->setScale(0.8, 1, 0.8);
	mRigidBody->setShape(ladderMainNode,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

	bulletListener->mEntities.push_back(mEntity);
	bulletListener->mShapes.push_back(sceneCubeShape);
	bulletListener->mBodies.push_back(mRigidBody);

	mNumEntitiesInstanced++;
}