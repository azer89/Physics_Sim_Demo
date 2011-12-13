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
		
		//private var curveOption:CurveOption;
		//private var prev:PrevButton;
		//private var next:NextButton;
		//private var curveText:TextField;
		//private var curveVal:int;
		
		private var oceanSimOption:OceanSimOption;
		private var prevOceanSim:PrevButton;
		private var nextOceanSim:NextButton;
		private var oceanSimText:TextField;
		private var oceanSimVal:Boolean;
		
		public function RayRayRayMenu()
		{
			this.setButton();
			this.setObjects();
			//curveVal = 0;
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
			
			/*
			startButton = new StartButton();
			startButton.x = 90;
			startButton.y = 70;
			startButton.addEventListener(MouseEvent.CLICK, onStartClick, false, 0, true);
			menu.addChild(startButton);
			
			stopButton = new StopButton();
			stopButton.x = 90;
			stopButton.y = 70;
			stopButton.addEventListener(MouseEvent.CLICK, onStopClick, false, 0, true);
			menu.addChild(stopButton);
			
			curveOption = new CurveOption();
			curveOption.x = 90;
			curveOption.y = 110;
			menu.addChild(curveOption);
			
			numTrainOpt = new NumTrainOption();
			numTrainOpt.x = 90;
			numTrainOpt.y = 150;
			menu.addChild(numTrainOpt);
			*/
			
			oceanSimOption = new OceanSimOption();
			oceanSimOption.x = 90;
			oceanSimOption.y = 70;
			menu.addChild(oceanSimOption);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 110;
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
			if (isDown)
			{
				TweenMax.to(gearIcon, 1, {shortRotation:{rotation:180}});
				TweenMax.to(menu, 0.5, { x:0, y:50, ease:Circ.easeOut, alpha:1 } );
				ExternalInterface.call("MenuState", "open");
			}
			else
			{
				TweenMax.to(gearIcon, 1, {shortRotation:{rotation:0}});
				TweenMax.to(menu, 0.5, { x:0, y: -200, ease:Circ.easeIn, alpha:0 } );
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
		
		private function onPrevClick( event:MouseEvent ):void
		{
			curveVal--;
			setCurve();
		}
		
		private function onNextClick( event:MouseEvent ):void
		{
			curveVal++;
			setCurve();
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
		
		/*
		private function setCurve():void
		{	
			if (curveVal > 2) curveVal = 0;
			else if (curveVal < 0) curveVal = 2;
			
			if (curveVal == 0) 
			{
				curveText.text = "BEZIER";
				//ExternalInterface.call("Curve", "bezier");
			}
			else if (curveVal == 1) 
			{
				curveText.text = "B-SPLINE";
				//ExternalInterface.call("Curve", "bspline");
			}
			else if (curveVal == 2) 
			{
				curveText.text = "LINEAR";
				//ExternalInterface.call("Curve", "linear");
			}
		}
		*/
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
			/*
			for (var c:int = 0; c < this.numTrainOpt.numChildren; c++ )
			{
				child = this.numTrainOpt.getChildAt(c);
				
				if (child.name == "trainText")
				{
					trainText = (TextField)(child);
					trainText.text = "TRAIN: 1";
				}
				else if (child.name == "nextTrain")
				{
					nextTrain = (NextButton)(child);
					nextTrain.addEventListener(MouseEvent.CLICK, onNextTrainClick, false, 0, true);
				}
				else if (child.name == "prevTrain")
				{
					prevTrain = (PrevButton)(child);
					prevTrain.addEventListener(MouseEvent.CLICK, onPrevTrainClick, false, 0, true);
				}
			}
			*/
		}
		
		private function setFPS(fps:Number):void
		{
			fpsText.text = "FPS: " + fps.toString();
		}
		
	}

}