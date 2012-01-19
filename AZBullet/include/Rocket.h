

#ifndef __Rocket_h_
#define __Rocket_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

// Class of Saturn V
class Rocket : public Character
{
protected:
	Ogre::Real curSpeed;					// current speed
	Ogre::Real accel;						// speed acceleration
	Ogre::Real maxSpeed;					// maximum speed
	Ogre::ParticleSystem* rocketSmoke;		// main rocket
	Ogre::ParticleSystem* rocketSmoke01;	// upleft rocket
	Ogre::ParticleSystem* rocketSmoke02;	// upright rocket
	Ogre::ParticleSystem* rocketSmoke03;	// downleft docket
	Ogre::ParticleSystem* rocketSmoke04;	// downright rocket

	bool isActivated;
	Ogre::Real timer;

public:
	
	bool setTimer;

	SceneNode *rocketNode;		// main rocket
	SceneNode *rocketNode01;	// up rocket
	SceneNode *rocketNode02;	// down rocket
	SceneNode *rocketNode03;	// left docket
	SceneNode *rocketNode04;	// right rocket

	Rocket::Rocket(void);
	virtual ~Rocket(void);

	void createObject(SceneManager* mSceneMgr);
	void activateRocket();

	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);
	
};

#endif