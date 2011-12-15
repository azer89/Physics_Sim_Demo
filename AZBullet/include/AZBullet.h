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

#include "Hydrax/Hydrax.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

class RayFlashInterface;

class AZBullet : public BaseApplication,  public OgreBulletListener
{
public:
	AZBullet::AZBullet(void);
    virtual ~AZBullet(void);	

	void bulletInit();
	virtual void createFrameListener(void);
	void shutdownApp(void);
	void toggleOceanSimulation();
	void setWeather(int val);

	// void bulletKeyPressed(BULLET_KEY_CODE key);
	// void bulletKeyReleased(BULLET_KEY_CODE key);
	// bool bulletFrameStarted(Ogre::Real elapsedTime);

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& arg);

public:
	Ogre::Viewport* hViewPort;
	RayFlashInterface* menu;	// hikari

protected:
     virtual void createScene(void);
	 void repositionCamera(void);
	 void createSimpleWater();
	 void createSimpleSky();
	 void createHydraxSimulation();
	 void changeSkyBox();
	 void changeCameraPosition(int val);

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

	Ogre::SceneNode* waterNode;
	TerrainManager* tManager;
	Vehicle* vehicle;
	ObstacleForFun* obs;
	RayTerrain* rayTerrain;
	Hydrax::Hydrax *mHydrax;
	Rocket* rocket;
	Robot* robot;
	Ship* ship; 
	bool isHydraxEnabled;

	OgreBites::Label* mInfoLabel;	// message info

	CameraListener* mCameraListener;
	ThirdPersonCamera* exCamera;

private:
	int _def_SkyBoxNum;

	Ogre::String mSkyBoxes[3];
	Ogre::Vector3 mSunPosition[3];
	Ogre::Vector3 mSunColor[3];
};

#endif // #ifndef __AZBullet_h_
