#ifndef CTM_HEAPALLOCATOR_H
#define CTM_HEAPALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

////////////////////////
//Memory block class
class memblock
{
public:
	memblock(): ptr(0), size(0) {}
	size_t size; //Size of memory block
	memblock *ptr; //Pointer to next memory block
};
////////////////////////

////////////////////////
//Heap allocator class
class heapallocator : public allocator
{
public:
	//System
		heapallocator(char *iHeap, size_t iSizeBytes, size_t iAlignment, bool iAutoDeleteMemory, bool iOptimizeForMemory);
		~heapallocator();
	//Memory
		void clear(); //Clears the heap
		void *allocate(size_t nSizeBytes); //Allocates a specified amount of memory
		void deallocate(void *pointer); //Deallocates memory
	//Get
		size_t get_size() { return size; } //Returns the size of the heap
		size_t get_unused() { return size-memused; } //Returns the amount of memory left
		size_t get_used() { return memused; } //Returns the amount of memory in use
		size_t get_blocks() { return blocks; } //Returns the amount of blocks allocated
private:
	//Inaccessible
		heapallocator(heapallocator &rhs);
		heapallocator &operator=(heapallocator &rhs);
	char *heap; //Heap
	memblock *freeblocks; //List of free blocks
	size_t size; //Size of heap
	size_t memused; //Memory used
	size_t alignment; //Heap alignment
	size_t blocks; //Blocks allocated
	bool autodeletememory; //Delete data when allocator is destroyed?
	bool optimizeformemory; //Optimize for memory?
};
////////////////////////

}

#endif