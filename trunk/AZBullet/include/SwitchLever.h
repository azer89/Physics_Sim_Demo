


#ifndef __SwitchLever_h_
#define __SwitchLever_h_

#include "Ogre.h"
#include "Character.h"
#include "Robot.h"
#include "Vehicle.h"
#include "Rocket.h"
#include "CollisionDetectorTool.h"

using namespace Ogre;

class SwitchLever
{

protected:
	RigidBody* mRigidBody01;
	RigidBody* mRigidBody02;

	Ogre::AnimationState* ani01;
	Ogre::AnimationState* ani02;

	CollisionDetectorTool* colDetector;

	bool lever01Active;
	bool lever02Active;
	Ogre::Real aniCounter01;
	Ogre::Real aniCounter02;

protected:
	RigidBody* addRigidBody(int noLever,
		OgreBulletListener *bulletListener,
		const Ogre::String meshFile,
		const Ogre::Vector3 &pos, 
		const Ogre::Vector3 &size,
		const Ogre::Vector3 &translation,
		const Ogre::Vector3 &scale,
		const Ogre::Quaternion &q, 
		size_t &mNumEntitiesInstanced);

public:
	Robot* robot;
	Vehicle* vehicle;
	Rocket* rocket;

public:
	SwitchLever(void);
	virtual ~SwitchLever(void);

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