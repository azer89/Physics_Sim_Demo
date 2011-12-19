
#ifndef __ObstacleForFun_h_
#define __ObstacleForFun_h_

#include "OgreBulletListener.h"

class ObstacleForFun
{
public:
	ObstacleForFun(void);
	virtual ~ObstacleForFun(void);

	void createObject(OgreBulletListener* listener);
};

#endif