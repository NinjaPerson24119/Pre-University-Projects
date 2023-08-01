#include <Custom/Memory/BlockAllocator.h>
#include <stdexcept>
#include <assert.h>

namespace ctm
{

//Constructor
BlockAllocator::BlockAllocator(char *Heap, uintptr_t HeapSize, void (*Deallocator)(void*), Optimization Choice):
heap(Heap),
heapsize(HeapSize),
deallocator(Deallocator),
allocations(0),
memoryusage(0),
memoryusagepeak(0),
optimization(Choice),
freelist(nullptr)
{
	assert(deallocator != nullptr);
	assert(Heap != nullptr);
	assert(HeapSize > sizeof(Block));

	Clear();
}

//Destructor
BlockAllocator::~BlockAllocator()
{
	if(heap != nullptr)
		throw std::runtime_error("BlockAllocator - Memory Leak! BlockAllocator was not released!\n");
}

//Clear
void BlockAllocator::Clear()
{
	ResetLists();

	allocations = 0;
	memoryusage = sizeof(Block);
	memoryusagepeak = memoryusage;
}

//Allocate
void *BlockAllocator::Allocate(uintptr_t Size, uintptr_t Alignment)
{
	//Find a block
	Block *block = nullptr;
	if(optimization == MEMORY)
	{
		Block *bestfit = nullptr;
		uintptr_t actualspace = 0;
		for(Block *iter = freelist; iter != nullptr; iter = iter->next)
		{
			actualspace = iter->size - (((uintptr_t)iter + sizeof(Block)) % (uintptr_t)Alignment);
			if(bestfit != nullptr)
			{
				if((actualspace < bestfit->size) && (actualspace >= Size))
					bestfit = iter;
			}
			else
			{
				if(actualspace >= Size)
					bestfit = iter;
			}
		}
		block = bestfit;
	}
	else
	{
		for(block = freelist; block != nullptr; block = block->next)
		{
			if(block->size - (((uintptr_t)block + sizeof(Block)) % (uintptr_t)Alignment) >= Size)
				break;
		}
	}

	if(block == nullptr)
		throw std::bad_alloc();

	//Find previous
	Block *previous = nullptr;
	for(Block *iter = freelist; iter != nullptr; iter = iter->next)
	{
		if(iter->next == block)
			break;
	}

	//Unlink chosen block into freelist
	if(previous != nullptr)
		previous->next = block->next; //Link past chosen block
	else //Reconstruct freelist in case of no previous block
		freelist = block->next;

	//Configure chosen block
	block->alignment = ((uintptr_t)block + sizeof(Block)) % Alignment;
	block->size -= block->alignment;

	//Divide chosen block
	if(Size < block->size)
	{
		if(block->size - Size > sizeof(Block))
		{
			Block *newblock = (Block*)((uintptr_t)block + sizeof(Block) + block->alignment + Size);
			newblock->alignment = 0;
			newblock->size = block->size - Size - sizeof(Block);

			if(previous != nullptr) //Link between previous and next
			{
				newblock->next = previous->next;
				previous->next = newblock;
			}
			else //Link before next
			{
				newblock->next = freelist;
				freelist = newblock;
			}
	
			//Register space change on chosen block
			block->size -= sizeof(Block) + newblock->size;
	
			//Profiling
			memoryusage += sizeof(Block);
		}
	}

	//Profiling
	++allocations;
	memoryusage += block->alignment + Size;
	if(memoryusage > memoryusagepeak)
		memoryusagepeak = memoryusage;

	//Return memory address and shift alignment
	Block temp = *block;
	block = (Block*)((uintptr_t)block + temp.alignment); //Shift up
	*block = temp; //Assign data
	return (void*)((uintptr_t)block + sizeof(Block)); //Return memory
}

//Deallocate
void BlockAllocator::Deallocate(void *Target)
{
	assert(Target != nullptr);

	//Remove alignment from block
	Block *access = (Block*)((uintptr_t)Target - sizeof(Block)); //Shift down
	Block temp = *access;
	Block *actual = (Block*)((uintptr_t)access - temp.alignment);
	*actual = temp;

	actual->size += actual->alignment;
	actual->alignment = 0;

	//Profiling
	memoryusage -= actual->size;

	//Find closest previous
	Block *prev;
	for(prev = freelist; prev != nullptr; prev = prev->next)
	{
		if((uintptr_t)prev < (uintptr_t)actual && ((uintptr_t)prev->next > (uintptr_t)actual || prev->next == nullptr))
			break;
	}

	//Set next
	Block *next;
	if(prev != nullptr) 
		next = prev->next;
	else
		next = freelist;

	//Link next block
	if(next != nullptr)
	{
		//Merge
		if((uintptr_t)actual + actual->size + sizeof(Block) == (uintptr_t)next)
		{
			actual->size += next->size + sizeof(Block);
			actual->next = next->next;
			memoryusage -= sizeof(Block);
		}
		else
		{
			actual->next = next;
			if(next == freelist)
				freelist = actual;
		}
	}
	else
		actual->next = nullptr;

	//Link previous block
	if(prev != nullptr)
	{
		//Merge
		if((uintptr_t)prev + prev->size + sizeof(Block) == (uintptr_t)actual)
		{
			prev->size += actual->size + sizeof(Block);
			prev->next = actual->next;
			memoryusage -= sizeof(Block);
		}
		else
			prev->next = actual;
	}
	else
		if(freelist == nullptr)
			freelist = actual;
}

//Reset Lists
void BlockAllocator::ResetLists()
{
	freelist = (Block*)heap;
	freelist->next = nullptr;
	freelist->alignment = 0;
	freelist->size = heapsize - sizeof(Block);
}

//Release
void BlockAllocator::Release()
{
	assert(heap != nullptr);
	deallocator((void*)heap);
	heap = nullptr;
}

}