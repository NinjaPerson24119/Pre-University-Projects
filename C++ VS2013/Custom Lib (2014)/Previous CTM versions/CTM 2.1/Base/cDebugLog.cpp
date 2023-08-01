#include "cDebugLog.h"

namespace ctm
{

//Constructor
debuglog::debuglog(const CHAR8 *iOutputFile)
{
	outputfile.open(iOutputFile); //Open file for output
	assert(outputfile.is_open()); //Failed to open output file
}

//Copy constructor
debuglog::debuglog(debuglog &rhs)
{}

//Destructor
debuglog::~debuglog()
{
	outputfile.close(); //Close output file
}

//Operator =
debuglog &debuglog::operator=(debuglog &rhs)
{
	return *this;
}

//Send error
void debuglog::send(const BOOL8 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const CHAR8 *nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const INT32 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const UINT32 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const LONG32 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const ULONG32 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const FLOAT32 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const DOUBLE64 nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

//Flush
void debuglog::flush()
{
	outputfile.flush();
}

debuglog *DEFAULT_DEBUGLOG = 0;

}