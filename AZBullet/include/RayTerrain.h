
#ifndef __RayTerrain_h_
#define __RayTerrain_h_

#include "Ogre.h"

//#include "Terrain/OgreTerrain.h"
//#include "Terrain/OgreTerrainGroup.h"
//
//#include "OgreBulletDynamicsWorld.h"
//
//#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
//#include "Shapes/OgreBulletCollisionsTerrainShape.h"

using namespace Ogre;
//using namespace OgreBulletCollisions;
//using namespace OgreBulletDynamics;

class RayTerrain
{
public:
	RayTerrain(void);
	virtual ~RayTerrain(void);

	/*void createTerrain(Ogre::SceneManager* mSceneMgr, Ogre::Light* light);
	void integrateBullet(Ogre::SceneManager* mSceneMgr, 
		OgreBulletDynamics::DynamicsWorld *mBulletWorld, 
		std::deque<OgreBulletDynamics::RigidBody *> mBodies,
		std::deque<OgreBulletCollisions::CollisionShape *>  mShapes
		);
	bool getTerrainsImported(void);
	void setTerrainsImported(bool val);
	Ogre::TerrainGlobalOptions* getTerrainGlobals(void);
	Ogre::TerrainGroup* getTerrainGroup(void);*/

private:
	//OgreBulletCollisions::HeightmapCollisionShape *mTerrainShape;
	//btHeightfieldTerrainShape *groundShape;

	//Ogre::TerrainGlobalOptions* mTerrainGlobals;	// terrain options
	//Ogre::TerrainGroup* mTerrainGroup;				// terrain group
	//Ogre::SceneManager* mSceneMgr;					// scene manager
	//bool mTerrainsImported;							// is already imported

	//void defineTerrain(long x, long y);
	//void initBlendMaps(Ogre::Terrain* terrain);
	//void configureTerrainDefaults(Ogre::Light* light);
	//void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);

};

#endif