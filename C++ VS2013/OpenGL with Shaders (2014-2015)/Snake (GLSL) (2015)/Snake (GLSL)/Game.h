#ifndef GAME_H
#define GAME_H

#include "StackAllocator.h"
#include "Timeline.h"
#include "Controller.h"
#include "Snake.h"
#include "Walls.h"
#include "Goal.h"
#include "Vertex.h"
#include "Color.h"

//////
//Game
class Game
{
public:
	//Game State
		enum State { RUNNING, GAMEOVER, ENDING, STARTING };
	//Base
		Game(unsigned int WindowWidth, unsigned int WindowHeight, unsigned int TileSize, unsigned int TilesPerSec);
	//Set
		void Reset();
		void Update();
		void Draw(Vertex *&Vertices, unsigned int &VertexBufferLength, unsigned int *&Indices, unsigned int &IndiceBufferLength);
	//Get
		Controller &Controls();
private:
	//Data
		ctm::StackAllocator fastalloc;
		Timeline time;
		Snake player1;
		Controller controller1;
		Walls walls;
		Goal goal;
		Color tint;
		double updatecapacitor;
		unsigned int wndwidth, wndheight, tilesize, tilespersec;
		State gamestate;
};
//////

#endif