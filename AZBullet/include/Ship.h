

#ifndef __Ship_h_
#define __Ship_h_

#include "Ogre.h"
#include "Character.h"
#include "Hydrax.h"

using namespace Ogre;

class Ship : public Character
{
protected:


public:
	SceneNode *shipNode;

	Ship::Ship(void);
	virtual ~Ship(void);

	void createShip(SceneManager* mSceneMgr, Hydrax::Hydrax *mHydrax);

};

#endif