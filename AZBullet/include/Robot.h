

#ifndef __Robot_h_
#define __Robot_h_

#include "Ogre.h"

using namespace Ogre;

class Robot 
{
protected:


public:
	SceneNode *robotNode;

	Robot::Robot(void);
	virtual ~Robot(void);

	void createRobot(SceneManager* mSceneMgr);

};

#endif