int const lvlsize = 20;
class world
{
public:
	//Constructor and destructor
	world();
	~world() { ; }
	//Get
	int const get_sizex() { return sizex; }
	int const get_sizey() { return sizey; }
	int const get_map(int x, int y) { return map[x][y]; }
	//Set
	void set_map(int x, int y, char new_value) { map[x][y] = new_value; }
	//Actions
	void reset();
	void layout();
	void draw();
private:
	int sizex;
	int sizey;
	char map[lvlsize][lvlsize];
};

//Constructor
world::world()
{
	int sizex = lvlsize;
	int sizey = lvlsize;
	reset();
}

//layout
void world::layout()
{
	for(int y = 0; y < lvlsize; y++)
	{
		for(int x = 0; x < lvlsize; x++)
		{
			if( (y == 0) || (y == lvlsize-1) )
				map[x][y] = '-';

			if( (x == 0) || (x == lvlsize-1) ) //Sides
				map[x][y] = '|';
		}
	}
}

//Reset
void world::reset()
{
	for(int y = 0; y < lvlsize; y++)
	{
		for(int x = 0; x < lvlsize; x++)
		{
			map[x][y] = ' ';
		}
	}
}

//Draw
void world::draw()
{
	for(int y = 0; y < lvlsize; y++)
	{
		for(int x = 0; x < lvlsize; x++)
		{
			std::cout << map[x][y];
		}
		std::cout << "\n";
	}
}