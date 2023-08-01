#include "HeapAllocator.h"

namespace ctm
{

//Constructor
HeapAllocator::HeapAllocator(char *Heap, void (*Deallocator)(void *), uintptr_t SizeBytes, bool OptimizeForMemory):
heap(Heap),
deallocator(Deallocator),
heapsize(SizeBytes),
memoryused(0),
memorypeak(0),
allocations(0),
optimizeformemory(OptimizeForMemory)
{
	#ifdef CTM_DEBUG_FAST
		if(iSizeBytes < sizeof(memblock))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cHeapAllocator - Size of heap must be atleast sizeof(memblock)!\n",true);
		}
	#endif

	#ifdef CTM_DEBUG_FAST
		if(alignment == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cHeapAllocator - Alignment cannot be 0!\n",true);
		}
	#endif

	//Set up free list
	memblock init;
	init.size = size-sizeof(memblock); //Set initial heap size
	*(memblock*)heap = init; //Insert initial memory block
	freeblocks = (memblock*)heap; //Set start of free list
}

//Copy constructor
HeapAllocator::HeapAllocator(HeapAllocator &rhs)
{}

//Destructor
HeapAllocator::~HeapAllocator()
{
	//Auto delete memory if set
	if(autodeletememory == true)
		delete[] heap;
}

//Operator =
HeapAllocator &HeapAllocator::operator=(HeapAllocator &rhs)
{
	return *this;
}

//Clear
void HeapAllocator::clear()
{
	//Set up free list
	memblock init;
	init.size = size-sizeof(memblock); //Set initial heap size
	*(memblock*)heap = init; //Insert initial memory block
	freeblocks = (memblock*)heap; //Set start of free list
	memused = 0; //Update memory usage
}

//Allocate
void *HeapAllocator::allocate(size_t nSizeBytes)
{
	//Search for large enough block
	memblock *iter = freeblocks; //Set iterator to start of free list
	size_t buffersize = 0; //Buffer size

	//Find best fit block
	memblock *bestfitblock = 0; //Pointer to best fit block
	size_t bestfitsize = size; //Size of best fit block
	if(optimizeformemory == true)
	{
		while(iter != 0)
		{
			//Calculate buffer size
			buffersize = (size_t)iter%alignment; //Calculate memblock adjustment
			if(buffersize < sizeof(unsigned char)) //Buffer must be atleast sizeof(char)
				buffersize += alignment;
		
			//Check fit
			if((iter->size < bestfitsize) && (buffersize + nSizeBytes <= iter->size))
			{
				bestfitsize = buffersize + nSizeBytes;
				bestfitblock = iter;
			}

			iter = iter->ptr; //Increment iterator
		}
		iter = bestfitblock; //Set initial cycle to best fitting block
	}

	while(iter != 0)
	{
		//Calculate buffer size
		buffersize = (size_t)iter%alignment; //Calculate memblock adjustment
		if(buffersize < sizeof(unsigned char)) //Buffer must be atleast sizeof(char)
			buffersize += alignment;

		if(buffersize + nSizeBytes <= iter->size)
		{
			*((char*)iter+sizeof(memblock)+buffersize-1) = (unsigned char)buffersize;
			
			//Store buffer size at end of buffer
			if(iter->size - (buffersize+nSizeBytes) >= sizeof(memblock)+alignment+1) //Check if free block will remain large enough for another allocation
			{
				//Make new free block
				memblock *newfreeblock = (memblock*)((char*)iter+sizeof(memblock)+buffersize+nSizeBytes); //Calculate location
				newfreeblock->ptr = iter->ptr; //Link to next block
				newfreeblock->size = iter->size-buffersize-nSizeBytes; //Calculate new size

				//Search for previous free block
				memblock *previter = freeblocks;
				while(previter != 0)
				{
					if(previter->ptr == iter)
						break;
					previter = previter->ptr; //Increment iterator
				}
				if(previter != 0) //Link previous block to new block
					previter->ptr = newfreeblock;
				else
					freeblocks = newfreeblock;
			}
			else
			{
				//Search for previous free block
				memblock *previter = freeblocks;
				while(previter != 0)
				{
					if(previter->ptr == iter)
						break;
					previter = previter->ptr; //Increment iterator
				}
				if(previter != 0) //Link previous past new block
					previter->ptr = iter->ptr;
				else
					freeblocks = iter->ptr;
			}
			memused += sizeof(memblock)+buffersize+nSizeBytes; //Update memory usage
			++blocks; //Updates blocks in use
			return (void*)((char*)iter+sizeof(memblock)+buffersize);
		}
		iter = iter->ptr; //Increment iterator
	}

	#ifdef CTM_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cHeapAllocator - Failed to allocate block! Out of memory!\n",true);
	#endif
	return 0;
}

//Deallocate
void HeapAllocator::deallocate(void *pointer)
{
	//Search for ajacent blocks
	unsigned char buffersize = (unsigned char)*((char*)pointer-1);
	memblock* target = (memblock*)((char*)pointer-buffersize-sizeof(memblock)); //Offset pointer to header
	memblock *iter = freeblocks; //Set iterator to start of free list
	memblock *before = 0; //Pointer to memblock before target block
	memblock *after = 0; //Pointer to memblock after target block
	memused -= sizeof(memblock)+target->size; //Update memory usage

	while(iter != 0)
	{
		if((char*)iter + iter->size < (char*)target) //Check that iterator is before target
			if(((char*)iter->ptr > (char*)target + target->size + sizeof(memblock)) || (iter->ptr == 0)) //Check that next iterator is after target or 0
			{
				before = iter;
				after = iter->ptr;
				break;
			}
		iter = iter->ptr; //Increment iterator
	}

	//Insert target back into free list
	if(before != 0) //Combine before
		before->size += target->size;
	if(after != 0) //Combine after
		if(before != 0) //Before was linked
		{
			before->size += after->size; //Resize past after
			before->ptr = after->ptr; //Link to block after after
		}
		else //Before was not linked
		{
			//Find block that links to after (If existant)
			iter = freeblocks; //Reset iterator
			while(iter != 0)
			{
				if(iter->ptr == after)
				{
					iter->ptr = target; //Link block linked to after to target
					break;
				}
				iter = iter->ptr; //Increment iterator
			}
			target->size += after->size; //Resize past after
			target->ptr = after->ptr; //Link target to block after after
		}
	if((before == 0) && (after == 0)) //No adjacent blocks exist
	{
		//Find end of free list
		iter = freeblocks; //Reset iterator
		if(iter == 0) //Link end of free list to target (Special case)
			freeblocks = target;
		while(iter != 0)
		{
			if(iter->ptr == 0)
			{
				iter->ptr = target; //Link end of free list to target
				break;
			}
			iter = iter->ptr; //Increment iterator
		}
	}
	--blocks; //Update blocks in use
}

}