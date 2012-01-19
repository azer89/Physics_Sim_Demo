
/* 
	Camera system tutorial by Kencho
	http://www.ogre3d.org/tikiwiki/3rd+person+camera+system+tutorial

	Modified by Reza Adhitya Saputra
*/

#ifndef __Character_h_
#define __Character_h_


#include "Ogre.h"
#include "OgreBulletListener.h"

using namespace Ogre;

// abstract class of animated character
class Character 
{

protected:
	SceneNode *mMainNode;			// Main character node
	SceneNode *mSightNode;			// "Sight" node - The character is supposed to be looking here
	SceneNode *mCameraNode;			// Node for the chase camera

public:
	//virtual void createObject(SceneManager* mSceneMgr);

	virtual void updatePerFrame(Real elapsedTime) = 0;
	virtual void keyPressed(const OIS::KeyEvent& arg) = 0;
	virtual void keyReleased(const OIS::KeyEvent& arg) = 0;

	SceneNode *getSightNode() { return mSightNode; }
	SceneNode *getCameraNode() { return mCameraNode; }
	Vector3 getWorldPosition() { return mMainNode->_getDerivedPosition (); }

public:
	bool isFocus;
};

#endif