

#ifndef __Rocket_h_
#define __Rocket_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class Rocket : public Character
{
protected:
	Ogre::Real curSpeed;					// current speed
	Ogre::Real accel;						// speed acceleration
	Ogre::Real maxSpeed;					// maximum speed
	Ogre::ParticleSystem* rocketSmoke;		// smoke particle

public:
	bool isActivated;
	SceneNode *rocketNode;

	Rocket::Rocket(void);
	virtual ~Rocket(void);

	void createObject(SceneManager* mSceneMgr);
	void activateRocket();

	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);
	
};

#endif