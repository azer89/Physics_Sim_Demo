
#ifndef __SoundManager_h_
#define __SoundManager_h_


#include "Ogre.h"
#include "irrKlang.h"

using namespace irrklang;

// Handling sound using irrKlang library
class SoundManager
{
protected:
	ISoundEngine* engine;			// irrKlang engine
	ik_f32 volume;					// current volume

	ISound* bgmSound;
	ISound* victorySound;
	ISound* toTheMoonSound;
	Ogre::Real victoryCounter;

	bool bgmInitiated;
	bool victoryInitiated;
	bool toTheMoonInitiated;

public:
	SoundManager(void);
	virtual ~SoundManager(void);

	void createSound();
	void playVictory();
	void update(Ogre::Real elapsedTime);
};

#endif