using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace SpaceInvaders
{
	public partial class Form1 : Form
	{
		public class point //Data type for a point
		{
			public point(int X, int Y) { x = X; y = Y; }
			public int x, y;
		};

		public class PowerUp //Data type for a power up
		{
			public PowerUp()
			{
				asset = 0;
				location = new point(0, 0);
			}
			public int asset;
			public point location;
		};

		public class EnemyShip //Data type for an enemy ship
		{
			public EnemyShip()
			{
				location = new point(0, 0);
			}
			public int asset; //Image index
			public bool animframe; //Which image of the sprite
			public int scorevalue;
			public point location;
			public int width, height;
			public int shotcooldown, shotcooldowntime;
		};

		public class Explosion //Data type for an explosion
		{
			public Explosion(int x, int y, int FramesLeft)
			{
				location = new point(0, 0);
				location.x = x;
				location.y = y;
				framesleft = FramesLeft;
			}
			public point location;
			public int framesleft;
		};

		public class Base //Data type for a base
		{
			public Base()
			{
				location = new point(0, 0);
				gridsize = 4;
				totalwidth = 0;
				totalheight = 0;
			}
			public point location;
			public int[] damage;
			public int gridsize;
			public int totalwidth, totalheight;
		};

		public Form1()
		{
			InitializeComponent();

			//DLL fix (Enable functional doublebuffering to reduce flicker)
			int style = NativeWinAPI.GetWindowLong(this.Handle, NativeWinAPI.GWL_EXSTYLE);
			style |= NativeWinAPI.WS_EX_COMPOSITED;
			NativeWinAPI.SetWindowLong(pnlView.Handle, NativeWinAPI.GWL_EXSTYLE, style);

			this.DoubleBuffered = true;
			SetStyle(ControlStyles.AllPaintingInWmPaint, true);
			SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
			UpdateStyles();

			//Instructions
			lblInstructions.Text = "Controls:\r\nMove Left = z\r\nMove Right = x\r\nFire = c\r\n\r\nCollect this power up to shoot faster for a time:\r\n\r\nCollect this power up to be invincible for a time:\r\n\r\nCollect this powerup to move faster for a time:\r\n\r\nCollect this powerup to get an extra life:\r\n\r\nShoot the UFO for lots of points:\r\n\r\nOn each level, shoot all the non UFO enemies\r\nbefore they reach the red line to advance to the next! \r\n\r\nHide behind bases for protection from incoming fire:\r\n\r\n";
			picAttack.Image = Image.FromFile("./Assets/attackpowerup.png");
			picShield.Image = Image.FromFile("./Assets/shieldpowerup.png");
			picSpeed.Image = Image.FromFile("./Assets/speedpowerup.png");
			picLife.Image = Image.FromFile("./Assets/lifepowerup.png");
			picUFO.Image = Image.FromFile("./Assets/ufo.png");
			picEnemy1.Image = Image.FromFile("./Assets/enemy1display.png");
			picEnemy2.Image = Image.FromFile("./Assets/enemy2display.png");
			picEnemy3.Image = Image.FromFile("./Assets/enemy3display.png");
			picBase.Image = Image.FromFile("./Assets/base0.png");

			//Core game variables
			fps = 60; //Frames per second
			timRefresh.Interval = 1000 / fps;
			simulatedclick = false;
			difficultyspeedmodifier = 0.5f; //Speed reduction per difficulty
			difficultyshotmodifier = 10; //Shot chance increase per difficulty
			
			keyleft = false;
			keyright = false;
			keyfire = false;
			gameon = false;
			timRefresh.Enabled = false; //Enable main loop
			rnd = new Random();
			notfirstlevel = false;
			
			//Graphics
			context = pnlView.CreateGraphics();
			backbuffer = new Bitmap(pnlView.Width, pnlView.Height);
			backbuffercontext = Graphics.FromImage(backbuffer);
			
			//Position death line
			deathline = 410;
			deathlinepen = new Pen(Color.FromArgb(150, Color.DarkRed));
			
			//Enemy ship variables
			enemies0 = new Image[3];
			enemies1 = new Image[3];
			enemies0[0] = Image.FromFile("./Assets/enemy1.png");
			enemies0[1] = Image.FromFile("./Assets/enemy2.png");
			enemies0[2] = Image.FromFile("./Assets/enemy3.png");
			enemies1[0] = Image.FromFile("./Assets/enemy1b.png");
			enemies1[1] = Image.FromFile("./Assets/enemy2b.png");
			enemies1[2] = Image.FromFile("./Assets/enemy3b.png");
			enemies = new List<EnemyShip>();
			enemyshots = new List<point>();

			xbuffer = 16;
			ybuffer = 16;
			shipwidth = 32;
			altshipwidth = shipwidth * 2;
			shipheight = 32;
			explosionwidth = shipwidth;
			explosionheight = shipheight;
			initial_x = pnlView.Width / 2 - (11 * (xbuffer + shipwidth)) / 2;
			initial_y = 50;
			downdistance = 8;
			enemyspeed = 1; //Start moving right
			firechance = 1000;
			animtime = 30; //Frames
			animtimeleft = animtime;

			//Power up variables
			powerups = new List<PowerUp>();
			powerupassets = new Image[4];
			powerupassets[0] = Image.FromFile("./Assets/attackpowerup.png");
			powerupassets[1] = Image.FromFile("./Assets/speedpowerup.png");
			powerupassets[2] = Image.FromFile("./Assets/lifepowerup.png");
			powerupassets[3] = Image.FromFile("./Assets/shieldpowerup.png");
			powerupwidth = 16;
			powerupheight = 16;
			powerupspeed = 2;
			poweruplifechance = 50; //1 in 50 ships destroyed will drop
			powerupattackchance = 30;
			powerupspeedchance = 30;
			powerupshieldchance = 30;
			poweruptime = 2 * fps; //Frames

			//Shot image
			shot = Image.FromFile("./Assets/shot.png");

			//Player variables
			player = Image.FromFile("./Assets/player.png");
			playerwidth = 64;
			playerheight = player.Height;
			playerposition = new point(0, 0);
			playercooldowntime = (int)((float)fps * (float)20); //4 Frames
			playercooldown = 0;
			playeracceleration = 2;
			playerdeceleration = 1;
			playervelocity = 0;
			playermaxspeed = 8;
			playershots = new List<point>();
			shotspeed = 12;
			playerpowerup = -1;
			playerpoweruptimeleft = 0;
			playerposition.x = (pnlView.Width / 2) - (player.Width / 2);
			playerposition.y = pnlView.Height - (2 * player.Height);

			//UFO variables
			ufoasset = Image.FromFile("./Assets/ufo.png");
			ufo = new point(800, 800);
			ufochance = fps * 12;
			ufoscorevalue = 1000;
			ufospeed = 5;
			ufowidth = playerwidth;
			ufoheight = playerheight / 2;

			//More power up variables (second set that is dependent the just set data)
			powerupshotspeed = playercooldowntime / 2;
			powerupmovementspeed = 12;

			//Base variables
			int basesize = 4;
			bases = new Base[basesize];
			Bitmap fullbase0 = (Bitmap)Bitmap.FromFile("./Assets/base0.png"); //Must be uniform size
			base0assets = new Image[basesize * basesize]; //Array for subparts
			shotdamage = 20;

			Rectangle baseclip = new Rectangle();
			int clipwidth = fullbase0.Width / basesize;
			int clipheight = fullbase0.Height / basesize;
			baseclip.Width = clipwidth;
			baseclip.Height = clipheight;

			for (int i = 0; i < basesize * basesize; ++i) // Take clips from base png
			{
				baseclip.X = i % basesize * clipwidth;
				baseclip.Y = clipheight * (i / basesize);
				base0assets[i] = fullbase0.Clone(baseclip, fullbase0.PixelFormat);
			}

			//Initialize bases
			for (int i = 0; i < 4; ++i)
			{
				bases[i] = new Base();
				bases[i].gridsize = basesize;
				bases[i].totalwidth = 80;
				bases[i].totalheight = bases[i].totalwidth;
				bases[i].damage = new int[basesize * basesize];

				for (int a = 0; a < basesize * basesize; ++a) //Set damage values
				{
					if (a == 9 || a == 10 || a == 13 || a == 14)
					{
						bases[i].damage[a] = -1;
					}
					else
					{
						bases[i].damage[a] = 100; // %health
					}
				}

				bases[i].location.x = playerwidth * 2 + i * 180 - 35; //Reposition
				bases[i].location.y = playerposition.y - bases[i].totalheight - 30;
			}
			
			//Explosions variables
			explosions = new List<Explosion>();
			explosiontime = fps / 3; //frames
			playerexplosiontime = fps; //frames
			explosionasset = Image.FromFile("./Assets/explosion.png");
			playerdeath = new Explosion(0, 0, 0);
		}

		private void btnNewGame_Click(object sender, EventArgs e)
		{
			//Hide instructions
			lblInstructions.Visible = false;
			picAttack.Visible = false;
			picShield.Visible = false;
			picSpeed.Visible = false;
			picLife.Visible = false;
			picUFO.Visible = false;
			picEnemy1.Visible = false;
			picEnemy2.Visible = false;
			picEnemy3.Visible = false;
			picBase.Visible = false;

			//Differentiate between simulated click and user click
			if (simulatedclick != true)
			{
				notfirstlevel = false;

				//Write highscore when player physcially clicks "New Game"
				if (highscore != 0)
				{
					byte[] buffer = new byte[4];
					System.IO.FileStream file = new System.IO.FileStream("./highscore.txt", System.IO.FileMode.OpenOrCreate);
					buffer = BitConverter.GetBytes(highscore);
					Array.Reverse(buffer);
					file.Write(buffer, 0, 4);
					file.Close();
				}
			}
			
			//Queue main loop
			timRefresh.Enabled = true;
			gameon = true;

			//Initialize for non-consecutive matches
			if (notfirstlevel == false)
			{
				//Reset player
				playerposition.x = (pnlView.Width / 2) - (player.Width / 2);
				playerposition.y = pnlView.Height - (2 * player.Height);
				playercooldown = 0;

				//Set difficulty
				difficulty = 0;
				lblDifficulty.Text = Convert.ToString(difficulty);

				//Load highscore
				byte[] buffer = new byte[4];
				System.IO.FileStream file;
				try
				{
					file = new System.IO.FileStream("./highscore.txt", System.IO.FileMode.Open);
					if (file.CanRead)
					{
						file.Read(buffer, 0, 4);
						Array.Reverse(buffer);
						highscore = BitConverter.ToInt32(buffer, 0);
					}
					file.Close();
				}
				catch //Create file if it does not exist (Delete file to reset highscore)
				{
					highscore = 0;
					file = new System.IO.FileStream("./highscore.txt", System.IO.FileMode.OpenOrCreate);
					buffer = BitConverter.GetBytes(highscore);
					Array.Reverse(buffer);
					file.Write(buffer, 0, 4);
					file.Close();
				}

				//HUD values
				score = 0;
				lblLives.TextAlign = ContentAlignment.MiddleCenter;
				lives = 5;
				lblScore.Text = Convert.ToString(score);
				lblHighScore.Text = Convert.ToString(highscore);
				lblLives.Text = Convert.ToString(lives);

				//Reset base damage values
				for (int i = 0; i < bases.Count(); ++i)
				{
					for (int a = 0; a < bases[i].damage.Count(); ++a)
					{
						if (a == 9 || a == 10 || a == 13 || a == 14)
						{
							bases[i].damage[a] = -1;
						}
						else
						{
							bases[i].damage[a] = 100; // %health
						}
					}
				}

				//Reset player death
				playerdeath.framesleft = 0;
			}
			else //Write highscore between matches
			{
				byte[] buffer = new byte[4];
				System.IO.FileStream file = new System.IO.FileStream("./highscore.txt", System.IO.FileMode.OpenOrCreate);
				buffer = BitConverter.GetBytes(highscore);
				Array.Reverse(buffer);
				file.Write(buffer, 0, 4);
				file.Close();
			}

			//Clear explosions
			explosions.Clear();
			
			//Clear shots
			playershots.Clear();
			enemyshots.Clear();

			//Clear power ups
			powerups.Clear();

			//Spawn enemies
			enemies.Clear();
			for (int y = 0; y < 5; ++y)
			{
				for (int x = 0; x < 11; ++x)
				{
					enemies.Add(new EnemyShip());
					enemies[enemies.Count - 1].animframe = false;
					if(y == 0)
					{
						enemies[enemies.Count - 1].asset = 0; //Image to draw with
						enemies[enemies.Count - 1].scorevalue = 300; //Score
						enemies[enemies.Count - 1].shotcooldowntime = fps; //Fire speed
					}
					else if(y == 1 || y == 2)
					{
						enemies[enemies.Count - 1].asset = 1;
						enemies[enemies.Count - 1].scorevalue = 200;
						enemies[enemies.Count - 1].shotcooldowntime = fps / 2;
					}
					else if(y == 3 || y == 4)
					{
						enemies[enemies.Count - 1].asset = 2;
						enemies[enemies.Count - 1].scorevalue = 100;
						enemies[enemies.Count - 1].shotcooldowntime = fps / 3;
					}
					enemies[enemies.Count - 1].width = shipwidth;
					enemies[enemies.Count - 1].height = shipheight;
					enemies[enemies.Count - 1].location.x = initial_x + enemies[enemies.Count - 1].width * x + x * xbuffer;
					enemies[enemies.Count - 1].location.y = initial_y + enemies[enemies.Count - 1].height * y + y * ybuffer;
					enemies[enemies.Count - 1].shotcooldown = 0;
				}
			}

			//Reset UFO
			ufo.x = 800; //pt(800, 800) is used as a "despawned" state
			ufo.y = 800;

			//Add shield
			playerpowerup = 3;
			playerpoweruptimeleft = poweruptime;

			//Clear physical click marker
			simulatedclick = false;
		}

		//Global Variables

		//Core
		int fps;
		int difficulty;
		float difficultyspeedmodifier;
		float difficultyshotmodifier;
		bool simulatedclick;
		bool keyleft, keyright, keyfire;
		Random rnd;
		Graphics context;
		bool gameon;
		bool notfirstlevel;

		//HUD
		int score;
		int highscore;
		int lives;

		//Graphics
		Bitmap backbuffer;
		Graphics backbuffercontext;

		//Deathline
		int deathline;
		Pen deathlinepen;

		//Shot
		Image shot;
		int shotspeed;

		//Enemy ships
		Image[] enemies0;
		Image[] enemies1;
		List<EnemyShip> enemies;
		int enemyspeed;
		int animtime;
		int animtimeleft;
		int downdistance;
		int firechance; //1 out of firechance
		List<point> enemyshots;
		int initial_x, initial_y; //Top left of enemy mass
		int xbuffer; //Horizontal space between enemy mass and left of screen
		int ybuffer; //Vertical space between enemy mass and upper screen
		int shipwidth;
		int altshipwidth;
		int shipheight;

		//UFO
		Image ufoasset;
		point ufo;
		int ufospeed;
		int ufochance;
		int ufoscorevalue;
		int ufowidth, ufoheight;

		//Bases
		Base[] bases;
		Image[] base0assets;
		int shotdamage;

		//Powerups
		List<PowerUp> powerups;
		Image[] powerupassets;
		int powerupwidth;
		int powerupheight;
		int powerupspeed;
		int poweruplifechance;
		int powerupattackchance;
		int powerupspeedchance;
		int powerupshieldchance;
		int powerupshotspeed;
		int powerupmovementspeed;
		int poweruptime;

		//Explosions
		List<Explosion> explosions;
		int explosiontime;
		int playerexplosiontime;
		Image explosionasset;
		int explosionwidth, explosionheight;
		Explosion playerdeath;

		//Player
		Image player;
		point playerposition;
		int playerwidth, playerheight;
		int playercooldowntime; //Millisecs (static value)
		int playercooldown; //Millisecs (dynamic value)
		int playeracceleration;
		int playerdeceleration;
		int playervelocity;
		int playermaxspeed;
		int playerpowerup;
		int playerpoweruptimeleft;
		List<point> playershots;

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			//Only draw while main loop is active
			if (gameon == false)
				return;

			//Draw backbuffer (bitmap) to window (swapbuffers)
			context.DrawImage(backbuffer, new Point(0, 0));
		}
		
		//Handle keys Z, X, and C
		private void Form1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Z)
			{
				keyleft = true;
			}
			else if (e.KeyCode == Keys.X)
			{
				keyright = true;
			}
			else if (e.KeyCode == Keys.C)
			{
				keyfire = true;
			}
		}

		private void Form1_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Z)
			{
				keyleft = false;
			}
			else if (e.KeyCode == Keys.X)
			{
				keyright = false;
			}
			else if (e.KeyCode == Keys.C)
			{
				keyfire = false;
			}
		}

		//Mainloop
		private void timRefresh_Tick(object sender, EventArgs e)
		{
			//Toggle loop
			if (gameon == false)
				return;

			////Game End Logic

			//End game at explosion of last player life
			if (playerdeath.framesleft <= 0 && lives == -1)
			{
				gameon = false; //Prevent further looping
				notfirstlevel = false; //Prevent complete reset
			}
			
			//End game at ship deaths
			if(enemies.Count() == 0 && lives > -1 && playerdeath.framesleft <= 0 && explosions.Count() == 0)
			{
				notfirstlevel = true;
				difficulty += 1;
				lblDifficulty.Text = Convert.ToString(difficulty);
				simulatedclick = true;
				this.btnNewGame.PerformClick(); //Simulate click on btnNewGame
				return; //Ditch loop
			}

			//Kill player if ships get too low
			for (int i = 0; i < enemies.Count(); ++i)
			{
				if (enemies[i].location.y + enemies[i].height >= deathline)
				{
					lives -= 1;
					notfirstlevel = true;
					simulatedclick = true;
					this.btnNewGame.PerformClick(); //Simulate click on btnNewGame
					return; //Ditch loop
				}
			}

			////

			//// Respawning

			if (playerdeath.framesleft == 1 && lives > -1) //Respawn
			{
				playerposition.x = (pnlView.Width / 2) - (player.Width / 2);
				playerposition.y = pnlView.Height - (2 * player.Height);
				playercooldown = 0;
				playerpowerup = 3; //Add shield
				playerpoweruptimeleft = poweruptime;
			}

			//Update player respawn timer
			if (playerdeath.framesleft > 0)
			{
				--playerdeath.framesleft;
			}

			////

			//// UFO logic

			//Spawn ufo
			if (ufo.x == 800 & ufo.y == 800)
			{
				if (rnd.Next() % ufochance == 0)
				{
					ufo.y = 20;
					ufo.x = pnlView.Width + ufowidth;
				}
			}

			//Move / despawn ufo (if it reaches the screen edge)
			if (ufo.y != 800)
			{
				if (ufo.x < -1 * ufowidth)
				{
					ufo.x = 800;
					ufo.y = 800;
				}
				else
				{
					ufo.x -= ufospeed;
				}
			}

			////

			////Player logic

			//Move Player
			if (playerdeath.framesleft <= 0)
			{
				if (keyleft == true && keyright != true) //Move left (mod velocity)
				{
					playervelocity -= playeracceleration;

					if (playerpowerup == 1) //Movement with powerup
					{
						if (playervelocity < powerupmovementspeed * -1)
							playervelocity = powerupmovementspeed * -1;
					}
					else //Without
					{
						if (playervelocity < playermaxspeed * -1)
							playervelocity = playermaxspeed * -1;
					}
				}
				else if (keyleft == false && keyright == true) //Move right (mod velocity)
				{
					playervelocity += playeracceleration;

					if (playerpowerup == 1) //Movement with powerup
					{
						if (playervelocity > powerupmovementspeed)
							playervelocity = powerupmovementspeed;
					}
					else //Without
					{
						if (playervelocity > playermaxspeed)
							playervelocity = playermaxspeed;
					}
				}
				else //Decelerate (no key pressed)
				{
					if (playervelocity > 0)
						playervelocity -= playerdeceleration;
					else if (playervelocity < 0)
						playervelocity += playerdeceleration;

					if ((playervelocity < playerdeceleration && playervelocity > 0) || (playervelocity > playerdeceleration * -1 && playervelocity < 0))
						playervelocity = 0;
				}

				playerposition.x += playervelocity; //Apply momentum (velocity)

				//Player Collision (stop movement through walls)
				if (playerposition.x < 0)
				{
					playerposition.x = 0;
					playervelocity = 0;
				}
				if (playerposition.x + playerwidth >= pnlView.Width)
				{
					playerposition.x = pnlView.Width - playerwidth;
					playervelocity = 0;
				}
			}

			//Fire player weapon
			if (playerdeath.framesleft <= 0)
			{
				if (playercooldown <= 0 && keyfire == true) //Add shot
				{
					playershots.Add(new point(playerposition.x + playerwidth / 2 - shot.Width / 2, playerposition.y - shot.Height));
					if (playerpowerup == 0)
						playercooldown = powerupshotspeed;
					else
						playercooldown = playercooldowntime;
				}
				else //Or wait
				{
					//Player weapon cool down
					if (playercooldown > 0)
						playercooldown -= fps;
				}
			}

			//Acquire powerups
			if (playerdeath.framesleft <= 0)
			{
				if (playerpoweruptimeleft > 0) //Powerup expiry
					--playerpoweruptimeleft;

				if (playerpoweruptimeleft <= 0) //Remove powerup when expired
					playerpowerup = -1;

				//Acquire powerups for player
				for (int i = 0; i < powerups.Count(); ++i) //Collisions
				{
					if ((powerups[i].location.x < playerposition.x + playerwidth && powerups[i].location.x > playerposition.x) || (powerups[i].location.x + powerupwidth < playerposition.x + playerwidth && powerups[i].location.x + powerupwidth > playerposition.x))
					{
						if (powerups[i].location.y >= playerposition.y && powerups[i].location.y < playerposition.y + playerheight)
						{
							//Life is not an active effect
							if (powerups[i].asset == 2) //attack, speed, life, shield
							{
								lives += 1;
								lblLives.Text = Convert.ToString(lives);
							}
							else //Apply active effects
							{
								playerpowerup = powerups[i].asset;
								playerpoweruptimeleft = poweruptime;
							}
							powerups.RemoveAt(i); //Destroy floating powerup (it is absorbed)
						}
					}
				}
			}

			////

			//// Enemy ship logic

			//Update enemy animations
			if (animtime <= 0)
			{
				for (int i = 0; i < enemies.Count(); ++i)
				{
					enemies[i].animframe = !enemies[i].animframe;
				}
				animtime = animtimeleft;
			}
			else
			{
				--animtime;
			}

			//Handle enemy movement
			for (int i = 0; i < enemies.Count(); ++i)
			{
				//Check for hitting wall
				if (((enemies[i].location.x + enemyspeed * 2 + enemies[i].width >= pnlView.Width) && (enemyspeed > 0))|| ((enemies[i].location.x - enemyspeed * 2 < 4) && (enemyspeed < 0)))
				{
					enemyspeed = enemyspeed * -1; //Reverse ship direction
					for(int a = 0; a < enemies.Count(); a++)
					{
						enemies[a].location.y += downdistance;
					}
					break;
				}
				else if (i == enemies.Count() - 1) //If not touching wall, move
				{
					//Apply speed modifier based on difficulty
					int resolvedenemyspeed = enemyspeed;
					if (enemyspeed < 0)
					{
						resolvedenemyspeed = enemyspeed - (int)(difficultyspeedmodifier * difficulty);
					}
					else
					{
						resolvedenemyspeed = enemyspeed + (int)(difficultyspeedmodifier * difficulty);
					}

					//Apply movement
					for (int a = 0; a < enemies.Count(); ++a)
					{

						enemies[a].location.x += resolvedenemyspeed;
					}
					break;
				}
			}
			
			//Handles enemy firing
			int resolvedfirechance = firechance - (int)(difficulty * difficultyshotmodifier); //Apply difficulty
			if(resolvedfirechance < 1) //Cap it
				resolvedfirechance = 0;

			for(int i = 0; i < enemies.Count(); ++i) //Fire
			{
				if(enemies[i].shotcooldown <= 0)
				{
					if (rnd.Next() % resolvedfirechance == 0)
					{
						enemyshots.Add(new point(enemies[i].location.x + enemies[i].width / 2, enemies[i].location.y + enemies[i].height + shot.Height));
					}
				}
				else //Or wait
				{
					--enemies[i].shotcooldown;
				}
			}

			////

			//// Destruction logic

			//Base Collisions
			for (int whichbase = 0; whichbase < bases.Count(); ++whichbase)
			{
				int clipheight = bases[whichbase].totalwidth / bases[whichbase].gridsize;
				int clipwidth = bases[whichbase].totalheight / bases[whichbase].gridsize;

				//Enemy shots
				retestshots:
				for (int i = 0; i < enemyshots.Count(); ++i)
				{
					//Prelim test (collision with whole base rect)
					if ((enemyshots[i].x > bases[whichbase].location.x && enemyshots[i].x < bases[whichbase].location.x + bases[whichbase].totalwidth) || (enemyshots[i].x + shot.Width > bases[whichbase].location.x && enemyshots[i].x + shot.Width < bases[whichbase].location.x + bases[whichbase].totalwidth))
					{
						if (enemyshots[i].y + shot.Height > bases[whichbase].location.y)
						{
							//Check for hit on each individual clip
							for (int whichclip = 0; whichclip < bases[whichbase].damage.Count(); ++whichclip)
							{
								if(bases[whichbase].damage[whichclip] >= 0) //Ensure base clip exists to collide with
								{
									if ((enemyshots[i].x > bases[whichbase].location.x + whichclip % bases[whichbase].gridsize * clipwidth && enemyshots[i].x < bases[whichbase].location.x + (whichclip % bases[whichbase].gridsize + 1) * clipwidth) || (enemyshots[i].x + shot.Width > bases[whichbase].location.x + whichclip % bases[whichbase].gridsize * clipwidth && enemyshots[i].x + shot.Width < bases[whichbase].location.x + (whichclip % bases[whichbase].gridsize + 1) * clipwidth))
									{
										if (enemyshots[i].y + shot.Height > bases[whichbase].location.y + whichclip / bases[whichbase].gridsize * clipheight)
										{
											bases[whichbase].damage[whichclip] -= shotdamage; //Reduce health

											if (bases[whichbase].damage[whichclip] == 0) //Simplify to -1 if excessively under 0
												bases[whichbase].damage[whichclip] = -1;

											enemyshots.RemoveAt(i); //Remove shot
											goto retestshots; //DO NOT continue loop as is, because that will cause an access error. Must refresh list first
										}
									}
								}
							}
						}
					}
				}

				//Player shots
				for (int i = 0; i < playershots.Count(); ++i)
				{
					//Prelim test
					if ((playershots[i].x > bases[whichbase].location.x && playershots[i].x < bases[whichbase].location.x + bases[whichbase].totalwidth) || (playershots[i].x + shot.Width > bases[whichbase].location.x && playershots[i].x + shot.Width < bases[whichbase].location.x + bases[whichbase].totalwidth))
					{
						if (playershots[i].y < bases[whichbase].location.y + bases[whichbase].totalheight)
						{
							//Check for hit on individual clip
							for (int whichclip = 0; whichclip < bases[whichbase].damage.Count(); ++whichclip)
							{
								if (bases[whichbase].damage[whichclip] >= 0)
								{
									if (((playershots[i].x > bases[whichbase].location.x + whichclip % bases[whichbase].gridsize * clipwidth) && (playershots[i].x < bases[whichbase].location.x + (whichclip % bases[whichbase].gridsize + 1) * clipwidth)) || ((playershots[i].x + shot.Width > bases[whichbase].location.x + whichclip % bases[whichbase].gridsize * clipwidth) && (playershots[i].x + shot.Width < bases[whichbase].location.x + (whichclip % bases[whichbase].gridsize + 1) * clipwidth)))
									{
										if (playershots[i].y < bases[whichbase].location.y + (whichclip / bases[whichbase].gridsize + 1) * clipheight)
										{
											bases[whichbase].damage[whichclip] -= shotdamage; //Apply dam
											
											if (bases[whichbase].damage[whichclip] == 0) //Cap
												bases[whichbase].damage[whichclip] = -1;

											playershots.RemoveAt(i);
											break; //It's only possible for one shot to hit per frame from the player, so I can exit to save the cpu
										}
									}
								}
							}
						}
					}
				}
			}

			//Destroy enemy ships
			repeatdestroyenemyship:
			for(int i = 0; i < enemies.Count(); ++i)
			{
				for(int a = 0; a < playershots.Count(); ++a)
				{
					if ((enemies[i].location.x <= playershots[a].x && playershots[a].x <= enemies[i].location.x + enemies[i].width) || (enemies[i].location.x <= playershots[a].x + shot.Width && playershots[a].x + shot.Width <= enemies[i].location.x + enemies[i].width))
					{
						if(enemies[i].location.y <= playershots[a].y && playershots[a].y <= enemies[i].location.y + enemies[i].height)
						{
							//Add explosion at destroyed ship
							explosions.Add(new Explosion(enemies[i].location.x, enemies[i].location.y, explosiontime));
							playershots.RemoveAt(a);

							//Update score
							if (playerdeath.framesleft <= 0)
							{
								score += enemies[i].scorevalue;
								lblScore.Text = Convert.ToString(score);
							}

							//Drop powerups (attack, speed, life, shield)
							if (rnd.Next() % powerupattackchance == 0)
							{
								powerups.Add(new PowerUp());
								powerups[powerups.Count - 1].asset = 0;
								powerups[powerups.Count - 1].location.x = enemies[i].location.x + enemies[i].width / 2 - powerupwidth / 2;
								powerups[powerups.Count - 1].location.y = enemies[i].location.y + enemies[i].height;
							}
							else if (rnd.Next() % powerupshieldchance == 3)
							{
								powerups.Add(new PowerUp());
								powerups[powerups.Count - 1].asset = 1;
								powerups[powerups.Count - 1].location.x = enemies[i].location.x + enemies[i].width / 2 - powerupwidth / 2;
								powerups[powerups.Count - 1].location.y = enemies[i].location.y + enemies[i].height;
							}
							else if (rnd.Next() % powerupspeedchance == 1)
							{
								powerups.Add(new PowerUp());
								powerups[powerups.Count - 1].asset = 3;
								powerups[powerups.Count - 1].location.x = enemies[i].location.x + enemies[i].width / 2 - powerupwidth / 2;
								powerups[powerups.Count - 1].location.y = enemies[i].location.y + enemies[i].height;
							}
							else if (rnd.Next() % poweruplifechance == 2)
							{
								powerups.Add(new PowerUp());
								powerups[powerups.Count - 1].asset = 2;
								powerups[powerups.Count - 1].location.x = enemies[i].location.x + enemies[i].width / 2 - powerupwidth / 2;
								powerups[powerups.Count - 1].location.y = enemies[i].location.y + enemies[i].height;
							}


							enemies.RemoveAt(i);
							goto repeatdestroyenemyship; //Prevent memory issues
						}
					}

					//UFO Collision
					if ((ufo.x <= playershots[a].x && playershots[a].x <= ufo.x + ufowidth) || (ufo.x <= playershots[a].x + shot.Width && playershots[a].x + shot.Width <= ufo.x + ufowidth))
					{
						if (ufo.y <= playershots[a].y && playershots[a].y <= ufo.y + ufoheight)
						{
							//Add explosion at destroyed UFO
							explosions.Add(new Explosion(ufo.x + ufowidth / 2 - explosionwidth, ufo.y + ufoheight / 2 - explosionheight / 2, explosiontime));
							playershots.RemoveAt(a);

							//Update score
							if (playerdeath.framesleft <= 0)
							{
								score += ufoscorevalue;
								lblScore.Text = Convert.ToString(score);
							}

							//Despawn UFO
							ufo.x = 800;
							ufo.y = 800;
						}
					}
				}
			}
			
			//Destroy player
			if (playerdeath.framesleft <= 0)
			{
				for (int i = 0; i < enemyshots.Count(); ++i)
				{
					//Collisions
					if ((playerposition.x <= enemyshots[i].x && enemyshots[i].x <= playerposition.x + playerwidth) || (playerposition.x <= enemyshots[i].x + shot.Width && enemyshots[i].x + shot.Width <= playerposition.x + playerwidth))
					{
						if (playerposition.y <= enemyshots[i].y && enemyshots[i].y <= playerposition.y + playerheight)
						{
							//Check for shield
							if (playerpowerup != 3)
							{
								lives -= 1; //Reduce lives

								//Game over logic
								if (lives == -1)
								{
									lblInstructions.Text = "Game Over";
									lblInstructions.Visible = true;

									//Write highscore
									if (score > highscore)
									{
										byte[] buffer = new byte[4];
										System.IO.FileStream file;
										file = new System.IO.FileStream("./highscore.txt", System.IO.FileMode.OpenOrCreate);
										buffer = BitConverter.GetBytes(highscore);
										Array.Reverse(buffer);
										file.Write(buffer, 0, 4);
										file.Close();
										highscore = score;
										lblHighScore.Text = Convert.ToString(highscore);
									}
								}
								else
								{
									//Update lives to HUD
									lblLives.Text = Convert.ToString(lives);
								}

								//Place explosion at ship (wait to respawn now)
								playerdeath.framesleft = playerexplosiontime;
								playerdeath.location.x = (playerwidth / 2) + playerposition.x - (explosionasset.Width / 2);
								playerdeath.location.y = playerposition.y;
							}
						}
					}
				}
			}
			
			////

			//// Scoring

			//Update highscore
			if (score > highscore)
			{
				highscore = score;
				lblHighScore.Text = Convert.ToString(highscore);
			}

			//// Rendering / Movement (Movement is interlaced with rendering to save loop cycles)

			//Clear
			backbuffercontext.Clear(Color.Black);

			//Draw death line
			backbuffercontext.DrawLine(deathlinepen, new Point(0, deathline), new Point(pnlView.Width, deathline));

			//Draw enemy ship explosions
			Rectangle explosionrect = new Rectangle();
			for(int i = 0; i < explosions.Count(); ++i)
			{
				explosionrect.X = explosions[i].location.x;
				explosionrect.Y = explosions[i].location.y;
				explosionrect.Width = explosionwidth;
				explosionrect.Height = explosionheight;
				backbuffercontext.DrawImage(explosionasset, explosionrect);

				//Fade
				explosions[i].framesleft -= 1; //Update time remaining
				backbuffercontext.FillRectangle(new SolidBrush(Color.FromArgb(255- (explosions[i].framesleft * 255 / explosiontime), Color.Black)), explosionrect);

				//Remove once it expires
				if(explosions[i].framesleft <= 0)
				{
					explosions.RemoveAt(i);
				}
			}
			
			//Draw player explosion
			if(playerdeath.framesleft > 0)
			{
				explosionrect.X = playerdeath.location.x;
				explosionrect.Y = playerdeath.location.y;
				explosionrect.Width = explosionwidth;
				explosionrect.Height = explosionheight;
				backbuffercontext.DrawImage(explosionasset, explosionrect);

				if(playerdeath.framesleft <=  explosiontime) //Fade
					backbuffercontext.FillRectangle(new SolidBrush(Color.FromArgb(255 - (playerdeath.framesleft * 255 / explosiontime), Color.Black)), explosionrect);
			}

			//Move player shots and draw
			for (int i = 0; i < playershots.Count; ++i)
			{
				playershots[i].y -= shotspeed;

				if (playershots[i].y < shot.Height)
				{
					playershots.RemoveAt(i); //Remove at end of screen
				}
				else
				{
					backbuffercontext.DrawImage(shot, new Point(playershots[i].x, playershots[i].y));
				}
			}

			//Move enemy shots and draw
			for(int a = 0; a < enemyshots.Count(); ++a)
			{
				enemyshots[a].y += shotspeed; //Move
				
				if(enemyshots[a].y > pnlView.Height - shot.Height)
				{
					enemyshots.RemoveAt(a); //Remove at edge of screen
				}
				else
				{
					backbuffercontext.DrawImage(shot, new Point(enemyshots[a].x, enemyshots[a].y));
				}
			}

			//Move and draw powerups
			Rectangle poweruprect = new Rectangle();
			for (int i = 0; i < powerups.Count(); ++i)
			{
				poweruprect.X = powerups[i].location.x;
				poweruprect.Y = powerups[i].location.y;
				poweruprect.Width = powerupwidth;
				poweruprect.Height = powerupheight;
				backbuffercontext.DrawImage(powerupassets[powerups[i].asset], poweruprect);

				powerups[i].location.y += powerupspeed; //Move

				if (powerups[i].location.y > pnlView.Height) //Remove at edge of screen
					powerups.RemoveAt(i);
			}

			//Draw Enemies / Enemy shots
			for (int i = 0; i < enemies.Count; ++i)
			{
				//Draw ships
				if (enemies[i].animframe == false) //Frame 1
				{
					backbuffercontext.DrawImage(enemies0[enemies[i].asset], new Rectangle(enemies[i].location.x, enemies[i].location.y, enemies[i].width, enemies[i].height));
				}
				else //Frame 2
				{
					backbuffercontext.DrawImage(enemies1[enemies[i].asset], new Rectangle(enemies[i].location.x, enemies[i].location.y, enemies[i].width, enemies[i].height));
				}

				for (int a = 0; a < enemyshots.Count; ++a) //Draw enemy shots	
				{
					backbuffercontext.DrawImage(shot, new Point(enemyshots[a].x, enemyshots[a].y));
				}
			}
			
			//Draw player
			Rectangle playerrect = new Rectangle();
			if (playerdeath.framesleft <= 0)
			{
				playerrect.X = playerposition.x;
				playerrect.Y = playerposition.y;
				playerrect.Width = playerwidth;
				playerrect.Height = playerheight;
				backbuffercontext.DrawImage(player, playerrect);

				if (playerpoweruptimeleft > 0) //Apply fade to powerup indicator on player
				{
					playerrect.X = playerposition.x + playerwidth / 2 - powerupwidth / 2;
					playerrect.Y = playerposition.y + powerupheight - 2;
					playerrect.Width = powerupwidth;
					playerrect.Height = powerupheight;
					backbuffercontext.DrawImage(powerupassets[playerpowerup], playerrect);
					if (playerpoweruptimeleft <= poweruptime)
						backbuffercontext.FillRectangle(new SolidBrush(Color.FromArgb(255 - (255 * playerpoweruptimeleft / poweruptime), 76, 255, 0)), playerrect);
				}
			}

			//Draw bases
			Rectangle clip = new Rectangle();
			for (int i = 0; i < 4; ++i)
			{
				clip.Width = bases[i].totalwidth / bases[i].gridsize;
				clip.Height = bases[i].totalheight / bases[i].gridsize;
				for (int a = 0; a < bases[i].gridsize * bases[i].gridsize; ++a)
				{
					clip.X = bases[i].location.x + (a % bases[i].gridsize * clip.Width);
					clip.Y = bases[i].location.y + (a / bases[i].gridsize * clip.Height);
					if (bases[i].damage[a] >= 0)
					{
						//Draw
						backbuffercontext.DrawImage(base0assets[a], clip);

						//Fade
						backbuffercontext.FillRectangle(new SolidBrush(Color.FromArgb(255 - (255 * bases[i].damage[a] / 100), Color.Black)), clip);
					}
				}
			}

			//Draw UFO
			Rectangle uforect = new Rectangle();
			if (ufo.y != 800)
			{
				uforect.X = ufo.x;
				uforect.Y = ufo.y;
				uforect.Width = ufowidth;
				uforect.Height = ufoheight;
				backbuffercontext.DrawImage(ufoasset, uforect);
			}

			//Refresh (Call WM_PAINT)
			pnlView.Refresh();
		}
	}

	//DLL fix (Enable functional doublebuffering to reduce flicker)
	internal static class NativeWinAPI
	{
		internal static readonly int GWL_EXSTYLE = -20;
		internal static readonly int WS_EX_COMPOSITED = 0x02000000;

		[DllImport("user32")]
		internal static extern int GetWindowLong(IntPtr hWnd, int nIndex);

		[DllImport("user32")]
		internal static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
	}
}
