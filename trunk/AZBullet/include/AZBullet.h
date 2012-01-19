/*
-----------------------------------------------------------------------------
Filename:    AZBullet.h
-----------------------------------------------------------------------------
*/

#ifndef __AZBullet_h_
#define __AZBullet_h_

#include "BaseApplication.h"
#include "ObstacleForFun.h"
#include "TerrainManager.h"
#include "Vehicle.h"
#include "CameraListener.h"
#include "ThirdPersonCamera.h"
#include "RayTerrain.h"
#include "Rocket.h"
#include "Robot.h"
#include "Ship.h"
#include "FancyTerrain.h"
#include "SwitchLever.h"
#include "CompositorSample.h"
#include "Flag.h"
#include "SoundManager.h"

#include "Hydrax/Hydrax.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

// forward definition
class RayFlashInterface;

// Main class which handles everything
class AZBullet : public BaseApplication,  public OgreBulletListener
{
public:
	AZBullet::AZBullet(void);
    virtual ~AZBullet(void);	

	void bulletInit();					// create bullet world	
	void shutdownApp(void);				// close program
	void toggleOceanSimulation();		// change ocean
	void setWeather(int val);			// change weather

	virtual void createFrameListener(void);

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& arg);

	void changeCameraPosition(int val);	// point the camera to different object
	void changeCompositor(int val);

public:
	 Ogre::Viewport* hViewPort;			// viewport from camera
	 RayFlashInterface* menu;			// hikari

protected:
     virtual void createScene(void);		// prepare everything
	 void repositionCamera(void);			// not used
	 void createSimpleWater();				// create simple water effect
	 void createHydraxSimulation();			// create hydrax ocean simulation
	 void changeSkyBox();					// change skybox texture and directional light	 

	 // OIS::MouseListener
	 virtual bool mouseMoved(const OIS::MouseEvent& arg);
	 virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	 virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

	 // OIS::KeyListener
	 virtual bool keyPressed(const OIS::KeyEvent& arg);
	 virtual bool keyReleased( const OIS::KeyEvent &arg);

protected:
	Ogre::SceneNode *mCurrentObject;	// pointer to our currently selected object
	Ogre::RaySceneQuery* mRayScnQuery;	// pointer to our ray scene query	

	bool bLMouseDown, bRMouseDown;		// true if mouse buttons are held down
	float mRotateSpeed;					// the rotation speed for the camera
	int mCurrentSkyBox;

	Ogre::SceneNode* waterNode;			// simple water effect
	TerrainManager* tManager;			// not used
	bool isHydraxEnabled;				// hydrax status
	Hydrax::Hydrax *mHydrax;			// hydrax ocean simulation
	CompositorSample* compSample;		// compositor implementation

	std::vector<Character*> chars;

	Vehicle* vehicle;					// 00
	Robot* robot;						// 01
	Ship* ship;							// 02
	Rocket* rocket;						// 03 
	FancyTerrain* fancyTerrain;			// 04
	SwitchLever* switchLever;			// 06
	Flag* flag;
	ObstacleForFun* obs;				// not used
	SoundManager* soundManager;
	//RayTerrain* rayTerrain;				// not used

	CameraListener* mCameraListener;
	ThirdPersonCamera* exCamera;

private:
	int _def_SkyBoxNum;

	Ogre::String mSkyBoxes[3];
	Ogre::Vector3 mSunPosition[3];
	Ogre::Vector3 mSunColor[3];
};

#endif // #ifndef __AZBullet_h_
