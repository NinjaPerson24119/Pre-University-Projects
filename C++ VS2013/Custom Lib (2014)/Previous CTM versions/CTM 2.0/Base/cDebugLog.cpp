#include "cDebugLog.h"

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
void debuglog::send_error(const CHAR8 *nReport, BOOL8 nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

debuglog *DEFAULT_DEBUGLOG = 0;