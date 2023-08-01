#include "cPoolAllocator.h"

namespace ctm
{

//Constructor
poolallocator::poolallocator(CHAR8 *iAlignedPool, UINT32 iElements, UINT32 iAlignedElementSizeBytes, BOOL8 iAutoDestruct):
pool(iAlignedPool),
freeblocks(0),
elements(iElements),
elementsizebytes(iAlignedElementSizeBytes),
elementsused(0),
autodestruct(iAutoDestruct)
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(iAlignedElementSizeBytes < sizeof(CHAR8*))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cPoolAllocator - Element size must be atleast sizeof(char*)!\n",true);
		}
	#endif
	
	//Setup free list
	freeblocks = (CHAR8**)pool; //Set iterator
	for(UINT32 count = 0; count < elements-1; ++count)
	{
		*freeblocks = &pool[(count+1)*elementsizebytes]; //Set list element
		freeblocks = (CHAR8**)*freeblocks; //Increment iterator
	}
	*freeblocks = 0; //Zero out end of list
	freeblocks = (CHAR8**)pool; //Reset iterator
}

//Copy constructor
poolallocator::poolallocator(poolallocator &rhs)
{}

//Destructor
poolallocator::~poolallocator()
{
	//Auto destruct if set
	if(autodestruct == true)
		delete[] pool;
}

//Operator =
poolallocator &poolallocator::operator=(poolallocator &rhs)
{
	return *this;
}

//Clear
void poolallocator::clear()
{
	//Setup free list
	freeblocks = (CHAR8**)pool; //Set iterator
	for(UINT32 count = 0; count < elements-1; ++count)
	{
		*freeblocks = &pool[(count+1)*elementsizebytes]; //Set list element
		freeblocks = (CHAR8**)*freeblocks; //Increment iterator
	}
	*freeblocks = 0; //Zero out end of list
	freeblocks = (CHAR8**)pool; //Reset iterator
	elementsused = 0; //Update memory usage
}

//Allocate
void *poolallocator::allocate(UINT32 nUnused)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(DEFAULT_DEBUGLOG != 0)
			if(freeblocks == 0)
				DEFAULT_DEBUGLOG->send("Error: cPoolAllocator - Failed to allocate element! Out of memory!\n",true);
	#endif
	if(freeblocks == 0) return 0;

	void *blockptr = &*freeblocks; //Store pointer to memory
	freeblocks = (CHAR8**)*freeblocks; //Increment free list iterator
	elementsused += elementsizebytes; //Update memory usage
	return blockptr; //Return stored memory pointer
}

//Deallocate
void poolallocator::deallocate(void *pointer)
{
	*(CHAR8**)pointer = (CHAR8*)freeblocks; //Set new free block internals
	freeblocks = (CHAR8**)pointer; //Set new free block as current free block
	elementsused -= elementsizebytes; //Update memory usage
}

}