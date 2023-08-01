#ifndef CTM_POOLALLOCATOR_H
#define CTM_POOLALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"
#include "cProfileableAllocator.h"

namespace ctm
{

//NOTE: Size of elements must be atleast sizeof(void*)

/////////////////////////
//Pool allocator class
class poolallocator : public allocator, public profileableallocator
{
public:
	//Sytem
		poolallocator(char *iPool, size_t iElements, size_t iElementSizeBytes, bool iAutoDeleteMemory);
		~poolallocator();
	//Memory
		void clear(); //Clears the pool
		void* allocate(size_t nUnused); //Allocates an element in the pool
		void deallocate(void *pointer); //Deallocates an element in the pool
	//Get
		size_t get_size() { return elements*elementsizebytes; } //Returns the pool size
		size_t get_unused() { return (elements-elementsused)*elementsizebytes; } //Returns the amount of memory unused
		size_t get_used() { return elementsused*elementsizebytes; } //Returns the amount of memory used
		size_t get_blocks() { return elementsused; } //Returns the amount of blocks allocated
		size_t get_elementsize() { return elementsizebytes; } //Returns the size of an element in bytes
private:
	//Inaccessible
		poolallocator(poolallocator &rhs);
		poolallocator &operator=(poolallocator &rhs);
	char *pool; //Pool
	char **freeblocks; //List of free elements
	size_t elements; //Amount of elements in pool
	size_t elementsizebytes; //Size of an element
	size_t elementsused; //Elements used
	bool autodeletememory; //Delete data when allocator is destroyed?
};
/////////////////////////

}

#endif