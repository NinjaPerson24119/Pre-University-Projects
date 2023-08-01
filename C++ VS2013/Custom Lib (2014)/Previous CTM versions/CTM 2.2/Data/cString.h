#ifndef STRING_H
#define STRING_H

#include "../Base/Base.h"
#include "cHeapAllocator.h"

namespace ctm
{

//////////////////////
//String class
class string
{
		friend string operator+(string lhs, string &rhs);
		friend string operator+(string lhs, CHAR8 *rhs);
		friend string operator+(string lhs, CHAR8 rhs);
		friend string operator-(string lhs, UINT32 rhs);
public:
	//System
		string(heapallocator *iAlloc);
		string(CHAR8 *iData, heapallocator *iAlloc);
		string(CHAR8 iData, heapallocator *iAlloc);
		string(string &rhs);
		~string();
		operator CHAR8 *() { return get_cstr(); } //Conversion operator to char*
		string &operator=(string &rhs); //Operator =
		string &operator=(CHAR8 *rhs); //Operator =
		string &operator=(CHAR8 rhs); //Operator =
		BOOL8 operator==(string &rhs); //Operator ==
		BOOL8 operator==(CHAR8 *rhs); //Operator ==
		BOOL8 operator==(CHAR8 rhs); //Operator ==
		BOOL8 operator!=(string &rhs); //Operator !=
		BOOL8 operator!=(CHAR8 *rhs); //Operator !=
		BOOL8 operator!=(CHAR8 rhs); //Operator !=
		string &operator+=(string &rhs); //Operator += (Adds anther string to the end of the string)
		string &operator+=(CHAR8 *rhs); //Operator += (Adds a char array to the end of the string)
		string &operator+=(CHAR8 rhs); //Operator += (Adds a character to the end of the string)
		string &operator-=(UINT32 rhs); //Operator -= (Removes a number of characters off the end of the string)
	//Memory
		void clear(); //Clears the string
		CHAR8 &at(UINT32 index); //Returns a character from the string
		CHAR8 *get_cstr(); //Returns the string as a char array
		UINT32 get_size() { return size; } //Returns the amount of characters in the string (Including the null character)
private:
	CHAR8 *data;
	UINT32 size;
	heapallocator *alloc; //Allocator
};
//////////////////////

}

#endif