

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

	void createObject(SceneManager* mSceneMgr);

	virtual void updatePerFrame(Real elapsedTime)
	{
	}

	virtual void keyPressed(const OIS::KeyEvent& arg)
	{
	}

	virtual void keyReleased(const OIS::KeyEvent& arg)
	{
	}

};

#endif