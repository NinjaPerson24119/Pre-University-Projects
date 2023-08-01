#ifndef CTM_SHAREDPOINTER_H
#define CTM_SHAREDPOINTER_H



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
	size_t references; //References
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
		sptr(sptr<type> &rhs); //Copy constructor
		~sptr(); //Destructor
		sptr<type> &operator=(sptr<type> &rhs); //Operator =
		sptr<type> &operator=(type *nPointer);
	//Memory
		void deallocate(); //Deallocates and clears data
		void set_deallocator(void (*nDeallocator)(void *pointer)); //Set function used to deallocate data
		type &operator[](size_t index); //Operator []
		type &operator*(); //Operator *
		type *operator->(); //Operator ->
private:
	sptrsd *sd; //Shared data
};

//Constructor
template<class type> sptr<type>::sptr(allocator *iAlloc)
{
	sd = (sptrsd*)iAlloc->allocate(sizeof(sptrsd)); //Allocate shared data
	sd->alloc = iAlloc; //Set allocator
	sd->references = 1; //Set references
}

template<class type> sptr<type>::sptr(type *iPointer, allocator *iAlloc)
{
	sd = (sptrsd*)iAlloc->allocate(sizeof(sptrsd)); //Allocate shared data
	sd->rawptr = iPointer; //Set pointer
	sd->alloc = iAlloc; //Set allocator
	sd->references = 1; //Set references
}

template<class type> sptr<type>::sptr(type *iPointer, void(*iDeallocator)(void *pointer), allocator *iAlloc)
{
	sd = (sptrsd*)iAlloc->allocate(sizeof(sptrsd)); //Allocate shared data
	sd->rawptr = iPointer; //Set pointer
	sd->deallocator = iDeallocator
		sd->alloc = iAlloc; //Set allocator
	sd->references = 1; //Set references
}

//Copy constructor
template<class type> sptr<type>::sptr(sptr<type> &rhs)
{
#ifdef CTM_DEBUG_SLOW
	if(sd->deallocator == 0 && sd->rawptr != 0 && sd->references - 1 == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
	}
#endif

	//Deallocate data
	if(sd->references - 1 == 0)
	{
		//Deallocate data
		if(sd->rawptr != 0)
			sd->deallocator((void*)sd->rawptr);
		sd->alloc->deallocate((void*)sd); //Deallocate shared data
	}
	else
		--sd->references;

	//Copy new data
	sd = rhs.sd; //Copy shared data
	++sd->references; //Increment references
}

//Destructor
template<class type> sptr<type>::~sptr()
{
#ifdef CTM_DEBUG_SLOW
	if(rawptr != 0 && deallocator == 0 && sd->references - 1 == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
	}
#endif

	//Deallocate data
	if(sd->references - 1 == 0)
	{
		//Deallocate data
		if(sd->rawptr != 0)
			sd->deallocator((void*)sd->rawptr);
		sd->alloc->deallocate((void*)sd); //Deallocate shared data
	}
}

//Operator =
template<class type> sptr<type> &sptr<type>::operator=(sptr<type> &rhs)
{
	#ifdef CTM_DEBUG_SLOW
		if(sd->deallocator == 0 && sd->rawptr != 0 && sd->references - 1 == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	if(sd->references - 1 == 0)
	{
		//Deallocate data
		if(sd->rawptr != 0)
			sd->deallocator((void*)sd->rawptr);
		sd->alloc->deallocate((void*)sd); //Deallocate shared data
	}
	else
		--sd->references;

	//Copy new data
	sd = rhs.sd; //Copy shared data
	++sd->references; //Increment references

	return *this;
}


template<class type> sptr<type> &sptr<type>::operator=(type *nPointer)
{
	#ifdef CTM_DEBUG_SLOW
		if(sd->deallocator == 0 && sd->rawptr != 0 && sd->references - 1 == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	if(sd->rawptr != 0)
		sd->deallocator((void*))

		//Create new shared data
		allocator *temp = sd->alloc; //Copy allocator
	if(sd->references != 1)
	{
		temp->deallocate((void*)sd); //Deallocate shared data
		sd = (sptrsd*)temp->allocate(sizeof(sptrsd)); //Allocate shared data
	}

	sd->alloc = temp; //Set allocator
	sd->rawptr = nPointer; //Set pointer
	sd->references = 1; //Set references
}

//Deallocate
template<class type> void sptr<type>::deallocate()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Deallocation failed! Pointer has not been allocated!\n", true);
		}
	#endif

	#ifdef CTM_DEBUG_SLOW
		if(deallocator == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	--sd->references; //Decrement references
	if(references == 0)
	{
		if(sd->rawptr != 0)
			sd->deallocator((void*)sd->rawptr);
		sd->references = 1; //Reset references
		sd->rawptr = 0; //Reset pointer
		sd->deallocator = 0; //Reset deallocatpr
	}
}

//Set deallocator
template<class type> void sptr<type>::set_deallocator(void(*nDeallocator)(void *pointer))
{
	sd->deallocator = nDeallocator;
}

//Operator []
template<class type> type &sptr<type>::operator[](size_t index)
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return sd->rawptr[index];
}

//Operator *
template<class type> type &sptr<type>::operator*()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return *sd->rawptr;
}

//Operator ->
template<class type> type *sptr<type>::operator->()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return sd->rawptr;
}
////////////////////////////

}

#endif