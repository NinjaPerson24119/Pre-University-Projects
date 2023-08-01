#include "cPoolAllocator.h"

namespace ctm
{

//Constructor
poolallocator::poolallocator(char *iPool, size_t iElements, size_t iElementSizeBytes, bool iAutoDeleteMemory):
pool(iPool),
freeblocks(0),
elements(iElements),
elementsizebytes(iElementSizeBytes),
elementsused(0),
autodestruct(iAutoDeleteMemory)
{
	#ifdef CTM_DEBUG_FAST
		if(iAlignedElementSizeBytes < sizeof(char*))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cPoolAllocator - Element size must be atleast sizeof(char*)!\n",true);
		}
	#endif
	
	//Setup free list
	freeblocks = (char**)pool; //Set iterator
	for(size_t count = 0; count < elements-1; ++count)
	{
		*freeblocks = &pool[(count+1)*elementsizebytes]; //Set list element
		freeblocks = (char**)*freeblocks; //Increment iterator
	}
	*freeblocks = 0; //Zero out end of list
	freeblocks = (char**)pool; //Reset iterator
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
	freeblocks = (char**)pool; //Set iterator
	for(size_t count = 0; count < elements-1; ++count)
	{
		*freeblocks = &pool[(count+1)*elementsizebytes]; //Set list element
		freeblocks = (char**)*freeblocks; //Increment iterator
	}
	*freeblocks = 0; //Zero out end of list
	freeblocks = (char**)pool; //Reset iterator
	elementsused = 0; //Update memory usage
}

//Allocate
void *poolallocator::allocate(size_t nUnused)
{
	#ifdef CTM_DEBUG_SLOW
		if(DEFAULT_DEBUGLOG != 0)
			if(freeblocks == 0)
				DEFAULT_DEBUGLOG->send("Error: cPoolAllocator - Failed to allocate element! Out of memory!\n",true);
	#endif
	if(freeblocks == 0) return 0;

	void *blockptr = &*freeblocks; //Store pointer to memory
	freeblocks = (char**)*freeblocks; //Increment free list iterator
	elementsused += elementsizebytes; //Update memory usage
	return blockptr; //Return stored memory pointer
}

//Deallocate
void poolallocator::deallocate(void *pointer)
{
	*(char**)pointer = (char*)freeblocks; //Set new free block internals
	freeblocks = (char**)pointer; //Set new free block as current free block
	elementsused -= elementsizebytes; //Update memory usage
}

}