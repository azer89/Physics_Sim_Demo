

#ifndef __Robot_h_
#define __Robot_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class Robot : public Character
{
protected:


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