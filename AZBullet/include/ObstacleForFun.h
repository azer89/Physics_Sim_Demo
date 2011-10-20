
#include "Stdafx.h"
#include "ClassDefine.h"
#include "OgreBulletListener.h"

class ObstacleForFun
{
public:
	ObstacleForFun(void);
	virtual ~ObstacleForFun(void);

	void createObstacle(OgreBulletListener* listener, Ogre::Vector3 shift);
};