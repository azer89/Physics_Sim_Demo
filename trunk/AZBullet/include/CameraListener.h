
#include "Stdafx.h"
#include "ClassDefine.h"
#include "ThirdPersonCamera.h"
#include "ExampleFrameListener.h"

using namespace Ogre;

class CameraListener : public ExampleFrameListener
{
public:
	CameraListener(RenderWindow* win, Camera* cam) : ExampleFrameListener(win, cam)
	{
		mChar = 0;
		mExCamera = 0;
		mMode = 0;
	}

	void setCharacter (Character *character);
	void setExtendedCamera (ThirdPersonCamera *cam);
	bool frameStarted(const FrameEvent& evt);

protected:
	
	Character *mChar;				// References to the main character and the camera
	ThirdPersonCamera *mExCamera;
	unsigned int mMode;				// Camera mode - Now supports 1st person, 3rd person (chasing) and 3rd person (fixed)


};