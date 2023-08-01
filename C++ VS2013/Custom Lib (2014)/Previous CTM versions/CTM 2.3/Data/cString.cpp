#include "cString.h"
#include <string.h>

namespace ctm
{

//Constructor
string::string(allocator *iAlloc):
data(0),
size(0),
alloc(iAlloc)
{}

string::string(const char *iData, allocator *iAlloc):
data(0),
size(0),
alloc(iAlloc)
{
	size = strlen(iData)+1; //Update size

	//Allocate new string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize string
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = iData[count];
	}
	data[size-1] = '\0'; //Add zero escape
}

string::string(char iData, allocator *iAlloc):
data(0),
size(0),
alloc(iAlloc)
{
	size = 2; //Update size

	//Allocate string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);

	data[0] = iData; //Initialize string
	data[1] = '\0'; //Add zero escape 
}

//Copy constructor
string::string(string &rhs, allocator *iAlloc):
data(0),
alloc(iAlloc),
size(rhs.size)
{
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	size = rhs.size; //Update size

	//Allocate string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize string
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}
}

//Destructor
string::~string()
{
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);
	data = 0;
}

//Operator =
string &string::operator=(string &rhs)
{
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	size = rhs.size; //Update size

	//Allocate new string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize string
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}
	return *this;
}

string &string::operator=(const char *rhs)
{
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	size = strlen(rhs)+1; //Update size

	//Allocate new string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);
	
	//Initialize string
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = rhs[count];
	}
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

string &string::operator=(char rhs)
{
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	size = 2; //Update size

	//Allocate new string
	if(alloc == 0)
		data = new char[size];
	else
		data = (char*)alloc->allocate(sizeof(char)*size);

	data[0] = rhs; //Initialize string
	data[1] = '\0'; //Add zero escape
	return *this;
}

//Operator ==
bool string::operator==(string &rhs)
{
	if(data == rhs.data)
		return true;
	else
		return false;
}

bool string::operator==(const char *rhs)
{
	if(data == rhs)
		return true;
	else
		return false;
}

bool string::operator==(char rhs)
{
	if(size != 2) return false;
	if(data[0] != rhs) return false;
	return true;
}

//Operator !=
bool string::operator!=(string &rhs)
{
	return !operator==(rhs);
}

bool string::operator!=(const char *rhs)
{
	return !operator==(rhs);
}

bool string::operator!=(char rhs)
{
	return !operator==(rhs);
}

//Operator +=
string &string::operator+=(string &rhs)
{
	size = size+rhs.size-1; //Update size

	//Allocate copy
	char *temp = 0;
	if(alloc == 0)
		temp = new char[size];
	else
		temp = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize copy
	for(size_t count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}

	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	data = temp; //Allocate string

	//Initialize new string from rhs
	for(size_t count = 0; count < rhs.size; ++count)
	{
		data[count+(size-rhs.size)] = rhs.data[count]; 
	}
	return *this;
}

string &string::operator+=(const char *rhs)
{
	size_t rhssize = strlen(rhs)+1; //Store size of rhs
	size = size+rhssize-1; //Update size

	//Allocate copy
	char *temp = 0;
	if(alloc == 0)
		temp = new char[size];
	else
		temp = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize copy
	for(size_t count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}
	
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	data = temp; //Assign pointer to new string

	//Initialize new string from rhs
	for(size_t count = 0; count < rhssize; ++count)
	{
		data[count+(size-rhssize)] = rhs[count]; 
	}
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

string &string::operator+=(char rhs)
{
	++size; //Update size

	//Allocate copy
	char *temp = 0;
	if(alloc == 0)
		temp = new char[size];
	else
		temp = (char*)alloc->allocate(sizeof(char)*size);

	//Initialize copy
	for(size_t count = 0; count < size-1; ++count)
	{
		temp[count] = data[count];
	}
	
	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	data = temp; //Assign pointer to new string
	data[size-2] = rhs; //Initialize new string from rhs
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

//Operator -=
string &string::operator-=(size_t amount)
{
	#ifdef CTM_DEBUG_SLOW
		if(size-rhs < 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cString - Failed to subtract string! Cannot remove more characters than those existant!\n",true);
		}
	#endif

	//Update size
	if(size-amount == 0) 
		size = 1; //Make space for zero escape
	else
		size -= amount;

	//Initialize new string from old string
	char *temp = 0;
	if(alloc == 0)
		temp = new char[size];
	else
		temp = (char*)alloc->allocate(sizeof(char)*size);

	for(size_t count = 0; count < size; ++count)
	{
		temp[count] = data[count];
	}

	//Deallocate string
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	data = temp; //Assign pointer to new string
	data[size-1] = '\0'; //Add zero escape
	return *this;
}

//Operator +
string operator+(string lhs, string &rhs)
{
	lhs += rhs;
	return lhs;
}

string operator+(string lhs, const char *rhs)
{
	lhs += rhs;
	return lhs;
}

string operator+(string lhs, char rhs)
{
	lhs += rhs;
	return lhs;
}

//Operator -
string operator+(string lhs, unsigned int amount)
{
	lhs -= amount;
	return lhs;
}

//Clear
void string::clear()
{
	//Deallocate data
	if(data != 0) 
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	size = 0; //Reset size
}

//At
char &string::at(size_t index)
{
	#ifdef CTM_DEBUG_SLOW
		if(index > size)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cString - Failed to access element! Index is out of range!\n",true);
		}
	#endif
	return data[index];
}

//Get char*
char *string::get_cstr()
{
	#ifdef CTM_DEBUG_SLOW
	if(data == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cString - Failed to return string! String has not been initialized!\n",true);
	}
	#endif
	return data;
}

}