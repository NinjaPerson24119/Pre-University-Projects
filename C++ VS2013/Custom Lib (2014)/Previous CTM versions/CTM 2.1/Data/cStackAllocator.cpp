#include "cStackAllocator.h"

namespace ctm
{

//Constructor
stackallocator::stackallocator(CHAR8 *iAlignedStack, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct):
stack(iAlignedStack),
size(iSizeBytes),
top(0),
alignment(iAlignment),
autodestruct(iAutoDestruct)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(alignment == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cStackAllocator - Alignment cannot be 0!\n",true);
		assert(0);
	}
	#endif
}

//Copy constructor
stackallocator::stackallocator(stackallocator &rhs)
{}

//Destructor
stackallocator::~stackallocator()
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(top != 0)
				DEFAULT_DEBUGLOG->send("Error: cStackAllocator - Stack was not fully deallocated!",false);
	#endif

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
void* stackallocator::allocate(UINT32 sizebytes)
{
	//Align size
	size += size%alignment;

	//Check that space exists
	if(top + sizebytes <= size)
	{
		void *pointer = &stack[top]; //Store pointer to block
		top = top + sizebytes; //Move top
		return pointer; //Return pointer
	}
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cStackAllocator - Failed to allocate memory! Stack is full!\n",true);
	#endif
	return 0; //Failed to allocate memory (Stack is full)
}

//Deallocate
void stackallocator::deallocate(UINT32 marker)
{
	top = marker;
}

}