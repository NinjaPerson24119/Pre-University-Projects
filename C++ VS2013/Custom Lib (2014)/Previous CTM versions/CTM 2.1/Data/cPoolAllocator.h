#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include "../Base/Base.h"

namespace ctm
{

/////////////////////////
//Pool allocator class
class poolallocator
{
public:
	//Sytem
		poolallocator(CHAR8 *iAlignedPool, UINT32 iElements, UINT32 iAlignedElementSizeBytes, BOOL8 iAutoDestruct);
		~poolallocator();
	//Memory
		void clear(); //Clears the pool
		void* allocate(); //Allocates an element in the pool
		void deallocate(void *pointer); //Deallocates an element in the pool
		UINT32 get_elements() { return elements; } //Returns the amount of elements
		UINT32 get_elementsizebytes() { return elementsizebytes; } //Returns the size of an element
private:
	//Inaccessible
		poolallocator(poolallocator &rhs);
		poolallocator &operator=(poolallocator &rhs);
	CHAR8 *pool; //Pool
	CHAR8 **freeblocks; //List of free elements
	UINT32 elements; //Amount of elements in pool
	UINT32 elementsizebytes; //Size of an element
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
};
/////////////////////////

}

#endif