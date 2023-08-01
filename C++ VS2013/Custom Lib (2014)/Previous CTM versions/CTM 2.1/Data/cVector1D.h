#ifndef VECTOR1D_H
#define VECTOR1D_H

#include "../Base/Base.h"
#include "cHeapAllocator.h"

namespace ctm
{

extern UINT32 DEFAULT_VECTOR_ALLOWANCE;

////////////////////
//One dimensional vector class
template<class type>
class vector1D
{
public:
	//System
		vector1D(heapallocator *nAlloc);
		vector1D(UINT32 iElements, heapallocator *nAlloc);
		vector1D(UINT32 iElements, type iInitial, heapallocator *nAlloc);
		vector1D(vector1D<type> &rhs);
		~vector1D();
		vector1D<type> &operator=(vector1D<type> &rhs);
	//Memory
		type& at(UINT32 index); //Returns an element
		type& operator[](UINT32 index); //Returns an element
		void resize(UINT32 nSize); //Resizes the vector
		void resize(UINT32 nSize, type nInitial); //Resizes the vector
		void clear(); //Clears the vector
		void insert(UINT32 index, type nElement); //Inserts an element (Elements shift up)
		void erase(UINT32 index); //Erases an element (Elements shift down)
		void push_back(type nElement); //Inserts an element at the end of the vector
		void pop_back(); //Erases an element at the end of the vector
		UINT32 get_size() { return size; } //Returns the vector size
		UINT32 get_capacity() { return capacity; } //Returns the vector capacity
		UINT32 get_allowance() { return allowance; } //Returns the vector allowance
		void set_allowance(UINT32 nAllowance) { allowance = nAllowance; } //Sets the vector allowance
private:
	type *data; //Data
	heapallocator *alloc; //Allocator
	UINT32 size; //Elements in use
	UINT32 capacity; //Elements allocated
	UINT32 allowance; //Elements allocated when vector is full or a number of elements have been deleted
};

//Constructor
template<class type> vector1D<type>::vector1D(heapallocator *nAlloc):
data(0),
alloc(DEFAULT_HEAPALLOCATOR),
size(0),
capacity(0),
allowance(10)
{
	//Allocate data
	if(alloc == 0)
		data = new type[capacity];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));
}

template<class type> vector1D<type>::vector1D(UINT32 iElements, heapallocator *nAlloc):
data(0),
alloc(DEFAULT_HEAPALLOCATOR),
size(iElements),
capacity(iElements),
allowance(10)
{
	//Allocate data
	if(alloc == 0)
		data = new type[capacity];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));
}

template<class type> vector1D<type>::vector1D(UINT32 iElements, type nInitial, heapallocator *nAlloc):
data(0),
alloc(DEFAULT_HEAPALLOCATOR),
size(iElements),
capacity(iElements),
allowance(10)
{
	//Allocate data
	if(alloc == 0)
		data = new type[capacity];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Initialize data
	for(UINT32 count = 0; count < capacity; ++count)
	{
		data[count] = nInitial;
	}
}

//Copy constructor
template<class type> vector1D<type>::vector1D(vector1D<type> &rhs):
data(0),
size(rhs.size),
capacity(rhs.capacity),
allowance(rhs.allowance)
{
	//Deallocate data
	if(data != 0) 
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = new type[capacity];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Copy elements
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs[count];
	}
}

//Destructor
template<class type> vector1D<type>::~vector1D()
{
	//Deallocate data
	if(alloc == 0)
		delete[] data; 
	else
		alloc->deallocate((void*)data);
}

//Operator = 
template<class type> vector1D<type> &vector1D<type>::operator=(vector1D<type> &rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;
	allowance = rhs.allowance;

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = new type[capacity];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Copy data
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs[count];
	}

	return *this;
}

//At
template<class type> type& vector1D<type>::at(UINT32 index)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(index >= size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to access element! Index is out of range!\n",true);
		assert(0);
	}
	#endif
	return data[index]; //Return element
}

//Operator []
template<class type> type& vector1D<type>::operator[](UINT32 index)
{
	return at(index);
}

//Resize
template<class type> void vector1D<type>::resize(UINT32 nSize)
{
	//Copy data
	type *copy = 0;
	if(alloc == 0)
		copy = new type[nSize];
	else
		copy = (type*)alloc->allocate(nSize*sizeof(type));
	for(unsigned int count = 0; count < nSize; ++count)
	{
		if(count < size)
			copy[count] = data[count];
	}

	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);
	data = copy; //Overwrite data with copy
	size = nSize; //Update size
	capacity = nSize; //Update capacity
}

template<class type> void vector1D<type>::resize(UINT32 nSize, type nInitial)
{
	//Copy data
	type *copy = 0;
	if(alloc == 0)
		copy = new type[nSize];
	else
		copy = (type*)alloc->allocate(nSize*sizeof(type));
	for(UINT32 count = 0; count < nSize; ++count)
	{
		if(count < size)
			copy[count] = data[count];
		else
			copy[count] = nInitial;
	}

	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);
	data = copy; //Overwrite data with copy
	size = nSize; //Update size
	capacity = nSize; //Update capacity
}

//Clear
template<class type> void vector1D<type>::clear()
{
	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = new type[0];
	else
		data = (type*)alloc->allocate(0);

	size = 0; //Update size
	capacity = 0; //Update capacity
}

//Insert
template<class type> void vector1D<type>::insert(UINT32 index, type nElement)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(index > size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to insert element! Index out of range!\n",true);
		assert(0);
	}
	#endif

	//Resize vector if needed
	if(size == capacity)
	{
		resize(capacity+allowance);
		size = capacity - allowance;
	}

	//Shift elements
	for(UINT32 count = size; count > index; --count)
	{
		data[count] = data[count-1];
	}
	data[index] = nElement; //Initialize new element
	++size; //Update size
}

//Erase
template<class type> void vector1D<type>::erase(UINT32 index)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(index >= size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to erase element! Index out of range!\n",true);
		assert(0);
	}
	#endif

	//Shift elements
	for(UINT32 count = index+1; count < size; ++count)
	{
		data[count-1] = data[count];
	}

	//Resize vector if needed
	if(size == capacity-allowance)
	{
		resize(capacity-allowance);
	}

	--size; //Update size
}

//Push back
template<class type> void vector1D<type>::push_back(type nElement)
{
	insert(size,nElement);
}

//Pop back
template<class type> void vector1D<type>::pop_back()
{
	erase(size-1);
}
////////////////////

}

#endif