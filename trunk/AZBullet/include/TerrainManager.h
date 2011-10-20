#include "Stdafx.h"
#include "ClassDefine.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"
#include "Shapes/OgreBulletCollisionsTerrainShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class TerrainManager
{
public:
	float terrain_height;
	Ogre::Vector3 terrain_Shift;

public:
	TerrainManager(void);
	virtual ~TerrainManager(void);

	void createTerrain(SceneManager* mSceneMgr, 
		OgreBulletDynamics::DynamicsWorld *mBulletWorld, 
		std::deque<OgreBulletDynamics::RigidBody *> mBodies,
		std::deque<OgreBulletCollisions::CollisionShape *>  mShapes
		);
private:
	OgreBulletCollisions::HeightmapCollisionShape *mTerrainShape;
};