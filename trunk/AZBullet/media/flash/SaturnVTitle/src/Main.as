package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	
	import com.greensock.*;
	import com.greensock.easing.*;
	
	/**
	 * ...
	 * @author Reza Adhitya Saputra
	 */
	public class Main extends Sprite 
	{
		private var title:Title;
		private var gameOver:GameOver;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			ExternalInterface.addCallback("SetGameOver", setGameOver);
			
			title = new Title();
			title.x = 300;
			title.y = 538 / 2;
			title.alpha = 0;
			this.addChild(title);
			title.addEventListener(MouseEvent.CLICK, onStartClick, false, 0, true);
			
			gameOver = new GameOver();
			gameOver.x = 300;
			gameOver.y = 538 / 2;
			gameOver.alpha = 0;
			this.addChild(gameOver);
			
			TweenLite.to(title, 1.0, { ease:Circ.easeIn, alpha:1 } );
		}
		
		private function onStartClick( event:MouseEvent ):void
		{			
			TweenLite.to(title, 1.0, {ease:Circ.easeOut, alpha:0 } );
			ExternalInterface.call("StartTitle", "start");
		}
		
		private function setGameOver(i:Number):void
		{
			TweenLite.to(gameOver, 1.0, {ease:Circ.easeIn, alpha:1 } );
		}
		
	}
	
}