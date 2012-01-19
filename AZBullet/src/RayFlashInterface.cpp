
#include "Stdafx.h"
#include "AZBullet.h"
#include "RayFlashInterface.h"
//-------------------------------------------------------------------------------------
RayFlashInterface::~RayFlashInterface(void)
{
	
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::update(Ogre::RenderWindow* mWindow)
{
	hikariMgr->update();	
	mainMenuControl->callFunction("setFPS", Hikari::Args((int)mWindow->getAverageFPS()));
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setupHikari(void)
{
	using namespace Hikari;

	isMenuOpen = false;
	isGameOver = false;

	hikariMgr = new HikariManager("..\\..\\media\\flash\\RayRayRayUI\\bin");

	mainMenuControl = hikariMgr->createFlashOverlay("Menu", rayApp->hViewPort, 500, 300, Position(TopLeft));

	mainMenuControl->load("RayRayRayUI.swf");
	mainMenuControl->setDraggable(false);
	mainMenuControl->setTransparent(true, true);
	mainMenuControl->hide();

	mainMenuControl->bind("Exit", FlashDelegate(this, &RayFlashInterface::onExitClick));
	mainMenuControl->bind("MenuState", FlashDelegate(this, &RayFlashInterface::onMenuStateChange));
	mainMenuControl->bind("OceanSimToggle", FlashDelegate(this, &RayFlashInterface::onOceanSimToogle));
	mainMenuControl->bind("WeatherOption", FlashDelegate(this, &RayFlashInterface::onWeatherOption));
	mainMenuControl->bind("Camera", FlashDelegate(this, &RayFlashInterface::onCameraChangePosition));
	mainMenuControl->bind("Compositor", FlashDelegate(this, &RayFlashInterface::onCompositorChange));	
	//mainMenuControl->bind("Curve", FlashDelegate(this, &RayFlashInterface::onCurveChange));

	objectControls = hikariMgr->createFlashOverlay("Tite", rayApp->hViewPort, 600, 538, Position(Center));
	objectControls->load("SaturnVTitle.swf");
	objectControls->setDraggable(false);
	objectControls->setTransparent(true, true);
	objectControls->bind("StartTitle", FlashDelegate(this, &RayFlashInterface::onStartTitle));
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::showObjectControl(int xMPos, int yMPos, int height)
{
	using namespace Hikari;

	//objectControls->callFunction("setVal", Hikari::Args(height));
	//objectControls->show();
	//objectControls->setPosition(Position(TopLeft, xMPos, yMPos));

	oCPos.x = xMPos;
	oCPos.y = yMPos;
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setGameOver()
{
	if(!isGameOver)
	{
		objectControls->callFunction("SetGameOver", Hikari::Args((int)0));
		isGameOver = true;
	}
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::hideObjectControl()
{
	//objectControls->hide();
}

//-------------------------------------------------------------------------------------
bool RayFlashInterface::isInsideMenu(int mouseX, int mouseY)
{
	if(isMenuOpen && 
		mouseX >= 0 && 
		mouseX <= 170 && 
		mouseY >= 0 && 
		mouseY <= 220)
	{
		return true;
	}
	else if (!isMenuOpen && 
		mouseX >= 0 && 
		mouseX <= 60 && 
		mouseY >= 0 && 
		mouseY <= 60)
	{
		return true;
	}
	/*
	else if(objectControls->getVisibility() &&
		mouseX >= oCPos.x &&
		mouseX <= (oCPos.x + 170) &&
		mouseY >= oCPos.y &&
		mouseY <= (oCPos.y + 50))
	{
		return true;
	}
	*/
	return false;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onOceanSimToogle(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString();
	this->rayApp->toggleOceanSimulation();

	return FLASH_VOID;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	this->rayApp->shutdownApp();

	return FLASH_VOID;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onWeatherOption(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "morning")
	{
		this->rayApp->setWeather(0);
	}
	else if(text == "evening")
	{
		this->rayApp->setWeather(1);
	}
	else if(text == "cloudy")
	{
		this->rayApp->setWeather(2);
	}

	return FLASH_VOID;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onCameraChangePosition(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "1")
	{
		this->rayApp->changeCameraPosition(0);
	}
	else if(text == "2")
	{
		this->rayApp->changeCameraPosition(1);
	}
	else if(text == "3")
	{
		this->rayApp->changeCameraPosition(2);
	}
	else if(text == "4")
	{
		this->rayApp->changeCameraPosition(3);
	}
	else if(text == "5")
	{
		this->rayApp->changeCameraPosition(4);
	}

	return FLASH_VOID;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onCompositorChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "0")
	{
		this->rayApp->changeCompositor(0);
	}
	else if(text == "1")
	{
		this->rayApp->changeCompositor(1);
	}
	else if(text == "2")
	{
		this->rayApp->changeCompositor(2);
	}
	else if(text == "3")
	{
		this->rayApp->changeCompositor(3);
	}

	return FLASH_VOID;
}

//-------------------------------------------------------------------------------------
Hikari::FlashValue RayFlashInterface::onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "open")
	{
		isMenuOpen = true;
	}
	else if(text == "close")
	{
		isMenuOpen = false;
	}

	return FLASH_VOID;
}


Hikari::FlashValue RayFlashInterface::onStartTitle(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;

	mainMenuControl->show();

	return FLASH_VOID;
}