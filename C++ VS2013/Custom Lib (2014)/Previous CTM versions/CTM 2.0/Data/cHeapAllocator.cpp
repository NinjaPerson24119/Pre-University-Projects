#include "cHeapAllocator.h"

//Constructor
heapallocator::heapallocator(CHAR8 *iHeap, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct):
heap(iHeap),
size(iSizeBytes),
alignment(iAlignment),
autodestruct(iAutoDestruct)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(iSizeBytes < sizeof(memblock))); //Error: cHeapAllocator - Size of heap must be atleast sizeof(memblock)!
	#endif

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(alignment == 0)
				DEFAULT_DEBUGLOG->send_error("Error: cHeapAllocator - Alignment cannot be 0! Setting alignment to 1!\n",false);
	#endif
	if(alignment == 0)
		alignment = 1;

	//Set up free list
	memblock init;
	init.size = size-sizeof(memblock); //Set initial heap size
	*(memblock*)heap = init; //Insert initial memory block
	freeblocks = (memblock*)heap; //Set start of free list
}

//Copy constructor
heapallocator::heapallocator(heapallocator &rhs)
{}

//Destructor
heapallocator::~heapallocator()
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(freeblocks->ptr != 0)
				DEFAULT_DEBUGLOG->send_error("Error: cHeapAllocator - Not all memory was not deallocated!\n",false);
	#endif

	//Auto destruct if set
	if(autodestruct == true)
		delete[] heap;
}

//Operator =
heapallocator &heapallocator::operator=(heapallocator &rhs)
{
	return *this;
}

//Clear
void heapallocator::clear()
{
	//Set up free list
	memblock init;
	init.size = size-sizeof(memblock); //Set initial heap size
	*(memblock*)heap = init; //Insert initial memory block
	freeblocks = (memblock*)heap; //Set start of free list
}

//Allocate
void *heapallocator::allocate(UINT32 nSizeBytes)
{
	//Search for large enough block
	memblock *iter = freeblocks; //Set iterator to start of free list
	UINT32 buffersize = 0; //Buffer size
	while(iter != 0)
	{
		//Calculate buffer size
		buffersize = (UINT32)iter%alignment; //Calculate memblock adjustment
		if(buffersize < sizeof(CHAR8)) //Buffer must be atleast sizeof(char)
			buffersize += alignment;

		//Check block size
		if(buffersize + nSizeBytes <= iter->size)
		{
			*((CHAR8*)iter+sizeof(memblock)+buffersize-1) = (UCHAR8)buffersize;
			//Store buffer size at end of buffer
			if(iter->size - (buffersize+nSizeBytes) >= sizeof(memblock)+alignment+1) //Check if free block will remain large enough for another allocation
			{
				//Make new free block
				memblock *newfreeblock = (memblock*)((CHAR8*)iter+sizeof(memblock)+buffersize+nSizeBytes); //Calculate location
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
			
			return (void*)((CHAR8*)iter+sizeof(memblock)+buffersize);
		}
		iter = iter->ptr; //Increment iterator
	}

	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send_error("Error: cHeapAllocator - Failed to allocate block! Out of memory!\n",true);
	#endif
	return 0;
}

//Deallocate
void heapallocator::deallocate(void *pointer)
{
	//Search for ajacent blocks
	UCHAR8 buffersize = (UCHAR8)*((CHAR8*)pointer-1);
	memblock* target = (memblock*)((CHAR8*)pointer-buffersize-sizeof(memblock)); //Offset pointer to header
	memblock *iter = freeblocks; //Set iterator to start of free list
	memblock *before = 0; //Pointer to memblock before target block
	memblock *after = 0; //Pointer to memblock after target block
	
	while(iter != 0)
	{
		if((CHAR8*)iter + iter->size < (CHAR8*)target) //Check that iterator is before target
			if(((CHAR8*)iter->ptr > (CHAR8*)target + target->size + sizeof(memblock)) || (iter->ptr == 0)) //Check that next iterator is after target or 0
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
}

heapallocator *DEFAULT_HEAPALLOCATOR = 0;