#include "StopWatch.h"

namespace ctm
{

//Constructor
stopwatch::stopwatch():
start(0)
{
	reset();
}

//Reset
void stopwatch::reset()
{
	start = clock();
}

//Elapsed seconds
double stopwatch::elapsedseconds()
{
	clock_t now = clock();
	return (double)(now - start)/CLOCKS_PER_SEC;
}

}