

#ifndef __CameraListener_h_
#define __CameraListener_h_

#include "Vehicle.h"
#include "ThirdPersonCamera.h"
#include "ExampleFrameListener.h"

using namespace Ogre;

class CameraListener : public ExampleFrameListener
{
public:
	CameraListener(RenderWindow* win, Camera* cam);

	void setCharacter (Character *character);
	void setExtendedCamera (ThirdPersonCamera *cam);
	bool frameStarted(const FrameEvent& evt);
	void instantUpdate();

protected:	
	Character *mChar;				// References to the main character and the camera
	ThirdPersonCamera *mExCamera;
	unsigned int mMode;				// Camera mode
};

#endif