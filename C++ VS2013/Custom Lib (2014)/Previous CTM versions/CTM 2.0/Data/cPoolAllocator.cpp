#include "cPoolAllocator.h"

//Constructor
poolallocator::poolallocator(CHAR8 *iAlignedPool, UINT32 iElements, UINT32 iAlignedElementSizeBytes, BOOL8 iAutoDestruct):
pool(iAlignedPool),
freeblocks(0),
elements(iElements),
elementsizebytes(iAlignedElementSizeBytes),
autodestruct(iAutoDestruct)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(iAlignedElementSizeBytes < sizeof(CHAR8*))); //Error: cPoolAllocator - Element size must be atleast sizeof(char*)!
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
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(freeblocks != 0)
				DEFAULT_DEBUGLOG->send_error("Error: cPoolAllocator - Not all memory was deallocated\n",false);
	#endif

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
}

//Allocate
void *poolallocator::allocate()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(DEFAULT_DEBUGLOG != 0)
			if(freeblocks == 0)
				DEFAULT_DEBUGLOG->send_error("Error: cPoolAllocator - Failed to allocate element! Out of memory!\n",true);
	#endif
	if(freeblocks == 0) return 0;

	void *blockptr = &*freeblocks; //Store pointer to memory
	freeblocks = (CHAR8**)*freeblocks; //Increment free list iterator
	return blockptr; //Return stored memory pointer
}

//Deallocate
void poolallocator::deallocate(void *pointer)
{
	*(CHAR8**)pointer = (CHAR8*)freeblocks; //Set new free block internals
	freeblocks = (CHAR8**)pointer; //Set new free block as current free block
}