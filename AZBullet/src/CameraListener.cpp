
#include "Stdafx.h"
#include "CameraListener.h"

//------------------------------------------------------------------------------------- 
CameraListener::CameraListener(RenderWindow* win, Camera* cam) : 
	ExampleFrameListener(win, cam)
{
	mChar = 0;
	mExCamera = 0;
	mMode = 0;
}


//------------------------------------------------------------------------------------- 
void CameraListener::setCharacter (Character *character) { mChar = character; }

//------------------------------------------------------------------------------------- 
void CameraListener::setExtendedCamera (ThirdPersonCamera *cam) { mExCamera = cam; }

//------------------------------------------------------------------------------------- 
void CameraListener::instantUpdate()
{
	if (mExCamera && mChar) mExCamera->instantUpdate (mChar->getCameraNode ()->_getDerivedPosition(), mChar->getSightNode ()->_getDerivedPosition());
}

//------------------------------------------------------------------------------------- 
bool CameraListener::frameStarted(const FrameEvent& evt)
{
	mKeyboard->capture();

	if (mChar) 
	{
		//mChar->update (evt.timeSinceLastFrame, mKeyboard);
		if (mExCamera) 
		{
			if(mMode == 0) // 3rd person chase
			{
				mExCamera->update (evt.timeSinceLastFrame, 
					mChar->getCameraNode()->_getDerivedPosition(), 
					mChar->getSightNode()->_getDerivedPosition());
			}
			else if(mMode == 1) // 3rd person fixed
			{
				mExCamera->update (evt.timeSinceLastFrame, 
					Vector3 (0, 200, 0), 
					mChar->getSightNode()->_getDerivedPosition());
			}
			else if(mMode == 2) // 1st person
			{
				mExCamera->update (evt.timeSinceLastFrame, 
					mChar->getWorldPosition(), 
					mChar->getSightNode()->_getDerivedPosition());
				
			}
		}
	}

	// 3rd Person - Chase Camera
	if (mKeyboard->isKeyDown (OIS::KC_F1)) {
		mMode = 0;
		if (mChar)
			static_cast<Vehicle *>(mChar)->setVisible(true);
		if (mExCamera) {
			if (mChar)
				mExCamera->instantUpdate (mChar->getCameraNode ()->_getDerivedPosition(), mChar->getSightNode ()->_getDerivedPosition());
			mExCamera->setTightness (Ogre::Vector3(0.01f));
		}
	}
	// 3rd Person - Fixed Camera
	if (mKeyboard->isKeyDown (OIS::KC_F2)) {
		mMode = 1;
		if (mChar)
			static_cast<Vehicle *>(mChar)->setVisible(true);
		if (mExCamera) {
			if (mChar)
				mExCamera->instantUpdate (Vector3 (0, 200, 0), mChar->getSightNode ()->_getDerivedPosition());
			mExCamera->setTightness (Ogre::Vector3(0.01f));
		}
	}
	// 1st Person
	if (mKeyboard->isKeyDown (OIS::KC_F3))  {
		mMode = 2;
		if (mChar)
			static_cast<Vehicle *>(mChar)->setVisible(false);
		if (mExCamera) {
			if (mChar)
				mExCamera->instantUpdate (mChar->getWorldPosition (), mChar->getSightNode ()->_getDerivedPosition());
			mExCamera->setTightness (Ogre::Vector3(0.01f));
		}
	}

	// Exit if we press Esc
	if(mKeyboard->isKeyDown (OIS::KC_ESCAPE)) return false;

	return true;
}


