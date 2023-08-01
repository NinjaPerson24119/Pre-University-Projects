////////////////////
//Graphics class
class graphics
{
	//Constructor
	public graphics(int iWidth, int iHeight, char iR)
	{
		//Allocate data
		data = new array2D<char>(iWidth, iHeight);

		//Clear data
		clear(iR);
	}

	//Draw
	public void draw()
	{
		//Cycle rows
		for(int y = 0; y < data.height; ++y)
		{
			//Draw characters
			for(int x = 0; x < data.width; ++x)
			{
				System.Console.Write(data[y, x]);
			}

			//Switch lines
			System.Console.Write('\n');
		}
	}

	//Clear
	public void clear(char nR)
	{
		//Cycle rows
		for(int y = 0; y < data.height; ++y)
		{
			//Clear characters
			for(int x = 0; x < data.width; ++x)
			{
				data[y, x] = nR;
			}
		}
	}

	public array2D<char> data; //Graphics data
};
////////////////////