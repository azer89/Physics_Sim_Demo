
#ifndef __SoundManager_h_
#define __SoundManager_h_


#include "Ogre.h"
#include "irrKlang.h"

using namespace irrklang;

class SoundManager
{
protected:
	ISoundEngine* engine; 
	ik_f32 volume;

public:
	SoundManager(void);
	virtual ~SoundManager(void);

	void createSound();
	void update(Ogre::Real elapsedTime);
};

#endif