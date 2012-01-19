

#ifndef __FancyTerrain_h_
#define __FancyTerrain_h_

#include "Ogre.h"
#include "Character.h"

#include "OgreBulletCollisionsShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Dynamics/Constraints/OgreBulletDynamicsHingeConstraint.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

// Fake class to focus on trimesh terrain
class FancyTerrain : public Character
{
protected:
	void addRigidBodyLadder(OgreBulletListener *bulletListener,
					const Ogre::String instanceName,
					const Ogre::Vector3 &pos, 
					const Ogre::Quaternion &q, 
					const Ogre::Real bodyRestitution, 
					const Ogre::Real bodyFriction, 
					const Ogre::Real bodyMass,
					size_t &mNumEntitiesInstanced);

public:
	SceneNode *robotNode;
	RigidBody* terrainRigidBody;

	FancyTerrain::FancyTerrain(void);
	virtual ~FancyTerrain(void);

	void createObject(OgreBulletListener *bulletListener, size_t &mNumEntitiesInstanced);

	virtual void updatePerFrame(Real elapsedTime)
	{
	}

	virtual void keyPressed(const OIS::KeyEvent& arg)
	{
	}

	virtual void keyReleased(const OIS::KeyEvent& arg)
	{
	}

};

#endif