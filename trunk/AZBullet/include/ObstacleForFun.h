
#ifndef __ObstacleForFun_h_
#define __ObstacleForFun_h_

#include "OgreBulletCollisionsShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Dynamics/Constraints/OgreBulletDynamicsHingeConstraint.h"

#include "Ogre.h"
#include "OgreBulletListener.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class ObstacleForFun
{

protected:
	void addRigidBody(
		OgreBulletListener *bulletListener,
		const Ogre::String meshFile,
		const Ogre::Vector3 &pos, 
		const Ogre::Vector3 &size,
		const Ogre::Vector3 &translation,
		const Ogre::Vector3 &scale,
		const Ogre::Quaternion &q, 
		size_t &mNumEntitiesInstanced);


public:
	ObstacleForFun(void);
	virtual ~ObstacleForFun(void);

	void createObject(OgreBulletListener *bulletListener, size_t &mNumEntitiesInstanced);

	virtual void updatePerFrame(Real elapsedTime);

	virtual void keyPressed(const OIS::KeyEvent& arg)
	{
	}

	virtual void keyReleased(const OIS::KeyEvent& arg)
	{
	}
};

#endif