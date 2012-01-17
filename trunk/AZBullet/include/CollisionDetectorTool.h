
#ifndef __CollisionDetectorTool_h_
#define __CollisionDetectorTool_h_

#include "Ogre.h"

#include "OgreBulletDynamicsRigidBody.h"

#include "BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
#include "BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btPointCollector.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

// declaration of callback
struct btDrawingResult : public btCollisionWorld::ContactResultCallback
{
	short int collisionResult;

	virtual btScalar addSingleResult(btManifoldPoint& cp,   
		const btCollisionObject* colObj0,
		int partId0,
		int index0,
		const btCollisionObject* colObj1,
		int partId1,
		int index1)
	{
		btVector3 ptA = cp.getPositionWorldOnA();
		btVector3 ptB = cp.getPositionWorldOnB();
		btVector3 norm = cp.m_normalWorldOnB;

		collisionResult = 1;

		return 0;
	}
};

class CollisionDetectorTool
{
protected:
	OgreBulletDynamics::DynamicsWorld *mBulletWorld;

public:
	CollisionDetectorTool(OgreBulletDynamics::DynamicsWorld *mBulletWorld)
	{
		this->mBulletWorld = mBulletWorld;
	}

	~CollisionDetectorTool()
	{
	}

	bool checkCollision(btRigidBody* objectA, btRigidBody* objectB)
	{
		btDrawingResult renderCallback;
		mBulletWorld->getBulletDynamicsWorld()->contactPairTest(objectA,objectB, renderCallback);
		
		if(renderCallback.collisionResult == 1) return true;

		return false;
	}
};

#endif
