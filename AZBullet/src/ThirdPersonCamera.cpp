
/* 
	Camera system tutorial by Kencho
	http://www.ogre3d.org/tikiwiki/3rd+person+camera+system+tutorial

	Modified by Reza Adhitya Saputra
*/

#include "Stdafx.h"
#include "ThirdPersonCamera.h"

using namespace Ogre;

ThirdPersonCamera::ThirdPersonCamera (String name, SceneManager *sceneMgr, Camera *camera) 
{
	// Basic member references setup
	mName = name;
	mSceneMgr = sceneMgr;

	// Create the camera's node structure
	mCameraNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName);
	mTargetNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName + "_target");
	mCameraNode->setAutoTracking (true, mTargetNode);	// The camera will always look at the camera target
	mCameraNode->setFixedYawAxis (true);				// Needed because of auto tracking
	
	// Create our camera if it wasn't passed as a parameter
	if (camera == 0) 
	{
		mCamera = mSceneMgr->createCamera (mName);
		mOwnCamera = true;
	}
	else 
	{
		mCamera = camera;
		// just to make sure that mCamera is set to 'origin' (same position as the mCameraNode)
		mCamera->setPosition(0.0, 0.0, 0.0);
		mOwnCamera = false;
	}

	// and attach the Ogre camera to the camera node
	mCameraNode->attachObject(mCamera);

	// Default tightness
	mTightness = Ogre::Vector3(0.05f, 0.02f, 0.05f);
}

ThirdPersonCamera::~ThirdPersonCamera () 
{
	mCameraNode->detachAllObjects ();
	if (mOwnCamera) delete mCamera;
	mSceneMgr->destroySceneNode (mName);
	mSceneMgr->destroySceneNode (mName + "_target");
}

void ThirdPersonCamera::setTightness (Ogre::Vector3 tightness) { mTightness = tightness; }
Ogre::Vector3 ThirdPersonCamera::getTightness () { return mTightness; }
Vector3 ThirdPersonCamera::getCameraPosition () { return mCameraNode->getPosition (); }
void ThirdPersonCamera::instantUpdate (Vector3 cameraPosition) { mCameraNode->setPosition (cameraPosition); }

void ThirdPersonCamera::instantUpdate (Vector3 cameraPosition, Vector3 targetPosition) 
{
	mCameraNode->setPosition (cameraPosition);
	mTargetNode->setPosition (targetPosition);
}

void ThirdPersonCamera::update (Real elapsedTime, Vector3 cameraPosition, Vector3 targetPosition) 
{
	// make the movement always on top
	bool isOnTop = true;
	if((cameraPosition.y - targetPosition.y) <= 2.0f) 
	{
		isOnTop = false;
	}

	// Handle movement
	Vector3 displacement01 = (targetPosition - mTargetNode->getPosition());
	displacement01.x *= mTightness.x;
	displacement01.y *= mTightness.y;
	displacement01.z *= mTightness.z;

	Vector3 displacement02 = (cameraPosition - mCameraNode->getPosition());
	displacement02.x *= mTightness.x;
	displacement02.y *= mTightness.y;	
	displacement02.z *= mTightness.z;

	if(!isOnTop) 
	{
		displacement01.y += 0.1;
		displacement02.y += 0.1;
	}

	mTargetNode->translate(displacement01);
	mCameraNode->translate(displacement02);
}