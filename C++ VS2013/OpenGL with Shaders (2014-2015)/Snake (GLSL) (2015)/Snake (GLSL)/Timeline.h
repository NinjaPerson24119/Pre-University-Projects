#ifndef TIMELINE_H
#define TIMELINE_H

//////
//Timeline
class Timeline
{
public:
	//Base
		Timeline();
	//Get
		double Total();
		double Change();
private:
	//Data
		double initial;
		double last;
};
//////

#endif