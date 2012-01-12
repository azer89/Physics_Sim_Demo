

#ifndef __Ship_h_
#define __Ship_h_

#include "Ogre.h"
#include "Character.h"
#include "Hydrax.h"
#include "LinearMath/btVector3.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"
#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"
#include "OgreBulletDynamicsRigidBody.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class Ship : public Character
{
private:
	RigidBody *shipRigidBody;

	void addRigidBodyShip(OgreBulletListener *bulletListener,
					const Ogre::String instanceName,
					const Ogre::Vector3 &pos, 
					const Ogre::Quaternion &q, 
					const Ogre::Vector3 &size,
					const Ogre::Real bodyRestitution, 
					const Ogre::Real bodyFriction, 
					const Ogre::Real bodyMass,
					size_t &mNumEntitiesInstanced);

protected:
	Hydrax::Hydrax *mHydrax;
	Ogre::Real speed;
	Ogre::Vector3 direction;

public:
	SceneNode *shipNode;

	Ship(void);
	virtual ~Ship(void);

	void createObject(OgreBulletListener *bulletListener, Hydrax::Hydrax *mHydrax, size_t &mNumEntitiesInstanced);
	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);
};

#endif