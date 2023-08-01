#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

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
		stackallocator(CHAR8 *iAlignedStack, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct); //AutoDestruct means that the allocator will delete the memory block provided upon its destruction
		~stackallocator();
	//Memory
		void clear(); //Clears the stack
		void* allocate(UINT32 sizebytes); //Allocates a specified amount of memory
		void deallocate(void *pointer); //Deallocates memory upto a marker
	//Get
		UINT32 get_size() { return size; } //Returns the stack size
		UINT32 get_unused() { return size-top; } //Returns the amount of memory left
		UINT32 get_used() { return top; } //Returns the amount of memory used
		UINT32 get_blocks() { return blocks; } //Returns the amount of blocks allocated
private:
	//Inaccessible
		stackallocator(stackallocator &rhs);
		stackallocator &operator=(stackallocator &rhs);
	CHAR8 *stack; //Stack
	UINT32 size; //Size of stack
	UINT32 top; //Points to top of allocator stack
	UINT32 alignment; //Stack alignment
	UINT32 blocks; //Blocks allocated
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
};
////////////////////////

}

#endif