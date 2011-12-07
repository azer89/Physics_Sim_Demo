

#ifndef __Rocket_h_
#define __Rocket_h_

#include "Ogre.h"

using namespace Ogre;

class Rocket 
{
protected:
	

public:
	SceneNode *rocketNode;

	Rocket::Rocket(void);
	virtual ~Rocket(void);

	void createRocket(SceneManager* mSceneMgr);
	
};

#endif