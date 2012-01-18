
#ifndef __FlagFlag_h_
#define __FlagFlag_h_


#include "Ogre.h"
#include "OgreBulletListener.h"

using namespace Ogre;

class Flag
{

protected:
	Ogre::AnimationState* ani01;
	Ogre::AnimationState* ani02;

public:
	Flag(void);
	virtual ~Flag(void);

	void createObject(OgreBulletListener *bulletListener);
	void updatePerFrame(Real elapsedTime);
};

#endif