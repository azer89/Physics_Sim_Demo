

#ifndef __Robot_h_
#define __Robot_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class Robot : public Character
{
protected:
	int robotState;
	Ogre::AnimationState* ani;
	Ogre::Vector3 direction;
	Ogre::Real speed;
	
public:
	SceneNode *robotNode;

	Robot(void);
	virtual ~Robot(void);

	void createObject(SceneManager* mSceneMgr);

	void updatePerFrame(Real elapsedTime);
	void keyPressed(const OIS::KeyEvent& arg);
	void keyReleased(const OIS::KeyEvent& arg);
};

#endif