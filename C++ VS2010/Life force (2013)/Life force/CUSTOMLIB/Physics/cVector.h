#ifndef VECTOR_H
#define VECTOR_H

#ifndef MATH
#define MATH
#include <math.h>
#endif

////////////////////
//Vector class
class vector
{
public:
	//System
		vector(float iX, float iY);
		vector& operator=(vector &rhs);
	//Functions
		void set_cartesian(float nX, float nY) { x = nX; y = nY; }
		void add_cartesian(float aX, float aY) { x = x + aX; y = y +aY; }
		void set_polar(angle direction, float magnitude);
		void decelerate(float amount);
		float get_x() { return x; }
		float get_y() { return y; }
		angle get_angle();
		float get_magnitude() { return distance(0,0,x,y); }
private:
	//Data
		float x, y;
};

//Constructor
vector::vector(float iX = 0, float iY = 0):
x(iX),
y(iY) {}

//Operator =
vector& vector::operator=(vector &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

//Set polar
void vector::set_polar(angle direction, float magnitude)
{
	x = cosf(direction.get_radians()) * magnitude;
	y = sinf(direction.get_radians()) * magnitude;
}

//Get angle
angle vector::get_angle()
{
	return angle(acosf(get_x()/get_magnitude()));
}

//Decelerate
void vector::decelerate(float amount)
{
	if(x > 0) x = x - amount;
	if(x < 0) x = x + amount;
	if(y > 0) y = y - amount;
	if(y < 0) y = y + amount;
}
////////////////////

#endif