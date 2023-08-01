#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

#include "../Base/Base.h"

namespace ctm
{

////////////////////////
//Stack Allocator class
class stackallocator
{
public:
	//System
		stackallocator(CHAR8 *iAlignedStack, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct);
		~stackallocator();
	//Memory
		void clear(); //Clears the stack
		void* allocate(UINT32 sizebytes); //Allocates a specified amount of memory
		void deallocate(UINT32 marker); //Deallocates memory upto a marker
		void resize(UINT32 nSizeBytes); //Resizes the stack
		UINT32 get_top() { return top; } //Returns the stack top
		UINT32 get_size() { return size; } //Returns the stack size
private:
	//Inaccessible
		stackallocator(stackallocator &rhs);
		stackallocator &operator=(stackallocator &rhs);
	CHAR8 *stack; //Stack
	UINT32 size; //Size of stack
	UINT32 top; //Points to top of allocator stack
	UINT32 alignment; //Stack alignment
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
};
////////////////////////

}

#endif