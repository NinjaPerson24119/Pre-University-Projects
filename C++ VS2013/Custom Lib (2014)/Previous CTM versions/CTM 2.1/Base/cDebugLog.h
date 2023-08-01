#ifndef DEBUGLOG_H
#define DEBUGLOG_H

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
		debuglog(const CHAR8 *iOutputFile);
		~debuglog();
	//Debugging
		void send(const BOOL8 nReport, BOOL8 nFatal = false); //Outputs a bool
		void send(const CHAR8 *nReport, BOOL8 nFatal = false); //Outputs a string
		void send(const INT32 nReport, BOOL8 nFatal = false); //Outputs an integer
		void send(const UINT32 nReport, BOOL8 nFatal = false); //Outputs an unsigned integer
		void send(const LONG32 nReport, BOOL8 nFatal = false); //Outputs a long
		void send(const ULONG32 nReport, BOOL8 nFatal = false); //Outputs an unsigned long
		void send(const FLOAT32 nReport, BOOL8 nFatal = false); //Outputs a float
		void send(const DOUBLE64 nReport, BOOL8 nFatal = false); //Outputs a double
		void flush(); //Writes all unwritten data to the output file
		void flag_fatal() { fatal = true; } //Flags that a fatal error has occured
		void unflag_fatal() { fatal = false; } //Unflags a fatal error
		bool check_fatal() { return fatal; } //Checks if a fatal error has occured
private:
	//Inaccessible
		debuglog(debuglog &rhs);
		debuglog &operator=(debuglog &rhs);
	std::ofstream outputfile; //Debug log file
	BOOL8 fatal; //Has a fatal error occured
};
//////////////////////

extern debuglog *DEFAULT_DEBUGLOG;

}

#endif
