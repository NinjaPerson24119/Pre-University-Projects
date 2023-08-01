///////////////////
//2D Array class
public class array2D<type>
{
	//Constructor
	public array2D(int iWidth, int iHeight)
	{
		//Set array dimensions
		width = iWidth;
		height = iHeight;

		//Allocate array data
		data = new type[width*height];
	}

	//Set data
	public type this[int x, int y]
	{
		get
		{
			//Check for errors
			if((x < 0) || (x >= width) || (y < 0) || (y >= height))
				throw new System.ApplicationException("Error: Array2D - Failed to access array! Invalid position!\n");

			return data[y*height+x];
		}

		set
		{
			//Check for errors
			if((x < 0) || (x >= width) || (y < 0) || (y >= height))
				throw new System.ApplicationException("Error: Array2D - Failed to edit array! Invalid position!\n");

			data[y*height+x] = value;
		}
	}

	private type[] data; //Array data
	public int width, height; //Array dimensions
};
///////////////////