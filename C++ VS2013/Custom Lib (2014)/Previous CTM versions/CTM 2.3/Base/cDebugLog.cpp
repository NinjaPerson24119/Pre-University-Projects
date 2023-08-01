#include "cDebugLog.h"

namespace ctm
{

//Constructor
debuglog::debuglog(const char *iOutputFile)
{
	outputfile.open(iOutputFile); //Open file for output
}

//Copy constructor
debuglog::debuglog(debuglog &rhs)
{}

//Destructor
debuglog::~debuglog()
{
	outputfile.flush(); //Flush to file
	outputfile.close(); //Close output file
}

//Operator =
debuglog &debuglog::operator=(debuglog &rhs)
{
	return *this;
}

//Send error
void debuglog::send(const bool nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const char *nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const int nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const unsigned int nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const long nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const unsigned long nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const long long nReport, bool nFatal)
{
	if (nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const unsigned long long nReport, bool nFatal)
{
	if (nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const float nReport, bool nFatal)
{
	if(nFatal == true) fatal = true; //Check for fatal error
	outputfile << nReport;
}

void debuglog::send(const double nReport, bool nFatal)
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