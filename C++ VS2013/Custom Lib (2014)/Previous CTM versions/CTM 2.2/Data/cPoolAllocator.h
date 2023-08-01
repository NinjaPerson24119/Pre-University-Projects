#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

//NOTE: Elements must be atleast the size of a pointer

/////////////////////////
//Pool allocator class
class poolallocator : public allocator
{
public:
	//Sytem
		poolallocator(CHAR8 *iAlignedPool, UINT32 iElements, UINT32 iAlignedElementSizeBytes, BOOL8 iAutoDestruct); //AutoDestruct means that the allocator will delete the memory block provided upon its destruction
		~poolallocator();
	//Memory
		void clear(); //Clears the pool
		void* allocate(UINT32 nUnused); //Allocates an element in the pool
		void deallocate(void *pointer); //Deallocates an element in the pool
	//Get
		UINT32 get_size() { return elements*elementsizebytes; } //Returns the pool size
		UINT32 get_unused() { (elements-elementsused)*elementsizebytes; } //Returns the amount of memory unused
		UINT32 get_used() { return elementsused*elementsizebytes; } //Returns the amount of memory used
		UINT32 get_blocks() { return elementsused; } //Returns the amount of blocks allocated
		UINT32 get_elementsize() { return elementsizebytes; } //Returns the size of an element in bytes
private:
	//Inaccessible
		poolallocator(poolallocator &rhs);
		poolallocator &operator=(poolallocator &rhs);
	CHAR8 *pool; //Pool
	CHAR8 **freeblocks; //List of free elements
	UINT32 elements; //Amount of elements in pool
	UINT32 elementsizebytes; //Size of an element
	UINT32 elementsused; //Elements used
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
};
/////////////////////////

}

#endif