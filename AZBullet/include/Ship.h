

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
protected:
	Hydrax::Hydrax *mHydrax;
	Ogre::Real speed;
	Ogre::Vector3 direction;

public:
	SceneNode *shipNode;

	Ship(void);
	virtual ~Ship(void);

	void createObject(SceneManager* mSceneMgr, Hydrax::Hydrax *mHydrax);
	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);
};

#endif