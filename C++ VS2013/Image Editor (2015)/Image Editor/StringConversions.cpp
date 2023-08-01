#include "StringConversions.h"

namespace ctm
{

//String To Integer
int StringToInteger(const char *Start, unsigned int Length)
{
	if(Length == 0)
		throw std::runtime_error("StringConversions - Failed to convert string to integer! Length of string cannot be 0!\n");

	if(Length == 1 && Start[0] == '-')
		throw std::runtime_error("StringConversions - Failed to convert string to integer! Length of string cannot be 1 if number is negative!\n");

	int value = 0;
	bool negative = false;

	//Cycle powers of 10
	unsigned int digit = 0;
	for(unsigned int count = 0; count < Length; ++count)
	{
		//Check for negative
		if(count == 0)
		{
			if(Start[0] == '-')
			{
				negative = true;
				++count;
			}
		}

		//Set digit
		digit = (unsigned int)(Start[count] - 48);

		if(digit > 9)
			throw std::runtime_error("StringConversions - Failed to convert string to integer! Invalid character has been found!\n");

		//Add power of 10
		if(negative == true)
		{
			value += (int)pow(10, Length - count - 1) * digit;
		}
		else
		{
			value += (int)pow(10, Length - count - 1) * digit;
		}
	}

	if(negative == true)
		value *= -1;

	return value;
}

//String To Unsigned Integer
unsigned int StringToUnsignedInteger(const char *Start, unsigned int Length)
{
	if(Length == 0)
		throw std::runtime_error("StringConversions - Failed to convert string to integer! Length of string cannot be 0!\n");

	int value = 0;

	//Cycle powers of 10
	unsigned int digit = 0;
	for(unsigned int count = 0; count < Length; ++count)
	{
		//Set digit
		digit = (unsigned int)(Start[count] - 48);

		if(digit > 9)
			throw std::runtime_error("StringConversions - Failed to convert string to integer! Invalid character has been found!\n");

		//Add power of 10
		value += (int)pow(10, Length - count - 1) * digit;
	}

	return value;
}

}