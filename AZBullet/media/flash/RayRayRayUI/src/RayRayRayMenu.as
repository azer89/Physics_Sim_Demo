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
		private var menu:MovieClip;
		private var gearIcon:GearIcon;
		private var isDown:Boolean = true;
		
		private var oceanSimOption:OceanSimOption;
		private var prevOceanSim:PrevButton;
		private var nextOceanSim:NextButton;
		private var oceanSimText:TextField;
		private var oceanSimVal:Boolean;
		
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
			ExternalInterface.addCallback("setFPS", setFPS);
		}
		
		private function setButton():void
		{
			gearIcon = new GearIcon();
			gearIcon.x = 35;
			gearIcon.y = 35;
			gearIcon.addEventListener(MouseEvent.CLICK, onGearClick, false, 0, true);
			this.addChild(gearIcon);
			
			menu = new MovieClip();
			menu.x = 0;
			menu.y = -200;
			menu.alpha = 0;
			
			fpsInfo = new FPSInfo();
			fpsInfo.x = 95;
			fpsInfo.y = 40;
			menu.addChild(fpsInfo);
			
			weatherOption = new WeatherOption();
			weatherOption.x = 90;
			weatherOption.y = 70;
			menu.addChild(weatherOption);
			
			oceanSimOption = new OceanSimOption();
			oceanSimOption.x = 90;
			oceanSimOption.y = 110;
			menu.addChild(oceanSimOption);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 150;
			exitButton.addEventListener(MouseEvent.CLICK, onExitClick, false, 0, true);
			menu.addChild(exitButton);
			
			this.addChild(menu);
			
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
				TweenLite.to(menu, 0.5, { x:0, y:50, ease:Circ.easeOut, alpha:1 } );
				ExternalInterface.call("MenuState", "open");
			}
			else
			{
				TweenLite.to(menu, 0.5, { x:0, y: -200, ease:Circ.easeIn, alpha:0 } );
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
		}
		
		private function setFPS(fps:Number):void
		{
			fpsText.text = "FPS: " + fps.toString();
		}
		
	}

}