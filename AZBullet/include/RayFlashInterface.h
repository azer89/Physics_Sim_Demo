
//class AZBullet;

#ifndef __RayFlashInterface_h_
#define __RayFlashInterface_h_

#include "Hikari.h"

// Forward declaration
class AZBullet;

// Main class for UI Interface
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
	void setGameOver();

	Hikari::HikariManager* hikariMgr;
	//Hikari::HikariManager* objectHikariMgr;

private:

	bool isGameOver;
	Hikari::FlashControl* mainMenuControl;
	Hikari::FlashControl* objectControls;

	AZBullet* rayApp;
	bool isMenuOpen;
	Ogre::Vector2 oCPos;

	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);				// event listener to close app
	Hikari::FlashValue onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);			// event listener when menu opened/closed
	Hikari::FlashValue onOceanSimToogle(Hikari::FlashControl* caller, const Hikari::Arguments& args);			// hydrax option
	Hikari::FlashValue onWeatherOption(Hikari::FlashControl* caller, const Hikari::Arguments& args);			// weather option
	Hikari::FlashValue onCameraChangePosition(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onCompositorChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	
	Hikari::FlashValue onStartTitle(Hikari::FlashControl* caller, const Hikari::Arguments& args);			// event listener to change curve type	
	//Hikari::FlashValue onHeightChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);			// event listener to change pole's height
};

#endif