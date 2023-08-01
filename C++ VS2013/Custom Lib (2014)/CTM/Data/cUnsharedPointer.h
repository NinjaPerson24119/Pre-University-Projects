#ifndef CTM_UNSHAREDPOINTER_H
#define CTM_UNSHAREDPOINTER_H

#include "../Base/Base.h"

namespace ctm
{

/////////////////////////
//Unshared pointer class
template<class type> class uptr
{
public:
	//System
		uptr(); //Constructor
		uptr(type *iPointer);
		uptr(type *iPointer, void (*iDeallocator)(void *pointer));
		uptr(uptr<type> &rhs); //Copy constructor
		~uptr(); //Destructor
		uptr<type> &operator=(uptr<type> &rhs); //Operator =
		uptr<type> &operator=(type *nPointer);
	//Memory
		void deallocate(); //Deallocates and clears data
		void set_deallocator(void(*nDeallocator)(void *pointer)); //Set function used to deallocate data
		type &operator[](size_t index); //Operator []
		type &operator*(); //Operator *
		type *operator->(); //Operator ->
private:
	type *rawptr; //Raw pointer
	void (*deallocator)(void *pointer); //Pointer to deleter
};

//Constructor
template<class type> uptr<type>::uptr() :
rawptr(0),
deleter(0)
{}

template<class type> uptr<type>::uptr(type *iPointer) :
rawptr(iPointer),
deleter(0)
{}

template<class type> uptr<type>::uptr(type *iPointer, void(*iDeallocator)(void *pointer)) :
rawptr(iPointer),
deleter(iDeleter)
{}

//Copy constructor
template<class type> uptr<type>::uptr(uptr<type> &rhs)
{
	#ifdef CTM_DEBUG_SLOW
		if(deallocator == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to deallocate data! Deallocator has not been specified\n", true);
		}
	#endif

	//Deallocate data
	if(rawptr != 0)
		deallocator((void*)rawptr);

	//Copy data
	rawptr == rhs.rawptr;
	deleter == rhs.deallocator;

	//Clear other uptr
	rhs.rawptr = 0;
	rhs.deallocator = 0;
}

//Destructor
template<class type> uptr<type>::~uptr()
{
	#ifdef CTM_DEBUG_SLOW
		if(deleter == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	if(rawptr != 0)
		deallocator((void*)rawptr);
}

//Operator = 
template<class type> uptr<type> &uptr<type>::operator=(uptr<type> &rhs)
{
	#ifdef CTM_DEBUG_SLOW
		if(deallocator == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	if(rawptr != 0)
		deallocator((void*)rawptr);

	//Copy data
	rawptr = rhs.rawptr;
	deallocator = rhs.deallocator;

	//Clear other uptr
	rhs.rawptr = 0;
	rhs.deallocator = 0;

	return *this;
}

template<class type> uptr<type> &uptr<type>::operator=(type *nPointer)
{
	#ifdef CTM_DEBUG_SLOW
		if(deallocator == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	if(rawptr != 0)
		deallocator(rawptr);

	//Clear deallocator
	deallocator = 0;

	//Copy pointer
	rawptr = nPointer;

	return *this;
}

//Deallocate
template<class type> void uptr<type>::deallocate()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Deallocation failed! Pointer has not been allocated!\n", true);
		}
	#endif

	#ifdef CTM_DEBUG_SLOW
		if(deallocator == 0 && rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to deallocate data! Deallocator has not been specified!\n", true);
		}
	#endif

	//Deallocate data
	deallocator((void*)rawptr);

	//Clear deallocator
	deallocator = 0;
}

//Set deleter
template<class type> void uptr<type>::set_deallocator(void(*nDeallocator)(void *pointer))
{
	deallocator = nDeallocator;
}

//Operator []
template<class type> type &uptr<type>::operator[](size_t index)
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return rawptr[index];
}

//Operator *
template<class type> type &uptr<type>::operator*()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return *rawptr;
}

//Operator ->
template<class type> type *uptr<type>::operator->()
{
	#ifdef CTM_DEBUG_SLOW
		if(rawptr != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cUnsharedPointer - Failed to dereference pointer! Pointer has not been allocated!\n", true);
		}
	#endif

	return rawptr;
}
/////////////////////////

}

#endif