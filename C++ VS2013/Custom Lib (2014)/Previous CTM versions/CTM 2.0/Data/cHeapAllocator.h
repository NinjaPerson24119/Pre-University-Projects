#ifndef HEAPALLOCATOR_H
#define HEAPALLOCATOR_H

#include "../Base/Base.h"

////////////////////////
//Memory block class
class memblock
{
public:
	memblock(): ptr(0), size(0) {}
	UINT32 size; //Size of memory block
	memblock *ptr; //Pointer to next memory block
};
////////////////////////

////////////////////////
//Heap allocator class
class heapallocator
{
public:
	//System
		heapallocator(CHAR8 *iHeap, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct);
		~heapallocator();
	//Memory
		void clear(); //Clears the heap
		void *allocate(UINT32 nSizeBytes); //Allocates a specified amount of memory
		void deallocate(void *pointer); //Deallocates memory
		UINT32 get_size() { return size; } //Returns the size of the heap
private:
	//Inaccessible
		heapallocator(heapallocator &rhs);
		heapallocator &operator=(heapallocator &rhs);
	CHAR8 *heap; //Heap
	memblock *freeblocks; //List of free blocks
	UINT32 size; //Size of heap
	UINT32 alignment; //Heap alignment
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
};
////////////////////////

extern heapallocator *DEFAULT_HEAPALLOCATOR;

#endif