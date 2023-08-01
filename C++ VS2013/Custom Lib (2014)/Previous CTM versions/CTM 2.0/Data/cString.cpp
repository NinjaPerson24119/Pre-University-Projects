#include "cString.h"
#include <string.h>

//Constructor
string::string():
data(0),
size(0)
{}

string::string(CHAR8 *iData):
data(0),
size(0)
{
	size = strlen(iData)+1; //Update size
	data = new CHAR8[size]; //Allocate new string

	//Initialize string
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = iData[count];
	}
	data[size-1] = '\0'; //Add zero escape
}

string::string(CHAR8 iData):
data(0),
size(0)
{
	size = 2; //Update size
	data = new CHAR8[size]; //Allocate string
	data[0] = iData; //Initialize string
	data[1] = '\0'; //Add zero escape 
}

//Copy constructor
string::string(string &rhs):
data(0),
size(rhs.size)
{
	if(data != 0) delete[] data; //Deallocate string
	size = rhs.size; //Update size
	data = new CHAR8[size]; //Allocate string
	
	//Initialize string
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}
}

//Destructor
string::~string()
{
	if(data != 0) delete[] data; //Deallocate string
	data = 0;
}

//Operator =
string &string::operator=(string rhs)
{
	if(data != 0) delete[] data; //Deallocate string
	size = rhs.size; //Update size
	data = new CHAR8[size]; //Allocate new string
	
	//Initialize string
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}
	return *this;
}

string &string::operator=(CHAR8 *rhs)
{
	if(data != 0) delete[] data; //Deallocate string
	size = strlen(rhs)+1; //Update size
	data = new CHAR8[size]; //Allocate new string
	
	//Initialize string
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs[count];
	}
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

string &string::operator=(CHAR8 rhs)
{
	if(data != 0) delete[] data; //Deallocate string
	size = 2; //Update size
	data = new CHAR8[size]; //Allocate new string
	data[0] = rhs; //Initialize string
	data[1] = '\0'; //Add zero escape
	return *this;
}

//Operator ==
BOOL8 string::operator==(string &rhs)
{
	if(data == rhs.data)
		return true;
	else
		return false;
}

BOOL8 string::operator==(CHAR8 *rhs)
{
	if(data == rhs)
		return true;
	else
		return false;
}

BOOL8 string::operator==(CHAR8 rhs)
{
	if(size != 2) return false;
	if(data[0] != rhs) return false;
	return true;
}

//Operator !=
BOOL8 string::operator!=(string &rhs)
{
	return !operator==(rhs);
}

BOOL8 string::operator!=(CHAR8 *rhs)
{
	return !operator==(rhs);
}

BOOL8 string::operator!=(CHAR8 rhs)
{
	return !operator==(rhs);
}

//Operator +=
string &string::operator+=(string &rhs)
{
	CHAR8 *temp = new CHAR8[size-1]; //Allocate copy

	//Initialize copy
	for(unsigned int count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}
	
	if(data != 0) delete[] data; //Deallocate string
	size = size+rhs.size-1; //Update size
	data = new CHAR8[size]; //Allocate string

	//Initialize new string from copy
	for(UINT32 count = 0; count < size-rhs.size; ++count)
	{
		data[count] = temp[count];
	}
	delete temp; //Deallocate copy

	//Initialize new string from rhs
	for(UINT32 count = 0; count < rhs.size; ++count)
	{
		data[count+(size-rhs.size)] = rhs.data[count]; 
	}
	return *this;
}

string &string::operator+=(CHAR8 *rhs)
{
	CHAR8 *temp = new CHAR8[size-1]; //Allocate copy

	//Initialize copy
	for(UINT32 count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}
	
	if(data != 0) delete[] data; //Deallocate string
	UINT32 rhssize = strlen(rhs)+1; //Store size of rhs
	size = size+rhssize-1; //Update size
	data = new CHAR8[size]; //Allocate string

	//Initialize new string from copy
	for(UINT32 count = 0; count < size-rhssize; ++count)
	{
		data[count] = temp[count];
	}
	delete temp; //Deallocate copy

	//Initialize new string from rhs
	for(UINT32 count = 0; count < rhssize; ++count)
	{
		data[count+(size-rhssize)] = rhs[count]; 
	}
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

string &string::operator+=(CHAR8 rhs)
{
	CHAR8 *temp = new CHAR8[size-1]; //Allocate copy

	//Initialize copy
	for(UINT32 count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}
	
	if(data != 0) delete[] data; //Deallocate string
	++size; //Update size
	data = new CHAR8[size]; //Allocate string

	//Initialize new string from copy
	for(UINT32 count = 0; count < size-1; ++count)
	{
		data[count] = temp[count];
	}
	delete temp; //Deallocate copy
	data[size-2] = rhs; //Initialize new string from rhs
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

//Operator +
string operator+(string lhs, string &rhs)
{
	lhs += rhs;
	return lhs;
}

string operator+(string lhs, CHAR8 *rhs)
{
	lhs += rhs;
	return lhs;
}

string operator+(string lhs, CHAR8 rhs)
{
	lhs += rhs;
	return lhs;
}

//At
CHAR8 &string::at(UINT32 index)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(index > size)); //Error: cString - Failed to access element! Index is out of range!
	#endif
	return data[index];
}

//Get char*
CHAR8 *string::get_char()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(data == 0)); //Error: cString - Failed to return string! String has not been initialized!
	#endif
	return data;
}