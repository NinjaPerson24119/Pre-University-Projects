#ifndef UNSHAREDPOINTER_H
#define UNSHAREDPOINTER_H

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
		uptr(uptr &rhs); //Copy constructor
		~uptr(); //Destructor
		uptr &operator=(uptr &rhs); //Operator =
		uptr &operator=(type *nPointer);
	//Memory
		void deallocate(); //Deallocates and clears data
		void set_deallocator(void(*nDeallocator)(void *pointer)) //Set function used to deallocate data
		type &operator[](UINT32 index); //Operator []
		type &operator*(); //Operator *
		type *operator->(); //Operator ->
private:
	type *rawptr; //Raw pointer
	void (*deallocator)(void *pointer); //Pointer to deleter
};
/////////////////////////

}

#endif