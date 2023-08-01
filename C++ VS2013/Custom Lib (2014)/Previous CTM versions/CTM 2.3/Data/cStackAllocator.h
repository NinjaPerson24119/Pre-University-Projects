#ifndef CTM_STACKALLOCATOR_H
#define CTM_STACKALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

////////////////////////
//Stack Allocator class
class stackallocator : public allocator
{
public:
	//System
		stackallocator(char *iStack, size_t iSizeBytes, size_t iAlignment, bool iAutoDeleteMemory);
		~stackallocator();
	//Memory
		void clear(); //Clears the stack
		void* allocate(size_t nSizeBytes); //Allocates a specified amount of memory
		void deallocate(void *pointer); //Deallocates memory upto a marker
	//Get
		size_t get_size() { return size; } //Returns the stack size
		size_t get_unused() { return size-top; } //Returns the amount of memory left
		size_t get_used() { return top; } //Returns the amount of memory used
		size_t get_blocks() { return blocks; } //Returns the amount of blocks allocated
private:
	//Inaccessible
		stackallocator(stackallocator &rhs);
		stackallocator &operator=(stackallocator &rhs);
	char *stack; //Stack
	size_t size; //Size of stack
	size_t top; //Points to top of allocator stack
	size_t alignment; //Stack alignment
	size_t blocks; //Blocks allocated
	bool autodestruct; //Delete data when allocator is destroyed?
};
////////////////////////

}

#endif