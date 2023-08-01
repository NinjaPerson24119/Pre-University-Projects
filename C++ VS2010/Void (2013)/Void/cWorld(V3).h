//V2 enhancements: (DATE UNKNOWN)
//-Added dynamic view ports and line function

//V3 enhancements: (MAY 17 2013)
//-Added physical objects
//-Allowed border on fixed viewport

int const lvlsizex = 21;
int const lvlsizey = 21;

enum AXIS { VERTICAL, HORIZONTAL };

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
	void reset(char type);
	void layout();
	void draw(int centerx, int centery, int portsize, int doborder, char border); //With ports
	void draw(int doborder, char border); //Without ports
	void copy(char array[lvlsizex][lvlsizey]);
	void line(AXIS axis, char type, int portsize, int docorners);
private:
	int sizex;
	int sizey;
	char map[lvlsizex][lvlsizey];
};

//Constructor
world::world()
{
	int sizex = lvlsizex;
	int sizey = lvlsizey;
	reset(' ');
}

//Line
void world::line(AXIS axis, char type, int portsize, int docorners = 0)
{
	portsize++;
	int size = portsize; //Mapsize placeholder
	switch(axis)
	{
	case HORIZONTAL: //Draw horizontal line to map
		if(docorners = 1) size++; //Leave space at end of line
		for(int count = 0; count < size; count++)
		{
			std::cout << type;
		}
		std::cout << "\n";
		break;
	case VERTICAL: //Draw vertical line to map
		if(docorners = 1) size++; //Leave space at end of line
		for(int count = 0; count < size; count++)
		{
			std::cout << type << "\n";
		}
		break;
	}
}

//layout
void world::layout()
{
	for(int y = 0; y < lvlsizey; y++)
	{
		for(int x = 0; x < lvlsizex; x++)
		{
			if( (y == 0) || (y == lvlsizey-1) )
				map[x][y] = '-';

			if( (x == 0) || (x == lvlsizex-1) ) //Sides
				map[x][y] = '|';
		}
	}
}

//Reset
void world::reset(char type)
{
	for(int y = 0; y < lvlsizey; y++)
	{
		for(int x = 0; x < lvlsizex; x++)
		{
			map[x][y] = type;
		}
	}
}

//Draw (DYNAMIC)
void world::draw(int centerx, int centery, int portsize, int doborder = 0, char border = ' ')
{
	int x0 = 0; //0 placeholder for bordering
	int y0 = 0;
	int port[4] = { 0,0,0,0 }; //Build ports
	port[0] = centerx-portsize/2; //Position ports
	port[1] = centery-portsize/2;
	port[2] = centerx+portsize/2;
	port[3] = centery+portsize/2;
	if(port[0] < 0) { port[0] = 0; port[2] = port[0]+portsize; } //Guard ports
	if(port[1] < 0) { port[1] = 0; port[3] = port[1]+portsize; }
	if(port[2] > lvlsizex) { port[2] = lvlsizex; port[0] = port[2]-portsize; }
	if(port[3] > lvlsizey) { port[3] = lvlsizey; port[1] = port[3]-portsize; }

	int x = 0; //Predefine x and y for use in bordering
	int y = 0;
	int drawborder = 0; //Placeholder to tell when to draw border
	if(doborder == 1) line(HORIZONTAL,border,portsize,1); //Draw top border

	for(y = port[1]; y < port[3]; y++) //Draw with dynamic ports
	{
		if(doborder == 1) std::cout << border; //Draw left border
		for(x = port[0]; x < port[2]; x++)
		{
			if(drawborder == 1)
			std::cout << border; //Draw border
			else
			std::cout << map[x][y]; //Draw map
		}
		if(doborder == 1) std::cout << border; //Draw right border
		std::cout << "\n"; //New line
	}

	if(doborder == 1) line(HORIZONTAL,border,portsize,1); //Draw bottom border
}

//Draw
void world::draw(int doborder = 0, char border = ' ')
{
	if(doborder == 1) line(HORIZONTAL,border,lvlsizex,1); //Draw top border
	for(int y = 0; y < lvlsizey; y++)
	{
		if(doborder == 1) std::cout << border; //Draw left border
		for(int x = 0; x < lvlsizex; x++)
		{
			std::cout << map[x][y]; //Draw map
		}
		if(doborder == 1) std::cout << border; //Draw right border
		std::cout << "\n"; //New line
	}
    if(doborder == 1) line(HORIZONTAL,border,lvlsizex,1); //Draw bottom border
}

//Copy
void world::copy(char array[lvlsizex][lvlsizey])
{
	for(int x1 = 0; x1 < lvlsizex; x1++)
	{
		for(int y1 = 0; y1 < lvlsizey; y1++)
		{
			map[x1][y1] = array[x1][y1]; //Copy array over
		}
	}
}

////////////////
//Vector class
class vector
{
public:
	vector() { dx = 0; dy = 0; locked = false; } //Constructor
	int dx, dy; //Displacement
	bool locked; //Lock used to check if should decelerate
};
////////////////

////////////////
//Physical object class
class pObject
{
public:
	pObject(int initial_x, int initial_y, bool initial_hidden, unsigned char initial_icon, world *initial_home); //Constructor
	//Data
	int x, y; //Position
	vector d; //Displacement
	unsigned char icon; //Char icon
	world *home; //Where to draw to
	bool hidden;
	//Actions
	void set_position(int new_x, int new_y) { x = new_x; y = new_y; }
	void set_vector(int new_dx, int new_dy) { d.dx = new_dx; d.dy = new_dy; }
	void add_vector(int add_dx, int add_dy) { d.dx = d.dx+add_dx; d.dy = d.dy+add_dy; }
	void update();
};

//Constructor
pObject::pObject(int initial_x, int initial_y, bool initial_hidden, unsigned char initial_icon, world *initial_home)
{
	x = initial_x;
	y = initial_y;
	hidden = initial_hidden;
	icon = initial_icon;
	home = initial_home;
}

//Updates object
void pObject::update()
{
	set_position(x+d.dx,y+d.dy); //Move on vector
	if(d.locked == false) //Decelerate vector
	{
		if(d.dx > 0) d.dx--;
		if(d.dx < 0) d.dx++;
		if(d.dy > 0) d.dy--;
		if(d.dy < 0) d.dy++;
	}
	if(hidden != true) home->set_map(x,y,icon);
}
////////////////