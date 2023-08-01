#include <Custom/Time.h>

namespace ctm
{

static clock_t programstart = clock();

//Time
double Time()
{
	return ((clock() - programstart) / (double)CLOCKS_PER_SEC) / 1000;
}

//Reset Time
void ResetTime()
{
	programstart = clock();
}

//Constructor
Timer::Timer():
setting(0)
{}

Timer::Timer(double Milliseconds)
{
	Setting(Milliseconds);
}

//Setting
void Timer::Setting(double Milliseconds)
{
	setting = Milliseconds + Time();
}

//Idle
void Timer::Idle()
{
	while(setting < Time())
	{}

	Setting(setting);
}

//Try
double Timer::Try()
{
	double temp = setting - Time();
	Setting(setting);
	return temp;
}

}