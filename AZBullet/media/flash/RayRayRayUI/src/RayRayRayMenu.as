package  
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.display.DisplayObject;
	
	import com.greensock.*;
	import com.greensock.easing.*;
	/**
	 * ...
	 * @author Azer
	 */
	public class RayRayRayMenu  extends MovieClip
	{
		//private var startButton:StartButton;
		//private var stopButton:StopButton;
		private var exitButton:ExitButton;
		private var fpsInfo:FPSInfo;
		private var fpsText:TextField;
		private var menu01:MovieClip;
		private var menu02:MovieClip;
		private var gearIcon:GearIcon;
		private var isDown:Boolean = true;
		
		private var vehicleButton:VehicleButton;
		private var robotButton:RobotButton;
		private var shipButton:ShipButton;
		private var rocketButton:RocketButton;
		private var terrainButton:TerrainButton;
		
		private var oceanSimOption:OceanSimOption;
		private var prevOceanSim:PrevButton;
		private var nextOceanSim:NextButton;
		private var oceanSimText:TextField;
		private var oceanSimVal:Boolean;
		
		private var compOption:CompositorOption;
		private var prevComp:PrevButton;
		private var nextComp:NextButton;
		private var compText:TextField;
		private var compVal:int;
		
		private var weatherOption:WeatherOption;
		private var prevWeather:PrevButton;
		private var nextWeather:NextButton;
		private var weatherText:TextField;
		private var weatherVal:int;
		
		public function RayRayRayMenu()
		{
			this.setButton();
			this.setObjects();
			oceanSimVal = true;
			
			this.compVal = 0;
			ExternalInterface.addCallback("setFPS", setFPS);
		}
		
		private function setButton():void
		{
			menu02 = new MovieClip();
			menu02.x = -400;
			menu02.y = 0;
			menu02.alpha = 0;
			
			gearIcon = new GearIcon();
			gearIcon.x = 35;
			gearIcon.y = 35;
			gearIcon.addEventListener(MouseEvent.CLICK, onGearClick, false, 0, true);
			this.addChild(gearIcon);
			
			menu01 = new MovieClip();
			menu01.x = 0;
			menu01.y = -200;
			menu01.alpha = 0;
			
			fpsInfo = new FPSInfo();
			fpsInfo.x = 95;
			fpsInfo.y = 40;
			menu01.addChild(fpsInfo);
			
			weatherOption = new WeatherOption();
			weatherOption.x = 90;
			weatherOption.y = 70;
			menu01.addChild(weatherOption);
			
			oceanSimOption = new OceanSimOption();
			oceanSimOption.x = 90;
			oceanSimOption.y = 110;
			menu01.addChild(oceanSimOption);
			
			compOption = new CompositorOption();
			compOption.x = 90;
			compOption.y = 150;
			menu01.addChild(compOption);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 190;
			exitButton.addEventListener(MouseEvent.CLICK, onExitClick, false, 0, true);
			menu01.addChild(exitButton);
			
			this.addChild(menu01);
			
			// ---------------------------------------------------------------------
			vehicleButton = new VehicleButton();
			vehicleButton.x = 60 + 35 + 10;
			vehicleButton.y = 35;
			menu02.addChild(vehicleButton);
			
			robotButton = new RobotButton();
			robotButton.x = 60 * 2 + 35 + 10 * 2;
			robotButton.y = 35;
			menu02.addChild(robotButton);
			
			shipButton = new ShipButton();
			shipButton.x = 60 * 3 + 35 + 10 * 3;
			shipButton.y = 35;
			menu02.addChild(shipButton);
			
			rocketButton = new RocketButton();
			rocketButton.x = 60 * 4 + 35 + 10 * 4;
			rocketButton.y = 35;
			menu02.addChild(rocketButton);
			
			terrainButton = new TerrainButton();
			terrainButton.x = 60 * 5 + 35 + 10 * 5;
			terrainButton.y = 35;
			menu02.addChild(terrainButton);
			
			this.addChild(menu02);
			
			// ------------------------------------------------------------------
			vehicleButton.addEventListener(MouseEvent.CLICK, onVehicleClick, false, 0, true);
			robotButton.addEventListener(MouseEvent.CLICK, onRobotClick, false, 0, true);
			shipButton.addEventListener(MouseEvent.CLICK, onShipClick, false, 0, true);
			rocketButton.addEventListener(MouseEvent.CLICK, onRocketClick, false, 0, true);
			terrainButton.addEventListener(MouseEvent.CLICK, onTerrainClick, false, 0, true);
			
			//this.startButton.enabled = true;
			//this.startButton.visible = true;
			
			//this.stopButton.enabled = false;
			//this.stopButton.visible = false;
		}
		
		private function onGearClick( event:MouseEvent ):void
		{	
			TweenLite.to(gearIcon, 1, {rotation:360});
			
			if (isDown)
			{				
				TweenLite.to(menu01, 0.5, { x:0, y:50, ease:Circ.easeOut, alpha:1 } );
				TweenLite.to(menu02, 0.5, { x:0, y:0, ease:Circ.easeOut, alpha:1 } );
				ExternalInterface.call("MenuState", "open");
			}
			else
			{
				TweenLite.to(menu01, 0.5, { x:0, y: -200, ease:Circ.easeIn, alpha:0 } );
				TweenLite.to(menu02, 0.5, { x:-400, y: 0, ease:Circ.easeIn, alpha:0 } );
				ExternalInterface.call("MenuState", "close");
			}
				
			isDown = !isDown;
		}
		
		/*
		private function onStartClick( event:MouseEvent ):void
		{
			this.startButton.enabled = false;
			this.startButton.visible = false;
			
			this.stopButton.enabled = true;
			this.stopButton.visible = true;
			
			//ExternalInterface.call("Start", "start");
		}
		
		private function onStopClick( event:MouseEvent ):void
		{
			this.startButton.enabled = true;
			this.startButton.visible = true;
			
			this.stopButton.enabled = false;
			this.stopButton.visible = false;
			
			//ExternalInterface.call("Stop", "stop");
		}
		*/
		private function onPrevOceanSimClick( event:MouseEvent ):void
		{
			toggleOceanSim();
		}
		
		private function onNextOceanSimClick( event:MouseEvent ):void
		{
			toggleOceanSim();
		}
		
		//------------------------------------------------------------------------------------
		private function onPrevCompClick( event:MouseEvent ):void
		{
			changeCompositor( -1);
		}
		
		private function onNextCompClick( event:MouseEvent ):void
		{
			changeCompositor(1);
		}
		
		private function changeCompositor(val:int):void
		{
			compVal += val;
			
			if (compVal == -1) compVal = 3;
			else if (compVal == 4) compVal = 0;
			
			if (compVal == 0) // no effect
			{
				compText.text = "NO EFFECT";
				ExternalInterface.call("Compositor", "0");
			}
			else if (compVal == 1) // hdr
			{
				compText.text = "HDR";
				ExternalInterface.call("Compositor", "1");
			}
			else if (compVal == 2) // bloom
			{
				compText.text = "BLOOM";
				ExternalInterface.call("Compositor", "2");
			}
			else if (compVal == 3) // radial blur
			{
				compText.text = "RADIAL BLUR";
				ExternalInterface.call("Compositor", "3");
			}
		}
		
		// --------------------------------------------------------------------------------------
		
		private function onPrevWeatherClick( event:MouseEvent ):void
		{
			changeWeather(-1);
		}
		
		private function onNextWeatherClick( event:MouseEvent ):void
		{
			changeWeather(1);
		}
		
		private function changeWeather(val:int):void
		{
			this.weatherVal += val;
			if (this.weatherVal == 3) this.weatherVal = 0;
			else if (this.weatherVal == -1) this.weatherVal = 2;
			
			if (this.weatherVal == 0) 
			{
				ExternalInterface.call("WeatherOption", "morning");
				weatherText.text = "MORNING";
			}
			else if (this.weatherVal == 1) 
			{
				ExternalInterface.call("WeatherOption", "evening");
				weatherText.text = "EVENING";
			}
			else if (this.weatherVal == 2) 
			{
				ExternalInterface.call("WeatherOption", "cloudy");
				weatherText.text = "CLOUDY";
			}
		}
		
		private function toggleOceanSim():void
		{
			this.oceanSimVal = !oceanSimVal;
			
			if (oceanSimVal) 
			{
				ExternalInterface.call("OceanSimToggle", "on");
				oceanSimText.text = "HYDRAX ON";
			}
			else 
			{	
				ExternalInterface.call("OceanSimToggle", "off");
				oceanSimText.text = "HYDRAX OFF";
			}
		}
		
		private function onExitClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Exit", "exit");
		}
		
		private function setObjects():void
		{
			var child:DisplayObject = null;
			
			for (var a:int = 0; a < this.fpsInfo.numChildren; a++)
			{
				child = this.fpsInfo.getChildAt(a);
				
				if (child.name == "FpsText")
				{
					fpsText = (TextField)(child);
					fpsText.text = "FPS: -";
				}
			}
			
			for (var b:int = 0; b < this.oceanSimOption.numChildren; b++ )
			{
				child = this.oceanSimOption.getChildAt(b);
				
				if (child.name == "oceanSimText")
				{
					oceanSimText = (TextField)(child);
				}
				else if (child.name == "nextOceanSim")
				{
					nextOceanSim = (NextButton)(child);
					nextOceanSim.addEventListener(MouseEvent.CLICK, onNextOceanSimClick, false, 0, true);
				}
				else if (child.name == "prevOceanSim")
				{
					prevOceanSim = (PrevButton)(child);
					prevOceanSim.addEventListener(MouseEvent.CLICK, onPrevOceanSimClick, false, 0, true);
				}
			}
			
			for (var c:int = 0; c < this.oceanSimOption.numChildren; c++ )
			{
				child = this.weatherOption.getChildAt(c);
				
				if (child.name == "weatherText")
				{
					weatherText = (TextField)(child);
				}
				else if (child.name == "nextWeather")
				{
					nextWeather = (NextButton)(child);
					nextWeather.addEventListener(MouseEvent.CLICK, onNextWeatherClick, false, 0, true);
				}
				else if (child.name == "prevWeather")
				{
					prevWeather = (PrevButton)(child);
					prevWeather.addEventListener(MouseEvent.CLICK, onPrevWeatherClick, false, 0, true);
				}
			}
			
			for (var d:int = 0; d < this.compOption.numChildren; d++ )
			{
				child = this.compOption.getChildAt(d);
				
				if (child.name == "compText")
				{
					compText = (TextField)(child);
				}
				else if (child.name == "nextComp")
				{
					nextComp = (NextButton)(child);
					nextComp.addEventListener(MouseEvent.CLICK, onNextCompClick, false, 0, true);
				}
				else if (child.name == "prevComp")
				{
					prevComp = (PrevButton)(child);
					prevComp.addEventListener(MouseEvent.CLICK, onPrevCompClick, false, 0, true);
				}
			}
		}
		
		private function setFPS(fps:Number):void
		{
			fpsText.text = "FPS: " + fps.toString();
		}
		
		//----------------------------------------------------------------
		
		private function onVehicleClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Camera", "1");
		}
		
		private function onRobotClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Camera", "2");
		}
		
		private function onShipClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Camera", "3");
		}
		
		private function onRocketClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Camera", "4");
		}
		
		private function onTerrainClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Camera", "5");
		}
		
		
	}

}