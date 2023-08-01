#ifndef CTM_ALLOCATOR_H
#define CTM_ALLOCATOR_H

#include "pstdint.h"

namespace ctm
{

const uintptr_t ALLOCATOR_ALIGNMENT = 4;

//////
//Allocator
class Allocator
{
public:
	//Profiling
		virtual uintptr_t Capacity() = 0;
		virtual uintptr_t MemoryUsed() = 0;
		virtual uintptr_t MemoryPeak() = 0;
		virtual uintptr_t Allocations() = 0;
};
//////

}

#endif