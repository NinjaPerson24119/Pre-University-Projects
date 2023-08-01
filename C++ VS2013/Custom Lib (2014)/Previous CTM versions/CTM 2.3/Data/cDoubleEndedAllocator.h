#ifndef CTM_DOUBLEENDEDALLOCATOR_H
#define CTM_DOUBLEENDEDALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

/////////////////
//Double Ended Allocator
class doubleendedallocator : public allocator
{
public:
	//System
		doubleendedallocator(char *iStack, size_t nSizeBytes, size_t iAlignment, bool iAutoDeleteMemory); //Constructor
		~doubleendedallocator(); //Destructor
private:
	char *stack; //Stack
};
/////////////////

}

#endif