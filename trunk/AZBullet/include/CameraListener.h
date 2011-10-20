
#include "Stdafx.h"
#include "ExampleFrameListener.h"
#include "Vehicle.h"

using namespace Ogre;

class CameraListener : public ExampleFrameListener
{
protected:
	// References to the main character and the camera
	Character *mChar;
	ThirdPersonCamera *mExCamera;

	// Camera mode - Now supports 1st person, 3rd person (chasing) and 3rd person (fixed)
	unsigned int mMode;

public:
	CameraListener(RenderWindow* win, Camera* cam)
		: ExampleFrameListener(win, cam)
	{
		mChar = 0;
		mExCamera = 0;
		mMode = 0;
	}

	void setCharacter (Character *character) 
	{
		mChar = character;
	}

	void setExtendedCamera (ExtendedCamera *cam) 
	{
		mExCamera = cam;
	}

	bool frameStarted(const FrameEvent& evt)
	{
		mKeyboard->capture();

		if (mChar) {
			mChar->update (evt.timeSinceLastFrame, mKeyboard);

			if (mExCamera) {
				switch (mMode) {
case 0: // 3rd person chase
	mExCamera->update (evt.timeSinceLastFrame, 
		mChar->getCameraNode ()->getWorldPosition (), 
		mChar->getSightNode ()->getWorldPosition ());
	break;
case 1: // 3rd person fixed
	mExCamera->update (evt.timeSinceLastFrame, 
		Vector3 (0, 200, 0), 
		mChar->getSightNode ()->getWorldPosition ());
	break;
case 2: // 1st person
	mExCamera->update (evt.timeSinceLastFrame, 
		mChar->getWorldPosition (), 
		mChar->getSightNode ()->getWorldPosition ());
	break;
				}
			}
		}

		// 3rd Person - Chase Camera
		if (mKeyboard->isKeyDown (OIS::KC_F1)) {
			mMode = 0;
			if (mChar)
				static_cast<OgreCharacter *>(mChar)->setVisible (true);
			if (mExCamera) {
				if (mChar)
					mExCamera->instantUpdate (mChar->getCameraNode ()->getWorldPosition (), mChar->getSightNode ()->getWorldPosition ());
				mExCamera->setTightness (0.01f);
			}
		}
		// 3rd Person - Fixed Camera
		if (mKeyboard->isKeyDown (OIS::KC_F2)) {
			mMode = 1;
			if (mChar)
				static_cast<OgreCharacter *>(mChar)->setVisible (true);
			if (mExCamera) {
				if (mChar)
					mExCamera->instantUpdate (Vector3 (0, 200, 0), mChar->getSightNode ()->getWorldPosition ());
				mExCamera->setTightness (0.01f);
			}
		}
		// 1st Person
		if (mKeyboard->isKeyDown (OIS::KC_F3))  {
			mMode = 2;
			if (mChar)
				static_cast<OgreCharacter *>(mChar)->setVisible (false);
			if (mExCamera) {
				if (mChar)
					mExCamera->instantUpdate (mChar->getWorldPosition (), mChar->getSightNode ()->getWorldPosition ());
				mExCamera->setTightness (1.0f);
			}
		}

		// Exit if we press Esc
		if(mKeyboard->isKeyDown (OIS::KC_ESCAPE))
			return false;

		return true;
	}
};