#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../Base/Base.h"

namespace ctm
{

//Note: maxmemory is only used for statistics calculations and must be set by the object user
//	    maxmemory specifies a target maximum memory usage amount

/////////////////////////
//Allocator class
class allocator
{
public:
	//System
		
	//Memory
		virtual void *allocate(UINT32 nSizeBytes); //Allocates a specified amount of memory
		virtual void deallocate(void *pointer); //Deallocates memory
	//Get
		virtual UINT32 get_size() { return maxmemory; } //Returns the amount of memory both used and unused in bytes
		virtual UINT32 get_unused() { return maxmemory-memoryused; } //Returns the amount of memory left before reaching max memory target
		virtual UINT32 get_used() { return memoryused; } //Returns the amount of memory used in bytes
		virtual UINT32 get_blocks() { return blocks; } //Returns the amount of memory blocks allocated
	UINT32 maxmemory; //Specified target maximum memory usage
private:
	UINT32 memoryused; //Memory used in bytes
	UINT32 blocks; //Blocks allocated
};
/////////////////////////

}

#endif