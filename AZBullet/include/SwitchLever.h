


#ifndef __SwitchLever_h_
#define __SwitchLever_h_

#include "Ogre.h"
#include "Character.h"

using namespace Ogre;

class SwitchLever : public Character
{
protected:

public:
	SceneNode *switchLeverNode;

	SwitchLever(void);
	virtual ~SwitchLever(void);

	void createObject(SceneManager* mSceneMgr);

	virtual void updatePerFrame(Real elapsedTime);

	virtual void keyPressed(const OIS::KeyEvent& arg)
	{
	}

	virtual void keyReleased(const OIS::KeyEvent& arg)
	{
	}
};

#endif