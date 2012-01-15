/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
/*
OgreBulletListener.h
-------------
A basic test framework that minimize code in each test scene listener.
*/
#ifndef _OgreBulletListener_H_
#define _OgreBulletListener_H_

#include "OgreBulletDynamics.h"

#include "OgreBulletInputListener.h"
#include "OgreBulletGuiListener.h"

//#define BASIC_HELP_INFO0 "Use F1, F2, F3, F4"
//#define BASIC_HELP_INFO1 "B,N,G,H to Throw a Cube, Sphere, Cone, Cylinder"
//#define BASIC_HELP_INFO2 "J,K,I,U to Drop  a Cube, Sphere, Cone, Cylinder"
//#define BASIC_HELP_INFO3 ""
//#define BASIC_HELP_INFO4 "left click to drag"
//#define BASIC_HELP_INFO5 "right to camera move"
//#define BASIC_HELP_INFO6 "middle for impulse"

enum QueryFlags
{
	ANY_QUERY_MASK					= 1<<0,
	RAGDOLL_QUERY_MASK				= 1<<1,
	GEOMETRY_QUERY_MASK				= 1<<2,
	VEHICLE_QUERY_MASK				= 1<<3,
	STATIC_GEOMETRY_QUERY_MASK		= 1<<4
};

class OgreBulletApplication;

/*
The base Test class, is also able to listen for collisions and thus change the contact properties
*/
class OgreBulletListener 
{
public:

	// Constructor/destructor
    OgreBulletListener();
    virtual ~OgreBulletListener(){};
    //virtual void bulletInit(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application);

    virtual void bulletShutdown();

    //void setBulletPhysicGUI();
    //void setBulletBasicLight();

    //const BULLET_KEY_CODE getNextKey() const {return mActivationKeyCode;};
    //void setNextKey(BULLET_KEY_CODE code){mActivationKeyCode = code;};

    //void setBulletInfoText();

    //const Ogre::String getName() {return mName;}

    //virtual bool bulletFrameStarted(Ogre::Real elapsedTime);
    //virtual bool bulletFrameEnded(Ogre::Real elapsedTime);

    //bool checkIfEnoughPlaceToAddObject(float maxDist);
    //void throwDynamicObject(BULLET_KEY_CODE key);
    void dropDynamicObject(int key, Ogre::Vector3 vec);

    //OgreBulletInputListener *getBulletInputListener(){return mInputListener;}

    //virtual void bulletMouseMoved();

    //virtual void bulletButton0Pressed();
    //virtual void bulletButton1Pressed();
    //virtual void bulletButton2Pressed();

    //virtual void bulletButton0Released();
    //virtual void bulletButton1Released();
    //virtual void bulletButton2Released();

    //virtual void bulletKeyPressed(BULLET_KEY_CODE key);
    //virtual void bulletKeyReleased(BULLET_KEY_CODE key);

    //bool *getBoolActivator(){return &mActivationBool;}

    //void setDebugText(const Ogre::String &debugText){mDebugText = debugText;}

    void initWorld (const Ogre::Vector3 &gravityVector = Ogre::Vector3 (0,-9.81,0), 
                    const Ogre::AxisAlignedBox &bounds = Ogre::AxisAlignedBox (Ogre::Vector3 (-10000, -10000, -10000),
                                                                               Ogre::Vector3 (10000,  10000,  10000)));

    void addGround();

    OgreBulletDynamics::RigidBody *addCube(const Ogre::String instanceName,
        const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
        const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
        const Ogre::Real bodyMass);

    OgreBulletDynamics::RigidBody *addCylinder(const Ogre::String instanceName,
        const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
        const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
        const Ogre::Real bodyMass);

    OgreBulletDynamics::RigidBody *addSphere(const Ogre::String instanceName,
        const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Real radius,
        const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
        const Ogre::Real bodyMass);


    OgreBulletDynamics::RigidBody *addCone(const Ogre::String instanceName,
        const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
        const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
        const Ogre::Real bodyMass);

    OgreBulletDynamics::RigidBody *addStaticTrimesh(const Ogre::String &instanceName,
                                                        const Ogre::String &meshName,
                                                        const Ogre::Vector3 &pos, 
                                                        const Ogre::Quaternion &q, 
                                                        const Ogre::Real bodyRestitution, 
                                                        const Ogre::Real bodyFriction,
                                                        const bool castShadow = true);

    OgreBulletDynamics::RigidBody *addStaticPlane( const Ogre::Real bodyRestitution, 
                                                   const Ogre::Real bodyFriction);
    
    
    //void getDebugLines();

    //OgreBulletDynamics::RigidBody* getBodyUnderCursorUsingBullet(Ogre::Vector3 &intersectionPoint, Ogre::Ray &rayTo);
    //OgreBulletDynamics::RigidBody* getBodyUnderCursorUsingOgre(Ogre::Vector3 &intersectionPoint, Ogre::Ray &rayTo);

public:
	std::deque<Ogre::Entity *>                          mEntities;
	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;
	Ogre::SceneManager      *mBulletSceneMgr;
	OgreBulletDynamics::DynamicsWorld *mBulletWorld;

protected:
    static size_t mNumEntitiesInstanced;
    
    //Ogre::RenderWindow      *mBulletWindow;
    //Ogre::Root              *mBulletRoot;
    //Ogre::SceneManager      *mBulletSceneMgr;

    //int mCurrentShadowTechnique;
    //Ogre::Light *mSunLight;
	//Ogre::Light *mLight;
	//Ogre::Light *mLight2;


    //Ogre::Camera            *mBulletCamera;
    //Ogre::Radian             mBulletCameraRotX;
    //Ogre::Radian             mBulletCameraRotY;
    //float                    mBulletCameraMove;
    //Ogre::Vector3            mBulletCameraTrans;

    //OgreBulletDynamics::DynamicsWorld *mBulletWorld;
    //OgreBulletApplication *mBulletApplication;

    //std::deque<Ogre::Entity *>                          mEntities;
    //std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
    //std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

    //bool                    mStatsOn;
    //bool                    mQuit;
    //bool                    mDoOnestep;

    //float                    mShootSpeed;
    //float                    mImpulseForce;
    //bool                     mPaused;


    //bool                    mWireFrame;
    //bool                    mDrawAabb;
    //bool                    mDrawFeaturesText;
    //bool                    mDrawContactPoints;
    //bool                    mNoDeactivation;
    //bool                    mNoHelpText;
    //bool                    mDrawText;
    //bool                    mProfileTimings;
    //bool                    mEnableSatComparison;
    //bool                    mDisableBulletLCP;
    //bool                    mEnableCCD;


   //BetaGUI::StaticText*  mFpsStaticText;


   // picking Drag&Drop, impulse
   //OgreBulletDynamics::RigidBody        *mPickedBody;
   //OgreBulletDynamics::TypedConstraint  *mPickConstraint;
   //Ogre::Vector3                        mOldPickingPos;
   //Ogre::Vector3                        mOldPickingDist;
   //OgreBulletCollisions::CollisionClosestRayResultCallback  *mCollisionClosestRayResultCallback;

   //OgreBulletCollisions::DebugLines    *mDebugRayLine;
   //Ogre::RaySceneQuery                 *mRayQuery;
   
   //BULLET_KEY_CODE mActivationKeyCode;
   //bool mActivationBool;

   //OgreBulletInputListener *mInputListener;
   //OgreBulletGuiListener *mGuiListener;

   //Ogre::String mDebugText;

   //Ogre::String mName;
   //std::vector<Ogre::String> mHelpKeys;
   //void updateStats();
};

#endif

