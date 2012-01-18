
#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager(void)
{
	engine = NULL;
	bgmSound = NULL;
	victorySound = NULL;

	bgmInitiated = false;
	victoryInitiated = false;
	toTheMoonInitiated = false;
	victoryCounter = 0.0f;
}

SoundManager::~SoundManager(void)
{
	engine->removeAllSoundSources(); 
	engine->drop();
}

void SoundManager::createSound()
{
	engine = createIrrKlangDevice();
	
	if (!engine)
	{
		return ;
	}

	volume = 0.0f;
	bgmSound = engine->play2D("../../media/sounds/cowboy_bebop_rush.ogg", true);
	bgmInitiated = true;
	engine->setSoundVolume(volume);
}

void SoundManager::playVictory()
{
	if(!victoryInitiated)
	{
		victorySound = engine->play2D("../../media/sounds/game_complete.ogg", false);
		victoryInitiated = true;
	}
}

void SoundManager::update(Ogre::Real elapsedTime)
{
	if(volume <= 0.5f && !victoryInitiated) 
	{
		volume += elapsedTime * 0.01;
		engine->setSoundVolume(volume);
	}

	//if(victoryInitiated)
	//{
	//	victoryCounter += elapsedTime;

	//	if(victoryCounter >= 2.0f)
	//	{
	//		volume -= elapsedTime;
	//		engine->setSoundVolume(volume);

	//		//std::cout <<  "vol " << volume << "\n";
	//		//std::cout <<  "ela " << elapsedTime << "\n";
	//	}

	//	if(volume <= 0 && !toTheMoonInitiated)
	//	{
	//		volume = 0.5f;
	//		//engine->stopAllSounds();
	//		//bgmSound->setVolume(0);
	//		engine->setSoundVolume(volume);
	//		toTheMoonSound = engine->play2D("../../media/sounds/fly_me_to_the_moon.ogg", true);
	//		toTheMoonInitiated = true;
	//	}

	//}

	engine->update();
}