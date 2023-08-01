#include <Custom/Memory/OverrideMemory.h>
#include <stdexcept>
#include <assert.h>

#pragma warning(disable: 4290)

namespace ctm
{

static ctm::BlockAllocator *alloc = nullptr;
static uintptr_t allocalignment = 4;

void SetMemoryAllocator(BlockAllocator *Allocator)
{
	alloc = Allocator;
}

void SetMemoryAlignment(uintptr_t Alignment)
{
	assert(Alignment != 0);
	allocalignment = Alignment;
}

}

void *operator new(size_t Size) throw(std::bad_alloc)
{
	assert(ctm::alloc != nullptr);
	return ctm::alloc->Allocate(Size, ctm::allocalignment);
}

void operator delete(void *Target) throw()
{
	assert(ctm::alloc != nullptr);
	assert(Target != nullptr);
	ctm::alloc->Deallocate(Target);
}

void *operator new(size_t Size, const std::nothrow_t&) throw()
{
	try
	{
		assert(ctm::alloc != nullptr);
		return ctm::alloc->Allocate(Size, ctm::allocalignment);
	}
	catch(...)
	{
		return nullptr;
	}
}

void operator delete(void *Target, const std::nothrow_t&) throw()
{
	assert(ctm::alloc != nullptr);
	assert(Target != nullptr);
	ctm::alloc->Deallocate(Target);
}

void *operator new[](size_t Size) throw(std::bad_alloc)
{
	assert(ctm::alloc != nullptr);
	return ctm::alloc->Allocate(Size, ctm::allocalignment);
}

void operator delete[](void *Target) throw()
{
	assert(ctm::alloc != nullptr);
	assert(Target != nullptr);
	ctm::alloc->Deallocate(Target);
}

void *operator new[](size_t Size, const std::nothrow_t&) throw()
{
	try
	{
		assert(ctm::alloc != nullptr);
		return ctm::alloc->Allocate(Size, ctm::allocalignment);
	}
	catch(...)
	{
		return nullptr;
	}
}

void operator delete[](void *Target, const std::nothrow_t&) throw()
{
	assert(ctm::alloc != nullptr);
	assert(Target != nullptr);
	ctm::alloc->Deallocate(Target);
}