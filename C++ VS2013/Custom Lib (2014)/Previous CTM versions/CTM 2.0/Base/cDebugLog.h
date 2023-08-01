#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include "Base.h"
#include <fstream>

//////////////////////
//Debug log class
class debuglog
{
public:
	//System
		debuglog(const CHAR8 *iOutputFile);
		~debuglog();
	//Debugging
		void send_error(const CHAR8 *nReport, BOOL8 nFatal); //Sends an error to be output
		bool fatal_error() { return fatal; } //Checks if a fatal error has occured
private:
	//Inaccessible
		debuglog(debuglog &rhs);
		debuglog &operator=(debuglog &rhs);
	std::ofstream outputfile; //Debug log file
	BOOL8 fatal; //Has a fatal error occured
};
//////////////////////

extern debuglog *DEFAULT_DEBUGLOG;

#endif
