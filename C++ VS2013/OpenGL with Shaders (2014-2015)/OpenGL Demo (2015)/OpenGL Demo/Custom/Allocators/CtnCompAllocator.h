#ifndef CTM_CTNCOMPALLOCATOR_H
#define CTM_CTNCOMPALLOCATOR_H

namespace ctm
{

namespace allocs
{

//////
//Container Compatible Allocator
class CtnCompAllocator
{
public:
	virtual void Deallocate(void *Pointer) = 0;
};
//////

}}

#endif