#ifndef BASICALLOCATOR_H
#define BASICALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

//////////////////////
//Basic Allocator class (new/delete)
class basicallocator : allocator
{
public:
	//System
		basicallocator(); //Constructor
	//Memory
		void *allocate(UINT32 nSizeBytes); //Allocates data
		void deallocate(void *pointer); //Deallocates data
	//Set
		void set_maxmemory(UINT32 nMaxMemory); //Sets the maximum amount of data the allocator can use
	//Get
		void get_maxmemory() { return maxmemory; } //Returns the maximum amount of data the allocator can use
		UINT32 get_size() { return maxmemory; } //Returns the amount of memory both used and unused in bytes
		UINT32 get_unused() { return maxmemory - memoryused; } //Returns the amount of memory left before reaching max memory target
		UINT32 get_used() { return memoryused; } //Returns the amount of memory used in bytes
		UINT32 get_blocks() { return blocks; } //Returns the amount of memory blocks allocated
private:
	UINT32 blocks; //Blocks allocated
	UINT32 maxmemory; //Target max memory
	UINT32 memoryused;
};
//////////////////////

}

#endif