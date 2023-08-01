#ifndef CTM_VECTOR1D_H
#define CTM_VECTOR1D_H

#include "../Base/Base.h"
#include "cHeapAllocator.h"

namespace ctm
{

extern size_t DEFAULT_VECTOR1D_ALLOWANCE;
extern float DEFAULT_VECTOR1D_RELATIVEGROWTH;

////////////////////
//One dimensional vector class
template<class type>
class vector1D
{
public:
	//System
		vector1D(heapallocator *iAlloc);
		vector1D(size_t iAllowance, heapallocator *iAlloc);
		vector1D(float iRelativeGrowth, heapallocator *iAlloc);
		vector1D(size_t iElements, type &iInitial, heapallocator *iAlloc);
		vector1D(size_t iElements, type &iInitial, size_t iAllowance, heapallocator *iAlloc);
		vector1D(size_t iElements, type &iInitial, float iRelativeGrowth, heapallocator *iAlloc);
		vector1D(vector1D<type> &rhs);
		~vector1D();
		vector1D<type> &operator=(vector1D<type> &rhs);
	//Memory
		type& at(size_t index); //Returns an element
		type& operator[](size_t index); //Returns an element
		void resize(size_t nSize); //Resizes the vector
		void resize(size_t nSize, const type &nInitial); //Resizes the vector
		void clear(); //Clears the vector
		void fill(type &nInitial); //Fills the vector with an element
		void insert(size_t index, type &nElement); //Inserts an element (Elements shift up)
		void erase(size_t index); //Erases an element (Elements shift down)
		void push_back(type &nElement); //Inserts an element at the end of the vector
		void pop_back(); //Erases an element at the end of the vector
		size_t get_size() { return size; } //Returns the vector size
		size_t get_capacity() { return capacity; } //Returns the vector capacity
		size_t get_allowance() { return allowance; } //Returns the vector allowance
		float get_relativegrowth() { return relativegrowth; } //Returns the vector relative growth
private:
	type *data; //Data
	heapallocator *alloc; //Allocator
	size_t size; //Elements in use
	size_t capacity; //Elements allocated
	size_t allowance; //Elements allocated when vector is full or a number of elements have been deleted
	float relativegrowth; //When set to 0 allowance is used for growth but this can be set to grow the vector by a percent of its size
};

//Constructor
template<class type> vector1D<type>::vector1D(heapallocator *nAlloc):
data(0),
alloc(nAlloc),
size(0),
capacity(0),
allowance(DEFAULT_VECTOR1D_ALLOWANCE),
relativegrowth(DEFAULT_VECTOR1D_RELATIVEGROWTH)
{}

template<class type> vector1D<type>::vector1D(size_t iAllowance, heapallocator *iAlloc):
{
	#ifdef CTM_DEBUG_FAST
		if(allowance == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cVector1D - Vector allowance must be atleast 1!\n",true);
		}
	#endif
}

template<class type> vector1D<type>::vector1D(float iRelativeGrowth, heapallocator *iAlloc):
data(0),
alloc(nAlloc),
size(0),
capacity(0),
allowance(DEFAULT_VECTOR1D_ALLOWANCE),
relativegrowth(iRelativeGrowth)
{
	#ifdef CTM_DEBUG_FAST
		if(relativegrowth != 0)
		{
			if(relativegrowth < 1)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cVector1D - Vector relative growth must be atleast 1 with the exception of 0!\n",true);
			}
		}
	#endif
}

template<class type> vector1D<type>::vector1D(size_t iElements, type &nInitial, heapallocator *nAlloc):
data(0),
alloc(nAlloc),
size(iElements),
capacity(iElements),
allowance(DEFAULT_VECTOR1D_ALLOWANCE),
relativegrowth(DEFAULT_VECTOR1D_RELATIVEGROWTH)
{
	//Allocate data
	if(alloc == 0)
		data = (type*)new char[capacity*sizeof(type)];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Initialize data
	for(size_t count = 0; count < capacity; ++count)
	{
		data[count] = nInitial;
	}
}

template<class type> vector1D<type>::vector1D(size_t iElements, type &nInitial, size_t iAllowance, heapallocator *nAlloc) :
data(0),
alloc(nAlloc),
size(iElements),
capacity(iElements),
allowance(iAllowance),
relativegrowth(0)
{
	#ifdef CTM_DEBUG_FAST
		if(allowance == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cVector1D - Vector allowance must be atleast 1!\n", true);
		}
	#endif

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[capacity*sizeof(type)];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Initialize data
	for(size_t count = 0; count < capacity; ++count)
	{
		data[count] = nInitial;
	}
}

template<class type> vector1D<type>::vector1D(size_t iElements, type &nInitial, float iRelativeGrowth, heapallocator *nAlloc) :
data(0),
alloc(nAlloc),
size(iElements),
capacity(iElements),
allowance(DEFAULT_VECTOR1D_ALLOWANCE),
relativegrowth(iRelativeGrowth)
{
	#ifdef CTM_DEBUG_FAST
		if(relativegrowth != 0)
		{
			if(relativegrowth < 1)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cVector1D - Vector relative growth must be atleast 1 with the exception of 0!\n", true);
			}
		}
	#endif

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[capacity*sizeof(type)];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Initialize data
	for(size_t count = 0; count < capacity; ++count)
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
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[capacity*sizeof(type)];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Copy elements
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}
}

//Destructor
template<class type> vector1D<type>::~vector1D()
{
	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data; 
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
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[capacity*sizeof(type)];
	else
		data = (type*)alloc->allocate(capacity*sizeof(type));

	//Copy data
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = rhs.data[count];
	}

	return *this;
}

//At
template<class type> type& vector1D<type>::at(size_t index)
{
	#ifdef CTM_DEBUG_SLOW
	if(index >= size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to access element! Index is out of range!\n",true);
	}
	#endif
	return data[index]; //Return element
}

//Operator []
template<class type> type& vector1D<type>::operator[](size_t index)
{
	return at(index);
}

//Resize
template<class type> void vector1D<type>::resize(size_t nCapacity)
{
	//Copy data
	type *copy = 0;
	if(alloc == 0)
		copy = (type*)new char[nCapacity*sizeof(type)];
	else
		copy = (type*)alloc->allocate(nCapacity*sizeof(type));

	for(size_t count = 0; count < nCapacity; ++count)
	{
		if(count < size)
			copy[count] = data[count];
	}

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	data = copy; //Overwrite data with copy
	capacity = nCapacity; //Update capacity
}

template<class type> void vector1D<type>::resize(size_t nCapacity, const type &nInitial)
{
	//Copy data
	type *copy = 0;
	if(alloc == 0)
		copy = (type*)new char[nCapacity*sizeof(type)];
	else
		copy = (type*)alloc->allocate(nCapacity*sizeof(type));

	for(size_t count = 0; count < nCapacity; ++count)
	{
		if(count < size)
			copy[count] = data[count];
		else
			copy[count] = nInitial;
	}

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	data = copy; //Overwrite data with copy
	capacity = nCapacity; //Update capacity
}

//Clear
template<class type> void vector1D<type>::clear()
{
	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);
	data = 0;

	size = 0; //Update size
	capacity = 0; //Update capacity
}

//Fill
template<class type> void vector1D<type>::fill(type &nInitial)
{
	for(size_t count = 0; count < size; ++count)
	{
		data[count] = nInitial;
	}
}

//Insert
template<class type> void vector1D<type>::insert(size_t index, type &nElement)
{
	#ifdef CTM_DEBUG_SLOW
	if(index > size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to insert element! Index out of range!\n",true);
	}
	#endif

	//Resize vector if needed
	if(size == capacity)
	{
		//Resize by allowance or relative growth
		if(relativegrowth == 0)
			resize(capacity+allowance);
		else
			resize((size_t)(capacity*relativegrowth));

		++size; //Update size
	}

	//Shift elements
	for(size_t count = size; count > index; --count)
	{
		data[count] = data[count-1];
	}
	data[index] = nElement; //Initialize new element
	++size; //Update size
}

//Erase
template<class type> void vector1D<type>::erase(size_t index)
{
	#ifdef CTM_DEBUG_SLOW
	if(index >= size)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector1D - Failed to erase element! Index out of range!\n",true);
	}
	#endif

	//Shift elements
	for(size_t count = index+1; count < size; ++count)
	{
		data[count-1] = data[count];
	}

	//Resize vector if needed
	if(relativegrowth == 0)
	{
		if(size == capacity-allowance)
		{
			resize(capacity-allowance);
		}
	}
	else
	{
		if(size == capacity/relativegrowth)
		{
			resize(capacity/resizefactor);
		}
	}

	--size; //Update size
}

//Push back
template<class type> void vector1D<type>::push_back(type &nElement)
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