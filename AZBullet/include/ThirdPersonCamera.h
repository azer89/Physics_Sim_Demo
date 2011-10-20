
/* 
	Camera system tutorial by Kencho
	http://www.ogre3d.org/tikiwiki/3rd+person+camera+system+tutorial
*/

#include "Stdafx.h"

using namespace Ogre;

class ThirdPersonCamera
{
protected:
	SceneNode *mTargetNode;		// The camera target
	SceneNode *mCameraNode;		// The camera itself
	Camera *mCamera;			// Ogre camera

	SceneManager *mSceneMgr;
	String mName;

	bool mOwnCamera;			// To know if the ogre camera binded has been created outside or inside of this class
	Real mTightness;			// Determines the movement of the camera - 1 means tight movement, while 0 means no movement

public:
	ThirdPersonCamera (String name, SceneManager *sceneMgr, Camera *camera = 0);
	virtual ~ThirdPersonCamera ();

	void setTightness (Real tightness);
	Real getTightness ();
	Vector3 getCameraPosition ();
	void instantUpdate (Vector3 cameraPosition, Vector3 targetPosition);
	void update (Real elapsedTime, Vector3 cameraPosition, Vector3 targetPosition);
};