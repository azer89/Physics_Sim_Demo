

#ifndef __Ship_h_
#define __Ship_h_

#include "Ogre.h"
#include "Character.h"
#include "Hydrax.h"

using namespace Ogre;

class Ship : public Character
{
protected:
	Hydrax::Hydrax *mHydrax;

public:
	SceneNode *shipNode;

	Ship(void);
	virtual ~Ship(void);

	void createShip(SceneManager* mSceneMgr, Hydrax::Hydrax *mHydrax);
	void updatePerFrame(Real elapsedTime);

};

#endif