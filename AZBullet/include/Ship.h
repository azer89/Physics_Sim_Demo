

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

	void createObject(SceneManager* mSceneMgr, Hydrax::Hydrax *mHydrax);
	virtual void updatePerFrame(Real elapsedTime);
	virtual void keyPressed(const OIS::KeyEvent& arg);
	virtual void keyReleased(const OIS::KeyEvent& arg);


};

#endif