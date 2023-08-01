/////////////////
//Walls class
class walls
{
	//Constructor
	public walls(char iR)
	{
		//Set representation
		r = iR;
	}

	//Draw
	public void draw(graphics target)
	{
		//Cycle y
		for(int y = 0; y < target.data.height; ++y)
		{
			//Cycle x
			for(int x = 0; x < target.data.width; ++x)
			{
				if((x == 0) || (x == target.data.width-1) || (y == 0) || (y == target.data.height-1))
					target.data[y, x] = r;
			}
		}
	}

	public char r; //Representation
};
/////////////////