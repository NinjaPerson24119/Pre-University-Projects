#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

////////////////////////////
//Shared pointer shared data
template<class type> class sptrsd
{
public:
	sptrsd(): rawptr(0), deallocator(0), references(0), alloc(0) {}
	type *rawptr; //Raw pointer
	allocator *alloc; //Allocator
	void(*deallocator)(void *pointer); //Deallocator
	UINT32 references; //References
};
////////////////////////////

////////////////////////////
//Shared pointer class
template<class type> class sptr
{
public:
	//System
		sptr(allocator *iAlloc); //Constructor
		sptr(type *iPointer, allocator *iAlloc);
		sptr(type *iPointer, void (*iDeallocator)(void *pointer), allocator *iAlloc);
		sptr(sptr &rhs); //Copy constructor
		~sptr(); //Destructor
		sptr &operator=(sptr &rhs); //Operator =
		sptr &operator=(type *nPointer);
	//Memory
		void deallocate(); //Deallocates and clears data
		void set_deallocator(void (*nDeallocator)(void *pointer)); //Set function used to deallocate data
		type &operator[](UINT32 index); //Operator []
		type &operator*(); //Operator *
		type *operator->(); //Operator ->
private:
	sptrsd *sd; //Shared data
};
////////////////////////////

}

#endif