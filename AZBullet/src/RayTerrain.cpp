
#include "Stdafx.h"
#include "RayTerrain.h"

#include <LinearMath/btVector3.h>
#include <LinearMath/btDefaultMotionState.h>
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "Shapes/OgreBulletCollisionsTerrainShape.h"
#include "OgreBulletDynamicsRigidBody.h"

//-------------------------------------------------------------------------------------
// constructor
RayTerrain::RayTerrain(void)
{
}
//-------------------------------------------------------------------------------------
// destructor
RayTerrain::~RayTerrain(void)
{
	OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}

//-------------------------------------------------------------------------------------
void RayTerrain::integrateBullet(SceneManager* mSceneMgr, 
								   OgreBulletDynamics::DynamicsWorld *mBulletWorld, 
								   std::deque<OgreBulletDynamics::RigidBody *> mBodies,
								   std::deque<OgreBulletCollisions::CollisionShape *>  mShapes
								   )
{
	
	Ogre::Terrain* pTerrain = mTerrainGroup->getTerrain(0, 0);	
	float * hData = pTerrain->getHeightData(); 
	Vector3 pos = pTerrain->getPosition();

	float *pDataConvert = new float[pTerrain->getSize() *pTerrain->getSize()];
	for (int i = 0; i < pTerrain->getSize(); i++)
		memcpy(pDataConvert + pTerrain->getSize() * i, 
		hData + pTerrain->getSize() * (pTerrain->getSize() - i - 1),
		sizeof(float) * (pTerrain->getSize()));

	float w = pTerrain->getSize();
	float h = pTerrain->getSize();
	
	float* data = pDataConvert;
	float minH = pTerrain->getMinHeight();
	float maxH = pTerrain->getMaxHeight();
	float scale = pTerrain->getWorldSize() / (pTerrain->getSize() - 1);
	float heightScale = (maxH - minH) / 2.0f;

	Vector3 localScaling = Vector3(scale, heightScale, scale);

	mTerrainShape = new HeightmapCollisionShape (
		w, 
		h, 
		localScaling, 
		pDataConvert, 
		true);

	RigidBody *defaultTerrainBody = new RigidBody(
		"TerrainABC", 
		mBulletWorld);

	const float      terrainBodyRestitution  = 0.1f;
	const float      terrainBodyFriction     = 0.8f;

	Ogre::Vector3 terrainShiftPos( (localScaling.x * (w - 1) / 2), 0, (localScaling.z * (h - 1) / 2));
	//terrainShiftPos.y = terrainScale.y / 2 * terrainScale.y;

	Ogre::SceneNode* pTerrainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
	defaultTerrainBody->setStaticShape (pTerrainNode, mTerrainShape, terrainBodyRestitution, terrainBodyFriction, terrainShiftPos);

	mBodies.push_back(defaultTerrainBody);
	mShapes.push_back(mTerrainShape);

	/*
	groundShape = new btHeightfieldTerrainShape(w, h, data, 1, minH,maxH,1, PHY_FLOAT, true);
	groundShape->setUseDiamondSubdivision(true);
	groundShape->setLocalScaling(localScaling);
	mShapes.push_back(groundShape);	

	btDefaultMotionState* state = new btDefaultMotionState();
	btRigidBody* rigidBody = new btRigidBody(0, state, groundShape);
	rigidBody->getWorldTransform().setOrigin(btVector3(scale*(w-1) / 2, heightScale / 2 *heightScale,scale* (w-1) / 2));
	Ogre::Quaternion q = Ogre::Quaternion::IDENTITY;
	rigidBody->getWorldTransform().setRotation(btQuaternion(q.x, q.y, q.z, q.w) );
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	mBulletWorld->addRigidBody(rigidBody);
	*/
	/*
	Ogre::Terrain* terrain = mTerrainGroup->getTerrain(0, 0);
	unsigned page_size = terrain->getLayerBlendMapSize();

	std::cout << page_size << "rrrrterrr=======\n";

	float *heights = new float [page_size*page_size];
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);

	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			heights[x + y * page_size] = terrain->getHeightAtTerrainPosition(tx, ty);
		}
	}

	
	Ogre::Vector3 terrainScale(1000.0f / (page_size-1),
		75,
		1000.0f / (page_size-1));

	mTerrainShape = new HeightmapCollisionShape (
		page_size, 
		page_size, 
		terrainScale, 
		heights, 
		true);

	RigidBody *defaultTerrainBody = new RigidBody(
		"TerrainABC", 
		mBulletWorld);

	const float      terrainBodyRestitution  = 0.1f;
	const float      terrainBodyFriction     = 0.8f;

	Ogre::Vector3 terrainShiftPos( (terrainScale.x * (page_size - 1) / 2), 0, (terrainScale.z * (page_size - 1) / 2));

	terrainShiftPos.y = terrainScale.y / 2 * terrainScale.y;

	Ogre::SceneNode* pTerrainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
	defaultTerrainBody->setStaticShape (pTerrainNode, mTerrainShape, terrainBodyRestitution, terrainBodyFriction, terrainShiftPos);

	mBodies.push_back(defaultTerrainBody);
	mShapes.push_back(mTerrainShape);
	*/
}

//-------------------------------------------------------------------------------------
// init function to create terrain
void RayTerrain::createTerrain(Ogre::SceneManager* mSceneMgr, Ogre::Light* light)
{
	this->mSceneMgr = mSceneMgr;

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	//mTerrainGlobals->setCastsDynamicShadows(true);
	//mTerrainGlobals->setLightMapDirection(light->getDirection());
												// scene_manager	align				   size world_size
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(this->mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 65, 1000.f);
	
    mTerrainGroup->setFilenameConvention(Ogre::String("RayRayRay"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
	
    configureTerrainDefaults(light);
 
    for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);
 
    // sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);
	
    if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;			
			t->getMaterial()->setReceiveShadows(true);
            initBlendMaps(t);
        }
    }
 
    mTerrainGroup->freeTemporaryResources();
	
	/*
	Ogre::Terrain*terrain = mTerrainGroup->getTerrain(0,0); //0,0 is where my terrain was created
	terrain->getTerrainNormalMap()->convertToImage(image);

	image.save("normalMap.png");
	image.load("normalMap.png", "General");
	*/
}

//-------------------------------------------------------------------------------------
// getter for mTerrainsImported
//
bool RayTerrain::getTerrainsImported(void)
{
	return this->mTerrainsImported;
}

//-------------------------------------------------------------------------------------
// setter for mTerrainsImported
void RayTerrain::setTerrainsImported(bool val)
{
	this->mTerrainsImported = val;
}

//-------------------------------------------------------------------------------------
// getter for mTerrainGlobals
Ogre::TerrainGlobalOptions* RayTerrain::getTerrainGlobals(void)
{
	return this->mTerrainGlobals;
}

//-------------------------------------------------------------------------------------
// getter for mTerrainGroup
Ogre::TerrainGroup* RayTerrain::getTerrainGroup(void)
{
	return this->mTerrainGroup;
}


//-------------------------------------------------------------------------------------
// get image
void RayTerrain::getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("Terrain_02.png", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX) img.flipAroundY();
    if (flipY) img.flipAroundX();
	
}
//-------------------------------------------------------------------------------------
// defining the terrain
void RayTerrain::defineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
//-------------------------------------------------------------------------------------
// init blend map
void RayTerrain::initBlendMaps(Ogre::Terrain* terrain)
{	
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 40;
    Ogre::Real fadeDist0 = 20;
    Ogre::Real minHeight1 = 20;
    Ogre::Real fadeDist1 = 5;
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}

//-------------------------------------------------------------------------------------
// terrain configuration
void RayTerrain::configureTerrainDefaults(Ogre::Light* light)
{
	// Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);
	//mTerrainGlobals->setCastsDynamicShadows(true);
	
    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
	
    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 1000.0f;
	defaultimp.inputScale = 75;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
	
	// textures	
    defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 10;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 20;
    defaultimp.layerList[2].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("grass_green-01_normalheight.dds");
}