#include "Game.h"
#include "GraphicsAssist.h"

//Constructor
Game::Game(unsigned int WindowWidth, unsigned int WindowHeight, unsigned int TileSize, unsigned int TilesPerSec):
fastalloc(new char[100000], 100000, operator delete[]),
player1((float)(WindowWidth / TileSize / 2), (float)(WindowHeight / TileSize / 2), 3, Color(0.f, 0.8f, 0.f), Color(0.f, 0.7f, 0.f)),
controller1(true),
walls(WindowWidth / TileSize, WindowHeight / TileSize, Color(0.3f, 0.3f, 0.3f)),
goal(0, 0, WindowWidth, WindowHeight),
tint(1.f, 0.f, 0.f, 0.f),
updatecapacitor(0),
wndwidth(WindowWidth),
wndheight(WindowHeight),
tilesize(TileSize),
tilespersec(TilesPerSec),
gamestate(RUNNING)
{}

//Reset
void Game::Reset()
{
	//Reset player
	player1.Reset((float)(wndwidth / tilesize / 2), (float)(wndheight / tilesize / 2), 3);

	//Randomize goal
	while(walls.Collision(goal) || player1.Collision(goal))
	{
		goal.Randomize();
	}
}

//Update
void Game::Update()
{
	updatecapacitor += time.Change();

	if(updatecapacitor >= 1000 / tilespersec)
	{
		updatecapacitor = 0;

		//Update game based on game state
		if(gamestate == GAMEOVER)
		{
			tint.a = 0.f;
		}
		else if(gamestate == ENDING)
		{
			tint.a += 0.05f;
	
			if(tint.a >= 1.f)
			{
				gamestate = STARTING;
				Reset();
			}
		}
		else if(gamestate == STARTING)
		{
			tint.a -= 0.05f;
	
			if(tint.a <= 0.f)
				gamestate = RUNNING;
		}
		else if(gamestate == RUNNING)
		{
			//Accept controls
			if(controller1.GetUp()) //Up
				player1.Direction(0, -1);
			
			if(controller1.GetDown()) //Down
				player1.Direction(0, 1);
			
			if(controller1.GetLeft()) //Left
				player1.Direction(-1, 0);
			
			if(controller1.GetRight()) //Right
				player1.Direction(1, 0);
			
			if(controller1.GetCoordUsage()) //Coordinate
			{
				if(player1.GetDirection().y == 1 || player1.GetDirection().y == -1) //Turn facing up or down
				{
					if(controller1.GetX() < player1.GetBody().at(0).x * tilesize)
						player1.Direction(-1, 0);
	
					if(controller1.GetX() > player1.GetBody().at(0).x * tilesize + tilesize)
						player1.Direction(1, 0);
				}
	
				if(player1.GetDirection().x == 1 || player1.GetDirection().x == -1) //Turn facing left or right
				{
					if(controller1.GetY() < player1.GetBody().at(0).y * tilesize)
						player1.Direction(0, -1);
	
					if(controller1.GetY() > player1.GetBody().at(0).y * tilesize + tilesize)
						player1.Direction(0, 1);
				}
	
				//Move player
				player1.Move();

				//Check for game over
				if(player1.Collision(walls) || player1.Collision())
					gamestate = GAMEOVER;

				//Check for player reaching goal
				if(player1.Collision(goal))
				{
					player1.Grow();
	
					while(player1.Collision(goal) || walls.Collision(goal))
					{
						goal.Randomize();
					}
				}
			}
		}
	}
}

//Draw
void Game::Draw(Vertex *&Vertices, unsigned int &VertexBufferLength, unsigned int *&Indices, unsigned int &IndiceBufferLength)
{
	//Free allocator memory
	fastalloc.Clear();

	//Allocate memory for vertices and indices
	VertexBufferLength = sizeof(Vertex) * ((player1.GetBody().size() + walls.Get().size() + 2) * 4); //+2 is for goal and tint then *4 for quads
	Vertex *vertices = (Vertex*)fastalloc.Allocate(VertexBufferLength);
	IndiceBufferLength = sizeof(unsigned int) * ((player1.GetBody().size() + walls.Get().size() + 2) * 6);
	unsigned int *indices = (unsigned int *)fastalloc.Allocate(IndiceBufferLength);

	//Count vertices written for indices
	unsigned int verticeswritten = 0;
	unsigned int indiceswritten = 0;

	//Write walls
	for(unsigned int count = 0; count < walls.Get().size(); ++count)
	{
		QuadToTriangles((unsigned int)walls.Get().at(0).x * tilesize, (unsigned int)walls.Get().at(0).y * tilesize, (float)tilesize, (float)tilesize, walls.c, &vertices[verticeswritten + count * 4], verticeswritten, &indices[indiceswritten + count * 6]);
	}
	verticeswritten += walls.Get().size() * 4;
	indiceswritten += walls.Get().size() * 6;

	//Write player
	for(unsigned int count = 0; count < player1.GetBody().size(); ++count)
	{
		if(count == 0)
			QuadToTriangles((unsigned int)player1.GetBody().at(0).x * tilesize, (unsigned int)player1.GetBody().at(0).y * tilesize, (float)tilesize, (float)tilesize, player1.headc, &vertices[verticeswritten + count * 4], verticeswritten, &indices[indiceswritten + count * 6]); 
		else
			QuadToTriangles((unsigned int)player1.GetBody().at(0).x * tilesize, (unsigned int)player1.GetBody().at(0).y * tilesize, (float)tilesize, (float)tilesize, player1.bodyc, &vertices[verticeswritten + count * 4], verticeswritten, &indices[indiceswritten + count * 6]); 
	}
	verticeswritten += player1.GetBody().size() * 4;
	indiceswritten += player1.GetBody().size() * 6;

	//Write goal
	QuadToTriangles((unsigned int)goal.x * tilesize, (unsigned int)goal.y * tilesize, (float)tilesize, (float)tilesize, goal.c, &vertices[verticeswritten], verticeswritten, &indices[indiceswritten]);
	verticeswritten += 4;
	indiceswritten += 6;

	//Write tint
	QuadToTriangles(0, 0, (float)wndwidth, (float)wndheight, tint, &vertices[verticeswritten], verticeswritten, &indices[indiceswritten]);
	verticeswritten += 4;
	indiceswritten += 6;

	//Pass data to caller
	Vertices = vertices;
	Indices = indices;
}