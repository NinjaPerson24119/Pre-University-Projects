#include "cSharedPointer.h"

namespace ctm
{

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

template<class type> sptr<type>::sptr(type *iPointer, void (*iDeallocator)(void *pointer), allocator *iAlloc)
{
	sd = (sptrsd*)iAlloc->allocate(sizeof(sptrsd)); //Allocate shared data
	sd->rawptr = iPointer; //Set pointer
	sd->deallocator = iDeallocator
	sd->alloc = iAlloc; //Set allocator
	sd->references = 1; //Set references
}

//Copy constructor
template<class type> sptr<type>::sptr(sptr &rhs)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(sd->deallocator == 0 && sd->rawptr != 0 && sd->references-1 == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n",true);
		}
	#endif

	//Deallocate data
	if(sd->references-1 == 0)
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
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(rawptr != 0 && deallocator == 0 && sd->references-1 == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to deallocate data! Deallocator has not been specified!\n",true);
		}
	#endif

	//Deallocate data
	if(sd->references-1 == 0)
	{
		//Deallocate data
		if(sd->rawptr != 0)
			sd->deallocator((void*)sd->rawptr);
		sd->alloc->deallocate((void*)sd); //Deallocate shared data
	}
}

//Operator =
template<class type> sptr &sprt<type>::operator=(sptr &rhs)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
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

template<class type> sptr &sptr<type>::operator=(type *nPointer)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
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
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Deallocation failed! Pointer has not been allocated!\n", true);
		}
	#endif

	#ifdef CUSTOMLIB_DEBUG_SLOW
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
template<class type> void sptr<type>::set_deallocator(void (*nDeallocator)(void *pointer))
{
	sd->deallocator = nDeallocator;
}

//Operator []
template<class type> type &sptr<type>::operator[](UINT32 index)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n",true);
		}
	#endif

	return sd->rawptr[index];
}

//Operator *
template<class type> type &sptr<type>::operator*()
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n",true);
		}
	#endif

	return *sd->rawptr;
}

//Operator ->
template<class type> type *sptr<type>::operator->()
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cSharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n",true);
		}
	#endif

	return sd->rawptr;
}

}