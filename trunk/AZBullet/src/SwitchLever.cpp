
#include "Stdafx.h"
#include "SwitchLever.h"

SwitchLever::SwitchLever(void)
{
	lever01Active = false;
	lever02Active = false;

	aniCounter01 = 0.0f;
	aniCounter02 = 0.0f;
}

SwitchLever::~SwitchLever(void)
{
}

void SwitchLever::createObject(OgreBulletListener *bulletListener, size_t &mNumEntitiesInstanced)
{
	// Collision Detector --------------------------------------------------------------
	colDetector = new CollisionDetectorTool(bulletListener->mBulletWorld);

	// First Lever ---------------------------------------------------------------------
	mRigidBody01 = this->addRigidBody(1,
		bulletListener,
		"lever.mesh",
		Ogre::Vector3(-195, 110, 375),
		Ogre::Vector3(2, 3, 5),
		Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(5),
		Ogre::Quaternion::IDENTITY,
		mNumEntitiesInstanced);

	// Second Lever --------------------------------------------------------------------
	Ogre::Real degree = Ogre::Degree(180).valueRadians();

	mRigidBody02 = this->addRigidBody(2,
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
	btRigidBody* vRigidBody = vehicle->mVehicle->getBulletVehicle()->getRigidBody();
	btRigidBody* rRigidBody = robot->mVehicle->getBulletVehicle()->getRigidBody();

	btRigidBody* lvr01 = mRigidBody01->getBulletRigidBody();
	btRigidBody* lvr02 = mRigidBody02->getBulletRigidBody();	

	bool col01 = colDetector->checkCollision(lvr01, vRigidBody);
	bool col02 = colDetector->checkCollision(lvr02, rRigidBody);

	if(col01)
	{
		lever01Active = true;
		robot->activateRobot();
	}
	else if(col02)
	{
		lever02Active = true;
		rocket->activateRocket();
		soundManager->playVictory();
	}

	if(lever01Active)
	{
		ani01->addTime(elapsedTime * 0.8f);
		aniCounter01 += (elapsedTime * 0.8f);

		if(aniCounter01 >= ani01->getLength())
		{
			lever01Active = false;
		}
	}

	if(lever02Active)
	{
		ani02->addTime(elapsedTime * 0.8f);
		aniCounter02 += (elapsedTime * 0.8f);

		if(aniCounter02 >= ani02->getLength())
		{
			lever02Active = false;
		}
	}
}

//-------------------------------------------------------------------------------------
RigidBody* SwitchLever::addRigidBody(int noLever,
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

	if(noLever == 1)
	{
		ani01 = mEntity->getAnimationState("rotate");
		ani01->setEnabled(true);
		ani01->setLoop(false);
	}
	else if(noLever == 2)
	{
		ani02 = mEntity->getAnimationState("rotate");
		ani02->setEnabled(true);
		ani02->setLoop(false);
	}

	BoxCollisionShape* sceneCubeShape = new BoxCollisionShape(size);

	RigidBody* mRigidBody = new RigidBody(
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

	return mRigidBody;
}