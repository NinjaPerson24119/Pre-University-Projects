#ifndef CTM_STRING_H
#define CTM_STRING_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

//////////////////////
//String class
class string
{
		friend string operator+(string lhs, string &rhs);
		friend string operator+(string lhs, const char *rhs);
		friend string operator+(string lhs, char rhs);
		friend string operator-(string lhs, size_t amount);
public:
	//System
		string(allocator *iAlloc = DEFAULT_ALLOCATOR);
		string(const char *iData, allocator *iAlloc = DEFAULT_ALLOCATOR);
		string(char iData, allocator *iAlloc = DEFAULT_ALLOCATOR);
		string(string &rhs, allocator *iAlloc = DEFAULT_ALLOCATOR);
		~string();
		operator char *() { return get_cstr(); } //Conversion operator to char*
		string &operator=(string &rhs); //Operator =
		string &operator=(const char *rhs); //Operator =
		string &operator=(char rhs); //Operator =
		bool operator==(string &rhs); //Operator ==
		bool operator==(const char *rhs); //Operator ==
		bool operator==(char rhs); //Operator ==
		bool operator!=(string &rhs); //Operator !=
		bool operator!=(const char *rhs); //Operator !=
		bool operator!=(char rhs); //Operator !=
		string &operator+=(string &rhs); //Operator += (Adds anther string to the end of the string)
		string &operator+=(const char *rhs); //Operator += (Adds a char array to the end of the string)
		string &operator+=(char rhs); //Operator += (Adds a character to the end of the string)
		string &operator-=(size_t amount); //Operator -= (Removes a number of characters off the end of the string)
	//Memory
		void clear(); //Clears the string
		char &at(size_t index); //Returns a character from the string
		char *get_cstr(); //Returns the string as a char array
		size_t get_size() { return size; } //Returns the amount of characters in the string (Including the null character)
private:
	char *data;
	allocator *alloc; //Allocator
	size_t size;
};
//////////////////////

}

#endif