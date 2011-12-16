

#ifndef __FancyTerrain_h_
#define __FancyTerrain_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class FancyTerrain : public Character
{
protected:


public:
	SceneNode *robotNode;

	FancyTerrain::FancyTerrain(void);
	virtual ~FancyTerrain(void);

	void createFancyTerrain(SceneManager* mSceneMgr);

};

#endif