public enum direction 
{ 
	UP, 
	RIGHT, 
	DOWN, 
	LEFT 
};

//////////////////////
//Snake class
class snake
{
	//Constructor
	public snake(int iX, int iY, int iLength, char iHeadR, char iBodyR)
	{
		//Set direction
		d = direction.UP;

		//Set representation
		headr = iHeadR;
		bodyr = iBodyR;

		//Allocate body
		body = new System.Collections.Generic.List<point>(iLength);

		//Initialize snake body
		body.Add(new point(iX, iY));
		for(int count = 0; count < iLength-1; ++count)
		{
			body.Add(new point(iX, iY + count + 1));
		}
	}

	//Update
	public void update()
	{
		//Super inefficient hack :)
		System.Collections.Generic.List<point> poop = new System.Collections.Generic.List<point>(body.Capacity);
		for(int count = 0; count < body.Count; ++count)
		{
			poop.Add(new point(body[count].x, body[count].y));
		}

		//Shift body segments down
		for(int count = 1; count < body.Count; ++count)
		{
			body[count] = poop[count-1]; 
		}

		//Move head
		switch(d)
		{
		case direction.UP:
			body[0].y -= 1;
			break;
		case direction.RIGHT:
			body[0].x += 1;
			break;
		case direction.DOWN:
			body[0].y += 1;
			break;
		case direction.LEFT:
			body[0].x -= 1;
			break;
		};
	}

	//Draw
	public void draw(graphics target)
	{
		//Draw body
		for(int count = 1; count < body.Count; ++count)
		{
			target.data[body[count].y, body[count].x] = bodyr;
		}

		//Draw head
		target.data[body[0].y, body[0].x] = headr;
	}

	//Grow
	public void grow()
	{
		//Add new body segment
		body.Add(new point(body[body.Count-1].x, body[body.Count-1].y));
	}

	public direction d; //Direction
	public System.Collections.Generic.List<point> body; //Snake body
	private char headr, bodyr; //Snake representations
};
//////////////////////