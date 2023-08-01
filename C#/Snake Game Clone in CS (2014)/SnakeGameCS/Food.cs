///////////////////////
//Food class
class food
{
	//Constructor
	public food(int nX, int nY, char nR)
	{
		//Set coordinates
		x = nX;
		y = nY;

		//Set representation
		r = nR;

		//Allocate random number generator
		rnd = new System.Random();
	}

	//Draw
	public void draw(graphics target)
	{
		target.data[y, x] = r;
	}

	//Randomize
	public void randomize(int minx, int miny, int maxx, int maxy)
	{
		x = rnd.Next(minx, maxx);
		y = rnd.Next(miny, maxy);
	}

	System.Random rnd; //Random number generator
	public int x, y; //Coordinates
	public char r; //Representation
};
///////////////////////