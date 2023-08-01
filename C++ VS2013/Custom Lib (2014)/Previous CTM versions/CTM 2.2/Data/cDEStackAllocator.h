#ifndef DESTACKALLOCATOR_H
#define DESTACKALLOCATOR_H

#include "../Base/Base.h"

namespace ctm
{

/////////////////
//Double Ended Stack Allocator
class destackallocator
{
public:
	//System
		destackallocator(CHAR8 *iAlignedStack, UINT32 nSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct); //Constructor
		~destackallocator(); //Destructor
private:
	CHAR8 *stack; //Stack
};
/////////////////

}

#endif