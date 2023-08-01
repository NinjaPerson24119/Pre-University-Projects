public class SnakeGameCS
{
	//Main
    public static void Main()
    {
		//Set initial game state
		gameready = false;

		while(true)
		{
			//Set fps
			fps = 10;
			paused = false;;
	
			//Setup game
			setup();
			
			//Start main loop
			while(gameready == true)
			{
				//Update the game
				update();		
	
				//Draw the game
				draw();

				//Restart timer
				if(timer.ElapsedMilliseconds >= 1000/fps)
					timer.Restart();
			}
		}
    }

	//Setup
	public static void setup()
	{
		//Allocate game objects
		goal = new food(0, 0, '+');
		border = new walls('#');
		screen = new graphics(20, 20, ' ');
		scoredisplay = new scoreboard("score.bin");
		player = new snake(screen.data.width/2, screen.data.height/2, 3, '@', '0');
		timer = new System.Diagnostics.Stopwatch();

		//Start timer
		timer.Restart();

		//Randomize initial goal
		goal.randomize(1, 1, screen.data.width-1, screen.data.height-1);

		//Register game setup
		gameready = true;
	}

	//Update
	public static void update()
	{
		//Check for player movement
		if(System.Console.KeyAvailable)
		{
			System.ConsoleKeyInfo key = System.Console.ReadKey(true);
			switch(key.KeyChar)
			{
			case 'w':
				if(player.d != direction.DOWN)
					player.d = direction.UP;
				break;
			case 'd':
				if(player.d != direction.LEFT)
					player.d = direction.RIGHT;
				break;
			case 's':
				if(player.d != direction.UP)
					player.d = direction.DOWN;
				break;
			case 'a':
				if(player.d != direction.RIGHT)
					player.d = direction.LEFT;
				break;
			case 'e':
				if(paused == false)
					paused = true;
				else
					paused = false;
				break;
			};
		}

		//Check timer and pause state
		if((timer.ElapsedMilliseconds >= 1000/fps) && (paused == false))
		{
			//Update player
			player.update();
	
			//Check if snake head is on goal
			if((goal.x == player.body[0].x) && (goal.y == player.body[0].y))
			{
				//Randomize goal
				while(true)
				{
					goal.randomize(1, 1, screen.data.width-1, screen.data.height-1);

					//Check that goal is not on player
					bool goalgood = true;
					for(int count = 0; count < player.body.Count; ++count)
					{
						if((goal.x == player.body[count].x) && (goal.y == player.body[count].y))
							goalgood = false;
					}

					if(goalgood == true)
						break;
				}

				//Grow player
				player.grow();

				//Add to scoreboard
				scoredisplay.score += 1;
			}

			//Check if snake is colliding with wall
			if((player.body[0].x == 0) || (player.body[0].x == screen.data.width-1) || (player.body[0].y == 0) || (player.body[0].y == screen.data.height-1))
				cleanup();

			//Check if snake head is colliding with snake body
			for(int count = 1; count < player.body.Count; ++count)
			{
				if((player.body[0].x == player.body[count].x) && (player.body[0].y == player.body[count].y))
				{
					cleanup();
					break;
				}
			}

			//Update scoreboard
			scoredisplay.update();
		}
	}

	//Draw
	public static void draw()
	{
		//Check timer
		if(timer.ElapsedMilliseconds >= 1000/fps)
		{
			//Clear the console
			System.Console.Clear();

			//Clear the screen
			screen.clear(' ');

			//Draw elements to screen
			border.draw(screen);
			goal.draw(screen);
			player.draw(screen);

			//Output screen to console
			screen.draw();
	
			//Output scoreboard to console
			System.Console.Write('\n');
			scoredisplay.draw();
		}
	}

	//Cleanup
	public static void cleanup()
	{
		//Wait
		System.Threading.Thread.Sleep(1000);

		//Save scoreboard
		scoredisplay.savebest("score.bin");

		//Register game cleanup
		gameready = false;
	}

	static food goal; //Goal
	static walls border; //Border
	static graphics screen; //Screen
	static scoreboard scoredisplay; //Score display
	static snake player; //Player
	static System.Diagnostics.Stopwatch timer; //Timer
	static bool gameready; //Is the game ready?
	static int fps; //Frames per second
	static bool paused; //Is the game paused?
};