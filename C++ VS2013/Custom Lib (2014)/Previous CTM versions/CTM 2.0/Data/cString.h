#ifndef STRING_H
#define STRING_H

#include "../Base/Base.h"

//////////////////////
//String class
class string
{
		friend string operator+(string lhs, string &rhs);
		friend string operator+(string lhs, CHAR8 *rhs);
		friend string operator+(string lhs, CHAR8 rhs);
public:
	//System
		string();
		string(string &rhs);
		string(CHAR8 *iData);
		string(CHAR8 iData);
		~string();
		operator CHAR8 *() { return get_char(); } //Conversion operator to char*
		string &operator=(string rhs); //Operator =
		string &operator=(CHAR8 *rhs); //Operator =
		string &operator=(CHAR8 rhs); //Operator =
		BOOL8 operator==(string &rhs); //Operator ==
		BOOL8 operator==(CHAR8 *rhs); //Operator ==
		BOOL8 operator==(CHAR8 rhs); //Operator ==
		BOOL8 operator!=(string &rhs); //Operator !=
		BOOL8 operator!=(CHAR8 *rhs); //Operator !=
		BOOL8 operator!=(CHAR8 rhs); //Operator !=
		string &operator+=(string &rhs); //Operator +=
		string &operator+=(CHAR8 *rhs); //Operator +=
		string &operator+=(CHAR8 rhs); //Operator +=
	//Memory
		CHAR8 &at(UINT32 index); //Returns a character from the string
		CHAR8 *get_char(); //Returns the string as a char array
		UINT32 get_size() { return size; } //Returns the amount of characters in the string (Including the null character)
private:
	CHAR8 *data;
	UINT32 size;
};
//////////////////////

#endif