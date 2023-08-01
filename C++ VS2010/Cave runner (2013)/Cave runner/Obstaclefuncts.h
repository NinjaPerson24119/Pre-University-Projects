//Point preparer
	void prepare(int line)
	{
		for(int num = 0; num < 15; num++)
		{
			walls[line][num].set_x(rand()%20);
		}
	}

	//Obstacle scroller
	void scroll()
	{
		int temp[20][15] = 0; //Temporary array
		for(int first = 0; first < 20; first++) //Copy data
		{
			for(int second = 0; second < 15; second++)
			{
				temp[first][second] = walls[first][second];
			}
		}

		for(int scrolling = 0; scrolling < 20; scrolling++) //Scroll
		{
			for(int second = 0; second < 15; second++)
			{
				if( (scrolling-1 != -1) && (scrolling+1 != 20)
				{
					walls[scrolling][second] = temp[scrolling+1][second]
				}
			}
		}
	}