

#ifndef __Ship_h_
#define __Ship_h_

#include "Ogre.h"

using namespace Ogre;

class Ship 
{
protected:


public:
	SceneNode *shipNode;

	Ship::Ship(void);
	virtual ~Ship(void);

	void createShip(SceneManager* mSceneMgr);

};

#endif