
#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager(void)
{
	engine = 0;
}

SoundManager::~SoundManager(void)
{
	engine->drop();
}

void SoundManager::createSound()
{
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		return ;
	}

	volume = 0.5f;
	engine->play2D("../../media/sounds/cowboy_bebop_rush.ogg", true);
	engine->setSoundVolume(volume);
}

void SoundManager::update(Ogre::Real elapsedTime)
{
	/*if(volume <= 0.5f) 
	{
		volume += (ik_f32)(elapsedTime * 0.5f);
		engine->setSoundVolume(volume);
	}*/

	//engine->update();

}