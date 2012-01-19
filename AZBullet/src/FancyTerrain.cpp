
#include "Stdafx.h"
#include "FancyTerrain.h"

//-------------------------------------------------------------------------------------
FancyTerrain::FancyTerrain(void)
{
}

//-------------------------------------------------------------------------------------
FancyTerrain::~FancyTerrain(void)
{
}

//-------------------------------------------------------------------------------------
void FancyTerrain::createObject(OgreBulletListener *bulletListener, size_t &mNumEntitiesInstanced)
{

	this->mMainNode = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();
	this->mMainNode->setPosition(Ogre::Vector3(0, 0, 0));

	Vector3 sight = Ogre::Vector3(0, 0, 0);
	Vector3 cam = Ogre::Vector3(0, 1225, 0);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("fancyTerrainSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("fancyTerrainCameraNode", cam);

	this->addRigidBodyLadder(bulletListener, "LadderLadder", Vector3(375, 110 + 58, -80), Quaternion::IDENTITY, 0.01f, 0.01f, 100, mNumEntitiesInstanced);

}

//-------------------------------------------------------------------------------------
void FancyTerrain::addRigidBodyLadder(OgreBulletListener *bulletListener,
							const Ogre::String instanceName,
							const Ogre::Vector3 &pos, 
							const Ogre::Quaternion &q, 
							const Ogre::Real bodyRestitution, 
							const Ogre::Real bodyFriction, 
							const Ogre::Real bodyMass,
							size_t &mNumEntitiesInstanced)
{
	Entity *ladderEntity = bulletListener->mBulletSceneMgr->createEntity( instanceName + StringConverter::toString(mNumEntitiesInstanced), "ladder.mesh");
	ladderEntity->setQueryFlags (GEOMETRY_QUERY_MASK);
	Vector3 size(15.0f, 103.0f, 1.5f);

	BoxCollisionShape* sceneCubeShape = new BoxCollisionShape(size);
	
	RigidBody* ladderRigidBody = new RigidBody(
		"LadderRigidBody" + StringConverter::toString(mNumEntitiesInstanced), 
		bulletListener->mBulletWorld);

	Ogre::SceneNode* ladderMainNode = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* ladderNode = ladderMainNode->createChildSceneNode();
	ladderNode->attachObject(ladderEntity);		
	ladderNode->translate(0, -size.y - 10, 0);
	ladderNode->setScale(0.8, 1.0, 0.8);
	ladderRigidBody->setShape(ladderMainNode,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);
	//ladderRigidBody->setDamping(10.0f, 10.0f);

	// hinge constraint
	Ogre::Vector3 pivot(0, -size.y, 0);
	Ogre::Vector3 axis(1, 0, 0);
	OgreBulletDynamics::HingeConstraint* hingeConstraint =new OgreBulletDynamics::HingeConstraint(ladderRigidBody, pivot, axis);	
	bulletListener->mBulletWorld->addConstraint(hingeConstraint);

	bulletListener->mEntities.push_back(ladderEntity);
	bulletListener->mShapes.push_back(sceneCubeShape);
	bulletListener->mBodies.push_back(ladderRigidBody);

	mNumEntitiesInstanced++;
}