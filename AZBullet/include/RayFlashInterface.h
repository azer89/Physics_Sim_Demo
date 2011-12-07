
//class AZBullet;

#ifndef __RayFlashInterface_h_
#define __RayFlashInterface_h_

#include "Hikari.h"

class AZBullet;

class RayFlashInterface
{

public:
	RayFlashInterface(AZBullet* rayApp):hikariMgr(0)
	{
		this->rayApp = rayApp;
	}
	virtual ~RayFlashInterface(void);

	void setupHikari();
	void update(Ogre::RenderWindow* mWindow);
	void showObjectControl(int xMPos, int yMPos, int height);
	void hideObjectControl();
	bool isInsideMenu(int mouseX, int mouseY);

	Hikari::HikariManager* hikariMgr;
	//Hikari::HikariManager* objectHikariMgr;

private:

	Hikari::FlashControl* mainMenuControl;
	//Hikari::FlashControl* objectControls;

	AZBullet* rayApp;
	bool isMenuOpen;
	Ogre::Vector2 oCPos;

	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to close app
	Hikari::FlashValue onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener when menu opened/closed
	//Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to startthe train
	//Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to stop the train	
	//Hikari::FlashValue onCurveChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener to change curve type	
	//Hikari::FlashValue onNumTrainChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener to change number of train
	//Hikari::FlashValue onHeightChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener to change pole's height
};

#endif