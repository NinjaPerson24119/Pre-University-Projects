int const lvlarea = 200;
class snake
{
public:
	//Constructor and destructor
	snake(int initial_x, int initial_y, int initial_direction);
	~snake() { ; }
	//Set
	void set_headx(int new_headx) { headx = new_headx; }
	void set_heady(int new_heady) { heady = new_heady; }
	void set_length(int new_length) { length = new_length; }
	void set_direction(int new_direction) { direction = new_direction; }
	//Get
	int get_headx() { return headx; }
	int get_heady() { return heady; }
	int get_length() { return length; }
	int get_direction() { return direction; }
	int get_body1(int get) { return body[get].get_1(); }
	int get_body2(int get) { return body[get].get_2(); }
	//Actions
	void move();
	void reset();
	int overlap(int entry1, int entry2);
private:
	//Characteristics
	int headx;
	int heady;
	doubleint body[lvlarea];
	int length;
	//Action related
	int direction;
};

//Constructor
snake::snake(int initial_x, int initial_y, int initial_direction)
{
	//Build stats
	headx = initial_x;
	heady = initial_y;
	direction = initial_direction;
	length = 1;
	reset();

	//Reset array
	reset();

	//Build first segment
	move(); //Calls move to scroll snake in direction
}

//Move
void snake::move()
{
	//Backup snake head
	int backupx = headx;
	int backupy = heady;

	switch(direction) //Move the snake head
	{
	case 1:
		heady = heady-1;
		break;
	case 2:
		headx = headx+1;
		break;
	case 3:
		heady = heady+1;
		break;
	case 4:
		headx = headx-1;
		break;
	}

	//Backup body
	doubleint backupbody[lvlarea];
	for(int count = 0; count < length; count++)
	{
		backupbody[count].set_1(body[count].get_1());
		backupbody[count].set_2(body[count].get_2());
	}

	//Scroll segments
	for(int count = 0; count < length; count++)
	{
		if(count == 0)
		{
			body[count].set_1(backupx);
			body[count].set_2(backupy);
		}
		else
		{
			body[count].set_1(backupbody[count-1].get_1());
			body[count].set_2(backupbody[count-1].get_2());
		}

	}
}

//Reset
void snake::reset()
{
		//Initialise body
	for(int count = 0; count < lvlarea; count++)
	{
		body[count].set_1(0);
		body[count].set_2(0);
	}

}

//Overlap
int snake::overlap(int entry1, int entry2)
{
		for(int count2 = 0; count2 < length; count2++)
		{
			if( (entry1 == body[count2].get_1()) && (entry2 == body[count2].get_2()) )
				return 1;
		}
	return 0;
}