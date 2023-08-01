class point
{
public:
	//Constructor and destructor
	point(int initial_x, int initial_y);
	~point() { ; }
	//Set
	void set_x(int new_x) { x = new_x; }
	void set_y(int new_y) { y = new_y; }
	//Get
	int get_x() { return x; }
	int get_y() { return y; }
private:
	int x;
	int y;
};

//constructor
point::point(int initial_x = 20, int initial_y = 20)
{
	x = initial_x;
	y = initial_y;
}