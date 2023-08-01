#ifndef CTM_DEBUGLOG_H
#define CTM_DEBUGLOG_H

#include "Base.h"

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

namespace ctm
{

//////////////////////
//Debug log class
class debuglog
{
public:
	//System
		debuglog(const char *iOutputFile);
		~debuglog();
	//Debugging
		void send(const bool nReport, bool nFatal = false); //Outputs a bool
		void send(const char *nReport, bool nFatal = false); //Outputs a string
		void send(const int nReport, bool nFatal = false); //Outputs an integer
		void send(const unsigned int nReport, bool nFatal = false); //Outputs an unsigned integer
		void send(const long nReport, bool nFatal = false); //Outputs a long
		void send(const unsigned long nReport, bool nFatal = false); //Outputs an unsigned long
		void send(const long long nReport, bool nFatal = false); //Outputs a long long
		void send(const unsigned long long nReport, bool nFatal = false); //Outputs an unsigned long long
		void send(const float nReport, bool nFatal = false); //Outputs a float
		void send(const double nReport, bool nFatal = false); //Outputs a double
		void flush(); //Writes all unwritten data to the output file
		void flag_fatal() { fatal = true; } //Flags that a fatal error has occured
		void unflag_fatal() { fatal = false; } //Unflags a fatal error
		bool check_fatal() { return fatal; } //Checks if a fatal error has occured
private:
	//Inaccessible
		debuglog(debuglog &rhs);
		debuglog &operator=(debuglog &rhs);
	std::ofstream outputfile; //Debug log file
	bool fatal; //Has a fatal error occured
};
//////////////////////

extern debuglog *DEFAULT_DEBUGLOG;

}

#endif
