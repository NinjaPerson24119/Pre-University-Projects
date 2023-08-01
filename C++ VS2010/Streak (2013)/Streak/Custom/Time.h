#ifndef CTM_TIME_H
#define CTM_TIME_H

#include <time.h>

namespace ctm
{

double Time(); //Milliseconds
void ResetTime();

//////
//Timer
class Timer
{
public:
	//Base
		Timer();
		Timer(double Milliseconds);
	//Functionality
		void Setting(double Milliseconds);
		void Idle();
		double Try();
		void Reset() { Setting(setting); }
	//Get
		double GetSetting() { return setting; }
private:
	//Data
		double setting;
};
//////

//////
//IntervalTimer
class IntervalTimer
{
public:
	//Base
		IntervalTimer(): interval(0), initial(0) { initial = Time(); } 
		IntervalTimer(double Milliseconds): interval(Milliseconds) { initial = Time(); }
	//Functionality
		void Setting(double Milliseconds) { interval = Milliseconds; initial = Time(); }
		void Idle() { while(Time() < initial + interval) {} Setting(interval); }
		double Try() { double temp = (interval + initial) - Time(); Setting(interval); return temp; }
		void Reset() { Setting(interval); }
	//Get
		double GetSetting() { return interval; }
private:
	//Data
		double interval;
		double initial;
};
//////

}

#endif