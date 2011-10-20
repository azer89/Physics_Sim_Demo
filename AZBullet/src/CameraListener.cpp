
#include "Stdafx.h"
#include "CameraListener.h"
#include "Character.h"
#include "Vehicle.h"
#include "ThirdPersonCamera.h"
#include "ExampleFrameListener.h"


void CameraListener::setCharacter (Character *character) 
{
	mChar = character;
}

void CameraListener::setExtendedCamera (ThirdPersonCamera *cam) 
{
	mExCamera = cam;
}

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
					mChar->getCameraNode()->getWorldPosition(), 
					mChar->getSightNode()->getWorldPosition());
			}
			else if(mMode == 0) // 3rd person fixed
			{
				mExCamera->update (evt.timeSinceLastFrame, 
					Vector3 (0, 200, 0), 
					mChar->getSightNode()->getWorldPosition());
			}
			else if(mMode == 2) // 1st person
			{
				mExCamera->update (evt.timeSinceLastFrame, 
					mChar->getWorldPosition(), 
					mChar->getSightNode()->getWorldPosition());
				
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
				mExCamera->instantUpdate (mChar->getCameraNode ()->getWorldPosition (), mChar->getSightNode ()->getWorldPosition ());
			mExCamera->setTightness (0.01f);
		}
	}
	// 3rd Person - Fixed Camera
	if (mKeyboard->isKeyDown (OIS::KC_F2)) {
		mMode = 1;
		if (mChar)
			static_cast<Vehicle *>(mChar)->setVisible(true);
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
			static_cast<Vehicle *>(mChar)->setVisible(false);
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


