

#ifndef __Rocket_h_
#define __Rocket_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class Rocket : public Character
{
protected:
	

public:
	SceneNode *rocketNode;

	Rocket::Rocket(void);
	virtual ~Rocket(void);

	void createRocket(SceneManager* mSceneMgr);
	
};

#endif