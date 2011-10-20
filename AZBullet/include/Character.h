
/* 
	Camera system tutorial by Kencho
	http://www.ogre3d.org/tikiwiki/3rd+person+camera+system+tutorial
*/

#include "Stdafx.h"
#include "ClassDefine.h"

using namespace Ogre;

class Character 
{
protected:
	SceneNode *mMainNode;			// Main character node
	SceneNode *mSightNode;			// "Sight" node - The character is supposed to be looking here
	SceneNode *mCameraNode;			// Node for the chase camera
	// Entity *mEntity;				// Character entity

public:
	// Updates the character (movement...)
	//virtual void update (Real elapsedTime, OIS::Keyboard *input) = 0;

	// The three methods below returns the two camera-related nodes, 
	// and the current position of the character (for the 1st person camera)
	SceneNode *getSightNode () 
	{
		return mSightNode;
	}

	SceneNode *getCameraNode () 
	{
		return mCameraNode;
	}

	Vector3 getWorldPosition () 
	{
		return mMainNode->_getDerivedPosition ();
	}
};