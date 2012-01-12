
#include "Stdafx.h"
#include "Ship.h"

const float gStaticBodyRestitution  = 0.1f;
const float gStaticBodyFriction     = 0.8f;

const float gDynamicBodyRestitution = 0.6f;
const float gDynamicBodyFriction    = 0.6f;
const float gDynamicBodyMass        = 1.0f;

//-------------------------------------------------------------------------------------
Ship::Ship(void)
{
	speed = 0.3f;
}

//-------------------------------------------------------------------------------------
Ship::~Ship(void)
{
}

//-------------------------------------------------------------------------------------
void Ship::createObject(OgreBulletListener *bulletListener,
						Hydrax::Hydrax *mHydrax,
						size_t &mNumEntitiesInstanced)
{
	this->mHydrax = mHydrax;
	this->addRigidBodyShip(bulletListener,	// bullet listener
		"BlueShip",							// instance name
		Ogre::Vector3(-80, 50, -50),		// position
		Quaternion::IDENTITY,				// orientation
		Ogre::Vector3(15, 10, 45),			// size
		0.0f,								// restitution
		0.6f,								// friction
		1500.0f,							// mass
		mNumEntitiesInstanced);				// number of instances

	//Ogre::Entity* rocketEntity = mSceneMgr->createEntity("ShipNode", "yatch.mesh");
	//this->mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	//shipNode = this->mMainNode->createChildSceneNode("ShipNode");
	//shipNode->attachObject(rocketEntity);		
	//shipNode->setScale(Ogre::Vector3(5));
	//shipNode->setFixedYawAxis(true);
	//shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-45).valueRadians()));

	//this->mMainNode->setPosition(Ogre::Vector3(-80, 50, -50));

	//Vector3 sight = Ogre::Vector3(0, 25, 0);
	//Vector3 cam = Ogre::Vector3(-250, 100, 0);

	//// set up sight node	
	//mSightNode = this->mMainNode->createChildSceneNode ("shipSightNode", sight);
	//mCameraNode = this->mMainNode->createChildSceneNode ("shipCameraNode", cam);
	
}

//-------------------------------------------------------------------------------------
void Ship::updatePerFrame(Real elapsedTime)
{
	
	Ogre::Vector3 curPos = this->mMainNode->getPosition();

	if(mHydrax->isVisible())
	{
		/*
		int dist = 30;
		Ogre::Real weight = 10.0f;

		Ogre::Real height01 = mHydrax->getHeigth(Ogre::Vector2(curPos.x, curPos.z + dist));
		Ogre::Real height02 = mHydrax->getHeigth(Ogre::Vector2(curPos.x + dist, curPos.z));
		Ogre::Real height03 = mHydrax->getHeigth(Ogre::Vector2(curPos.x - dist, curPos.z));

		Ogre::Vector3 point1 = curPos * (Ogre::Vector3(dist, height02, 0) - Ogre::Vector3(0, height01, dist));
		Ogre::Vector3 point2 = curPos * (Ogre::Vector3(-dist, height03, 0) - Ogre::Vector3(0, height01, dist));
		Ogre::Vector3 point3 = point1.crossProduct(point2);

		point3.x /= weight;
		point3.z /= weight;
		point3.normalise();
		*/

		Ogre::Real hydraxHeight = mHydrax->getHeigth(Ogre::Vector2(curPos.x, curPos.z));
		this->mMainNode->setPosition(Ogre::Vector3(curPos.x, hydraxHeight, curPos.z));

		//this->shipNode->setOrientation(Ogre::Quaternion(point3.x, point3.y, point3.z));
		//shipNode->rotate(Ogre::Vector3::UNIT_X, Ogre::Radian(Ogre::Degree(180).valueRadians()));
	}
	else
	{
		this->mMainNode->setPosition(Ogre::Vector3(curPos.x, 50, curPos.z));
	}

	if(direction.x == -1)		// left
	{
		//mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-speed).valueRadians()));
	}
	else if(direction.x == 1)	// right
	{
		//mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(speed).valueRadians()));
	}

	if(direction.z == -1)		// currently move forward
	{
		mMainNode->translate(
			mMainNode->_getDerivedOrientation() *
			Ogre::Vector3(0, 0, -speed));
	}
	else if (direction.z == 1)		// currently move backward
	{
		mMainNode->translate(
			mMainNode->_getDerivedOrientation() *
			Ogre::Vector3(0, 0, speed));
	}
}

//-------------------------------------------------------------------------------------
void Ship::keyPressed(const OIS::KeyEvent& arg)
{
	if(!isFocus) return;

	if(arg.key == OIS::KC_LEFT) 
	{ 
		direction.x = -1; 
	}
	else if(arg.key == OIS::KC_RIGHT) 
	{ 
		direction.x = 1; 
	}
	else if(arg.key == OIS::KC_DOWN) 
	{ 
		direction.z = 1;
	}
	else if(arg.key == OIS::KC_UP) 
	{ 
		direction.z = -1; 
	}
}

//-------------------------------------------------------------------------------------
void Ship::keyReleased(const OIS::KeyEvent& arg)
{
	if(arg.key == OIS::KC_LEFT) 
	{ 
		direction.x = 0; 
	}
	else if(arg.key == OIS::KC_RIGHT) 
	{ 
		direction.x = 0; 
	}
	else if(arg.key == OIS::KC_DOWN) 
	{ 
		direction.z = 0; 
	}
	else if(arg.key == OIS::KC_UP) 
	{ 
		direction.z = 0; 
	}
}

//-------------------------------------------------------------------------------------
RigidBody* Ship::addRigidBodyShip(OgreBulletListener *bulletListener,
							const Ogre::String instanceName,
							const Ogre::Vector3 &pos, 
							const Ogre::Quaternion &q, 
							const Ogre::Vector3 &size,
							const Ogre::Real bodyRestitution, 
							const Ogre::Real bodyFriction, 
							const Ogre::Real bodyMass,
							size_t &mNumEntitiesInstanced)
{
	Entity *shipEntity = bulletListener->mBulletSceneMgr->createEntity(
		instanceName + StringConverter::toString(mNumEntitiesInstanced),
		"yatch.mesh");

	shipEntity->setQueryFlags (GEOMETRY_QUERY_MASK);
	//rocketEntity->setCastShadows(true);

	BoxCollisionShape *sceneCubeShape = new BoxCollisionShape(size);
	
	RigidBody *shipRigidBody = new RigidBody(
		"shipRigid" + StringConverter::toString(mNumEntitiesInstanced), 
		bulletListener->mBulletWorld);

	this->mMainNode = bulletListener->mBulletSceneMgr->getRootSceneNode()->createChildSceneNode();
	//shipNode = this->mMainNode->createChildSceneNode("ShipNode");
	mMainNode->attachObject(shipEntity);		
	mMainNode->setScale(Ogre::Vector3(5));
	mMainNode->setFixedYawAxis(true);
	mMainNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-45).valueRadians()));

	Vector3 sight = Ogre::Vector3(0, 25, 0);
	Vector3 cam = Ogre::Vector3(-250, 100, 0);

	// set up sight node	
	mSightNode = this->mMainNode->createChildSceneNode ("shipSightNode", sight);
	mCameraNode = this->mMainNode->createChildSceneNode ("shipCameraNode", cam);
	
	shipRigidBody->setShape (mMainNode,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

	bulletListener->mEntities.push_back(shipEntity);
	bulletListener->mShapes.push_back(sceneCubeShape);
	bulletListener->mBodies.push_back(shipRigidBody);

	shipRigidBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));		// make it float
	shipRigidBody->setKinematicObject(true);									// set it as kinematic object

	mNumEntitiesInstanced++;

	return shipRigidBody;
}