
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
	this->addRigidBody(mRigidBody01,
		ani01,
		bulletListener,
		"lever.mesh",
		Ogre::Vector3(-75, 110, 375),
		Ogre::Vector3(2, 3, 5),
		Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(5),
		Ogre::Quaternion::IDENTITY,
		mNumEntitiesInstanced);

	Ogre::Real degree = Ogre::Degree(180).valueRadians();

	this->addRigidBody(mRigidBody02,
		ani02,
		bulletListener,
		"lever02.mesh",
		Ogre::Vector3(375, 70, 260),
		Ogre::Vector3(8, 15, 1),
		Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(1),
		Quaternion(Math::Cos(degree/2), 0, Math::Sin(degree/2), 0),
		mNumEntitiesInstanced);
}

void SwitchLever::updatePerFrame(Real elapsedTime)
{
}

//-------------------------------------------------------------------------------------
void SwitchLever::addRigidBody(RigidBody* mRigidBody,
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
	switchLvrNode->setScale(scale);
	mRigidBody->setShape(ladderMainNode,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);
	mRigidBody->setKinematicObject(true);

	bulletListener->mEntities.push_back(mEntity);
	bulletListener->mShapes.push_back(sceneCubeShape);
	bulletListener->mBodies.push_back(mRigidBody);

	mNumEntitiesInstanced++;
}