#ifndef CTM_STOPWATCH_H
#define CTM_STOPWATCH_H

#include <time.h>

namespace ctm
{

//////
//Stopwatch
class stopwatch
{
public:
	//Constructor
		stopwatch();
	//Reset
		void reset();
	//Elapsed seconds
		double elapsedseconds();
private:
	clock_t start;
};
//////

}

#endif