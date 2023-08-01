#include "cStackAllocator.h"

namespace ctm
{

//Constructor
stackallocator::stackallocator(char *iStack, size_t iSizeBytes, size_t iAlignment, bool iAutoDeleteMemory):
stack(iStack),
size(iSizeBytes),
top(0),
alignment(iAlignment),
blocks(0),
autodestruct(iAutoDeleteMemory)
{
	#ifdef CTM_DEBUG_FAST
	if(alignment == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cStackAllocator - Alignment cannot be 0!\n",true);
	}
	#endif
}

//Copy constructor
stackallocator::stackallocator(stackallocator &rhs)
{}

//Destructor
stackallocator::~stackallocator()
{
	//Auto destruct if set
	if(autodestruct == true)
		delete[] stack;
}

//Operator = 
stackallocator &stackallocator::operator=(stackallocator &rhs)
{
	return *this;
}

//Clear
void stackallocator::clear()
{
	deallocate(0); //Deallocate all memory
}

//Allocate
void* stackallocator::allocate(size_t nSizeBytes)
{
	//Align size
	size += size%alignment;

	//Check that space exists
	if(top + nSizeBytes <= size)
	{
		void *pointer = &stack[top]; //Store pointer to block
		top = top + nSizeBytes; //Move top
		++blocks; //Update blocks in use
		return pointer; //Return pointer
	}
	#ifdef CTM_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cStackAllocator - Failed to allocate memory! Stack is full!\n",true);
	#endif
	return 0; //Failed to allocate memory (Stack is full)
}

//Deallocate
void stackallocator::deallocate(void *pointer)
{
	top = top - ((size_t)&stack[top] - (size_t)pointer);
	--blocks; //Update blocks in use
}

}