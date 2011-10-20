
#include "Stdafx.h"
#include "TerrainManager.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

//-------------------------------------------------------------------------------------
// constructor
TerrainManager::TerrainManager(void)
{
	terrain_height = 45;
	terrain_Shift = Ogre::Vector3(750, terrain_height, 750);
}
//-------------------------------------------------------------------------------------
// destructor
TerrainManager::~TerrainManager(void)
{
}

//-------------------------------------------------------------------------------------
// init function to create terrain
void TerrainManager::createTerrain(SceneManager* mSceneMgr, 
								   OgreBulletDynamics::DynamicsWorld *mBulletWorld, 
								   std::deque<OgreBulletDynamics::RigidBody *> mBodies,
								   std::deque<OgreBulletCollisions::CollisionShape *>  mShapes
								   )
{
	mSceneMgr->setWorldGeometry("terrain.cfg");

	Ogre::ConfigFile config;

	config.loadFromResourceSystem("terrain.cfg", ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, "=", true);

	unsigned page_size = Ogre::StringConverter::parseUnsignedInt(config.getSetting( "PageSize" ));

	Ogre::Vector3 terrainScale(Ogre::StringConverter::parseReal( config.getSetting( "PageWorldX" ) ) / (page_size-1),
		Ogre::StringConverter::parseReal( config.getSetting( "MaxHeight" ) ),
		Ogre::StringConverter::parseReal( config.getSetting( "PageWorldZ" ) ) / (page_size-1));

	Ogre::String terrainfileName = config.getSetting( "Heightmap.image" );
	float *heights = new float [page_size*page_size];

	Ogre::Image terrainHeightMap;
	terrainHeightMap.load(terrainfileName, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);

	for(unsigned y = 0; y < page_size; ++y)
	{
		for(unsigned x = 0; x < page_size; ++x)
		{
			Ogre::ColourValue color = terrainHeightMap.getColourAt(x, y, 0);
			heights[x + y * page_size] = color.r;
		}
	}

	mTerrainShape = new HeightmapCollisionShape (
		page_size, 
		page_size, 
		terrainScale, 
		heights, 
		true);

	RigidBody *defaultTerrainBody = new RigidBody(
		"Terrain", 
		mBulletWorld);

	const float      terrainBodyRestitution  = 0.1f;
	const float      terrainBodyFriction     = 0.8f;

	Ogre::Vector3 terrainShiftPos( (terrainScale.x * (page_size - 1) / 2), 0, (terrainScale.z * (page_size - 1) / 2));

	terrainShiftPos.y = terrainScale.y / 2 * terrainScale.y;

	Ogre::SceneNode* pTerrainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
	defaultTerrainBody->setStaticShape (pTerrainNode, mTerrainShape, terrainBodyRestitution, terrainBodyFriction, terrainShiftPos);

	mBodies.push_back(defaultTerrainBody);
	mShapes.push_back(mTerrainShape);
}

