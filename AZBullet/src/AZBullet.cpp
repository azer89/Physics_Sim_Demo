/*
-----------------------------------------------------------------------------
Filename:    AZBullet.cpp
-----------------------------------------------------------------------------
*/

#include "Stdafx.h"
#include "AZBullet.h"

#include "OgreBulletDynamicsWorld.h"

#include "Hydrax/Noise/Perlin/Perlin.h"
#include "Hydrax/Modules/ProjectedGrid/ProjectedGrid.h"

#define _def_SkyBoxNum 3

Ogre::String mSkyBoxes[_def_SkyBoxNum] = {"Sky/ClubTropicana", "Sky/EarlyMorning", "Sky/Clouds"};
Ogre::Vector3 mSunPosition[_def_SkyBoxNum] = {Ogre::Vector3(0,10000,0), Ogre::Vector3(0,10000,90000), Ogre::Vector3(0,10000,0)};
Ogre::Vector3 mSunColor[_def_SkyBoxNum] =  {Ogre::Vector3(1, 0.9, 0.6), Ogre::Vector3(1,0.6,0.4), Ogre::Vector3(0.45,0.45,0.45)};

AZBullet::AZBullet(void):OgreBulletListener()
{
	this->mRotateSpeed = 0.1f;
	this->mCurrentSkyBox = 0;

	vehicle = NULL;
	tManager = NULL;
	obs = NULL;
	rayTerrain = NULL;
	mHydrax = NULL;
}

//-------------------------------------------------------------------------------------
AZBullet::~AZBullet(void)
{	
	if (vehicle != NULL)	delete vehicle;
	if (tManager != NULL)	delete tManager;
	if (obs != NULL)		delete obs;
	if (rayTerrain != NULL) delete rayTerrain;
	if (mHydrax != NULL)	delete mHydrax;
}

//-------------------------------------------------------------------------------------
void AZBullet::createScene(void)
{		
	hViewPort = mCamera->getViewport();
	this->bulletInit();
}

//------------------------------------------------------------------------------------
void AZBullet::changeSkyBox()
{
	// Change skybox
	mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999*3, true);

	// Update Hydrax sun position and colour
	mHydrax->setSunPosition(mSunPosition[mCurrentSkyBox]);
	mHydrax->setSunColor(mSunColor[mCurrentSkyBox]);

	// Update light 0 light position and colour
	mSceneMgr->getLight("Light0")->setPosition(mSunPosition[mCurrentSkyBox]);
	mSceneMgr->getLight("Light0")->setSpecularColour(mSunColor[mCurrentSkyBox].x,
													 mSunColor[mCurrentSkyBox].y,
													 mSunColor[mCurrentSkyBox].z);
}

// -------------------------------------------------------------------------
void AZBullet::bulletInit()
{	
	mBulletCamera = mCamera;		// OgreBulletListener's camera
	mBulletWindow = mWindow;		// OgreBulletListener's window
	mBulletRoot = mRoot;			// OgreBulletListener's root
	mBulletSceneMgr = mSceneMgr;	// OgreBulletListener's scene manager

	mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
	mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999*3, true);
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(99999*6);
	mCamera->pitch(Degree(0));
	mCamera->yaw(Degree(0));
	//mBulletCameraMove = 1;

	//Ogre::Viewport *vp = this->mCamera->getViewport();
	//vp->setBackgroundColour(ColourValue(0, 0, 0.2f));	
	initWorld();					// Start Bullet

	// Light
	Ogre::Light *mLight = mSceneMgr->createLight("Light0");
	mLight->setPosition(mSunPosition[mCurrentSkyBox]);
	mLight->setDiffuseColour(1, 1, 1);
	mLight->setSpecularColour(mSunColor[mCurrentSkyBox].x,
							  mSunColor[mCurrentSkyBox].y,
							  mSunColor[mCurrentSkyBox].z);

	
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// create terrain group
	//rayTerrain = new RayTerrain();
	//rayTerrain->createTerrain(this->mSceneMgr, light);
	//rayTerrain->integrateBullet(mSceneMgr, mBulletWorld, mBodies, mShapes);
	
	// Create a terrain
	//tManager = new TerrainManager();
	//tManager->createTerrain(mSceneMgr, mBulletWorld, mBodies, mShapes);

	// create a vehicle
	vehicle = new Vehicle();
	vehicle->createVehicle(this->mSceneMgr, 
		this->mBulletWorld, 
		this->mNumEntitiesInstanced,
		this->mCamera);

	exCamera = new ThirdPersonCamera("Third Person Camera", mSceneMgr, mCamera);
	mCameraListener = new CameraListener(mWindow, mCamera);
	static_cast<CameraListener*> (mCameraListener)->setCharacter(vehicle);
	static_cast<CameraListener*> (mCameraListener)->setExtendedCamera(exCamera);
	mCameraListener->instantUpdate();	
	
	// create the obstacle
	//obs = new ObstacleForFun();
	//obs->createObstacle(this);
	
	this->addStaticTrimesh("GroundsceneMesh",
		"terrain_ground.mesh",
		Ogre::Vector3(0, 0, 0), 
		Quaternion::IDENTITY,
		0.1f, 
		0.8f);

	//createSimpleSky();	
	//createSimpleWater();
	createHydraxSimulation();
	
	//mBulletWorld->getDebugDrawer()->setDrawWireframe(true);
	//mBulletWorld->setShowDebugShapes(true);
}

//-------------------------------------------------------------------------------------
void AZBullet::createHydraxSimulation()
{	
	// Create Hydrax object
	mHydrax = new Hydrax::Hydrax(mSceneMgr, mCamera, mCamera->getViewport());

	// Create our projected grid module  
	Hydrax::Module::ProjectedGrid *mModule 
		= new Hydrax::Module::ProjectedGrid(
		mHydrax,	
		new Hydrax::Noise::Perlin(),
		Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),	
		Hydrax::MaterialManager::NM_VERTEX,	
		Hydrax::Module::ProjectedGrid::Options());	

	
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));		// Set our module

	mHydrax->loadCfg("HydraxDemo.hdx");
	mHydrax->create();

	mHydrax->getMaterialManager()->addDepthTechnique(
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))
		->createTechnique());
}

//-------------------------------------------------------------------------------------
void AZBullet::createSimpleSky()
{
	Ogre::Plane skyPlane;
	skyPlane.d = 100;
	skyPlane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	//mSceneMgr->setSkyDome(true, "Sky/EarlyMorning", 5, 8, 1500);
}

//-------------------------------------------------------------------------------------
void AZBullet::createSimpleWater()
{	
	// this is to add water pond effect
	Ogre::Plane plane01(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane01, 1000, 1000, 20, 20, true, 1, 20, 20, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entWater01 = mSceneMgr->createEntity("WaterPlane01", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode("Water", Ogre::Vector3(500, 30, 500))->attachObject(entWater01);

	entWater01->setMaterialName("Examples/WaterStream3");
	entWater01->setCastShadows(false);	
	
	// this is to add water pond effect
	Ogre::Plane plane02(Ogre::Vector3::UNIT_Y, 0);

	/*	
	Ogre::MeshManager::getSingleton().createPlane("ground", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane02, 
		1000, 
		1000, 
		1, 
		1, 
		true, 
		1, 
		5, 
		5, 
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entWater02 = mSceneMgr->createEntity("WaterPlane02", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode("Water02", Ogre::Vector3(500, 5, 500))->attachObject(entWater02);

	entWater02->setMaterialName("Examples/WaterStream2");
	entWater02->setCastShadows(false);	
	*/
}


bool AZBullet::frameRenderingQueued(const Ogre::FrameEvent& arg)
{
	if(!BaseApplication::frameRenderingQueued(arg)) { return false; }

	Ogre::Real elapsedTime = arg.timeSinceLastFrame;
	
	mHydrax->update(elapsedTime);
	mBulletWorld->stepSimulation(elapsedTime);	
	//this->repositionCamera();	
	this->vehicle->updatePerFrame(arg.timeSinceLastFrame);	

	return true;
}

// -------------------------------------------------------------------------
bool AZBullet::frameStarted(const FrameEvent& evt)
{
	Ogre::Real elapsedTime = evt.timeSinceLastFrame;	
	mCameraListener->frameStarted(evt);
	return true;
}

// -------------------------------------------------------------------------
bool AZBullet::frameEnded(const FrameEvent& evt)
{
	Ogre::Real elapsedTime = evt.timeSinceLastFrame;
	return true; 
}

//-------------------------------------------------------------------------------------
// when mouse dragged
bool AZBullet::mouseMoved(const OIS::MouseEvent& arg)
{
	if(!BaseApplication::mouseMoved(arg)) { return false; }

	Ogre::Real screenWidth = hViewPort->getWidth();
	Ogre::Real screenHeight = hViewPort->getHeight();

	Ogre::Real offsetX = (float)arg.state.X.abs / (float)arg.state.width;
	Ogre::Real offsetY = (float)arg.state.Y.abs / (float)arg.state.height;

	//using namespace Hikari;
	//bool val = menu->hikariMgr->injectMouseMove(arg.state.X.abs, arg.state.Y.abs) ||  menu->hikariMgr->injectMouseWheel(arg.state.Z.rel);

	//if the left mouse button is held down
	if(bLMouseDown)
	{		
	}
	else if(bRMouseDown)	//if the right mouse button is held down, be rotate the camera with the mouse
	{		
		mCamera->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
		mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * mRotateSpeed));
	}

	return true;
}

//-------------------------------------------------------------------------------------
// when a mouse button is pressed
bool AZBullet::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{	
	if(id == OIS::MB_Left) { bLMouseDown = true; }
	else if(id == OIS::MB_Right) { bRMouseDown = true; }
		
	//return  menu->hikariMgr->injectMouseDown(id); 
	return true;
}

//-------------------------------------------------------------------------------------
// when a mouse button is released
bool AZBullet::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	if(id  == OIS::MB_Left) { bLMouseDown = false; }
	else if(id == OIS::MB_Right) { bRMouseDown = false; }

	//return  menu->hikariMgr->injectMouseUp(id);
	return true;
}

//------------------------------------------------------------------------------------- 
// when keyboard pressed
bool AZBullet::keyPressed(const OIS::KeyEvent& arg)
{
	if(!BaseApplication::keyPressed(arg)) { return false; }

	if(arg.key == OIS::KC_UP     || 
		arg.key == OIS::KC_RIGHT || 
		arg.key == OIS::KC_LEFT  || 
		arg.key == OIS::KC_DOWN
		)
	{
	}
	/*else if(arg.key == OIS::KC_W)
	{
	}
	else if(arg.key == OIS::KC_A)
	{
	}
	else if(arg.key == OIS::KC_S)
	{
	}
	else if(arg.key == OIS::KC_D)
	{
	}*/
	else { mCameraMan->injectKeyDown(arg); }

	vehicle->keyPressed(arg);

	return true;
}

//------------------------------------------------------------------------------------- 
// when keyboard pressed
bool AZBullet::keyReleased(const OIS::KeyEvent& arg)
{
	if(!BaseApplication::keyReleased(arg)) { return false; }

	if(arg.key == OIS::KC_UP     || 
		arg.key == OIS::KC_RIGHT || 
		arg.key == OIS::KC_LEFT  || 
		arg.key == OIS::KC_DOWN )
	{
	}
	/*else if(arg.key == OIS::KC_W)
	{
	}
	else if(arg.key == OIS::KC_A)
	{
	}
	else if(arg.key == OIS::KC_S)
	{
	}
	else if(arg.key == OIS::KC_D)
	{
	}*/
	else { mCameraMan->injectKeyUp(arg); }

	vehicle->keyReleased(arg);
	return true;
}

//-------------------------------------------------------------------------------------
void AZBullet::repositionCamera()
{
	//Ogre::Vector3 camPos = mCamera->getRealPosition();
	//Ogre::Vector3 camPos = exCamera->getCameraPosition();
	Ogre::Vector3 camPos = Ogre::Vector3::ZERO;

	Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
	mRayScnQuery->setRay(cameraRay);

	// Perform the scene query
	Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr = result.begin();

	// Get the results, set the camera height
	if (itr != result.end() && itr->worldFragment)
	{
		Ogre::Real terrainHeight = itr->worldFragment->singleIntersection.y;
		if( Ogre::Math::Abs(terrainHeight - camPos.y) > 1.0f )
		{
			//std::cout << itr->worldFragment->singleIntersection.y << "-";
			//std::cout << camPos.y << "\n";
			//std::cout << "whoops\n";
			//exCamera->instantUpdate(Ogre::Vector3(camPos.x, terrainHeight + 1.0f, camPos.z));
			//mCamera->setPosition( camPos.x, terrainHeight + 0.5f, camPos.z );
		}
	}

	
}

//-------------------------------------------------------------------------------------
void AZBullet::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	this->bLMouseDown = false;
	this->bRMouseDown = false;
	this->mRotateSpeed = 0.1f;
	this->mName = "AZBullet";	

	mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());	
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#ifdef _DEBUG
		int main()
	#else
		INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
	#endif	
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        AZBullet app;

        try { app.go(); } 
		catch( Ogre::Exception& e ) 
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif