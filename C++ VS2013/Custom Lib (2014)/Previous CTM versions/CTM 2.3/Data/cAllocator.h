#ifndef CTM_ALLOCATOR_H
#define CTM_ALLOCATOR_H

#include "../Base/Base.h"

namespace ctm
{

extern allocator *DEFAULT_ALLOCATOR;

/////////////////////////
//Allocator class
class allocator
{
public:
	//Memory
		virtual void clear() = 0; //Clears all allocated memory
		virtual void *allocate(size_t nSizeBytes) = 0; //Allocates a specified amount of memory
		virtual void deallocate(void *pointer) = 0; //Deallocates memory
	//Get
		virtual size_t get_size() = 0; //Returns the amount of memory both used and unused in bytes
		virtual size_t get_unused() = 0; //Returns the amount of memory left
		virtual size_t get_used() = 0; //Returns the amount of memory used in bytes
		virtual size_t get_blocks() = 0; //Returns the amount of memory blocks allocated
};
/////////////////////////

}

#endif