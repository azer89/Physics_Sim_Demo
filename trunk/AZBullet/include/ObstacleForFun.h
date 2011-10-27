
#ifndef __ObstacleForFun_h_
#define __ObstacleForFun_h_

//#include "Stdafx.h"
//#include "ClassDefine.h"
#include "OgreBulletListener.h"

class ObstacleForFun
{
public:
	ObstacleForFun(void);
	virtual ~ObstacleForFun(void);

	void createObstacle(OgreBulletListener* listener);
};

#endif