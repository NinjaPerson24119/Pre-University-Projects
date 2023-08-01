#include "Timeline.h"
#include <ctime>

//Constructor
Timeline::Timeline():
initial(clock()),
last(initial)
{}

//Total
double Timeline::Total()
{
	last = clock() / (double)(CLOCKS_PER_SEC / 1000);
	return last - initial;
}

//Change
double Timeline::Change()
{
	double newlast = clock() / (double)(CLOCKS_PER_SEC / 1000);
	double returnval = newlast - last;
	last = newlast;
	return returnval;
}