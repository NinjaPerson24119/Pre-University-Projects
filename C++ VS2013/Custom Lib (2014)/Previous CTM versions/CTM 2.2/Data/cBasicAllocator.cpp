#include "cBasicAllocator.h"

namespace ctm
{

//Allocate
void *basicallocator::allocate(UINT32 nSizeBytes)
{
	return (void*)new CHAR8[nSizeBytes];
}

//Deallocate
void basicallocator::deallocate(void *pointer)
{
	delete[] pointer;
}

//Set maxmemory
void basicallocator::set_maxmemory(UINT32 nMaxMemory)
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(nMaxMemory < memoryused)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cBasicAllocator - Failed to set maxmemory! New maxmemory must be greater than the amount of memory already in use!\n",true);
		}
	#endif

	maxmemory = nMaxMemory;
}

}