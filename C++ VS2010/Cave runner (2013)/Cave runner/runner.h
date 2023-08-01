class runner
{
public:
	//Constructor
	runner(int initial_x, int initial_speed);
	//Get
	int get_x() { return x; }
	int get_speed() { return speed; }
	//Set
	void set_x(int new_x) { x = new_x; }
	void set_speed(int new_speed) { speed = new_speed; }
	//Actions
	void left() { x = x-1; }
	void right() { x = x+1; }
private:
	int x;
	int speed;
};

//Constructor
runner::runner(int initial_x, int initial_speed = 1):
x(initial_x),
speed(initial_speed)
{ }