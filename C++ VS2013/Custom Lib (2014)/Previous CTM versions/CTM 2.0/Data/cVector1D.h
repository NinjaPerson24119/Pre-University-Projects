#ifndef VECTOR1D_H
#define VECTOR1D_H

#include "../Base/Base.h"

extern UINT32 DEFAULT_VECTOR_ALLOWANCE;

////////////////////
//One dimensional vector class
template<class type>
class vector1D
{
public:
	//System
		vector1D();
		vector1D(UINT32 iElements);
		vector1D(UINT32 iElements, type iInitial);
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
	UINT32 size; //Elements in use
	UINT32 capacity; //Elements allocated
	UINT32 allowance; //Elements allocated when vector is full or a number of elements have been deleted
};

//Constructor
template<class type> vector1D<type>::vector1D():
data(0),
size(0),
capacity(0),
allowance(10)
{
	data = new type[capacity]; //Allocate data
}

template<class type> vector1D<type>::vector1D(UINT32 iElements):
data(0),
size(iElements),
capacity(iElements),
allowance(10)
{
	data = new type[capacity]; //Allocate data
}

template<class type> vector1D<type>::vector1D(UINT32 iElements, type nInitial):
data(0),
size(iElements),
capacity(iElements),
allowance(10)
{
	data = new type[capacity]; //Allocate data

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
	if(data != 0) delete[] data; //Deallocate data
	data = new type[capacity]; //Allocate data

	//Copy elements
	for(UINT32 count = 0; count < size; ++count)
	{
		data[count] = rhs[count];
	}
}

//Destructor
template<class type> vector1D<type>::~vector1D()
{
	delete[] data; //Deallocate data
}

//Operator = 
template<class type> vector1D<type> &vector1D<type>::operator=(vector1D<type> &rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;
	allowance = rhs.allowance;

	if(data != 0) delete[] data; //Deallocate data
	data = new type[capacity]; //Allocate data

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
		assert(!(index >= size)); //Error: cVector1D - Failed to access element! Index is out of range!
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
	type *copy = new type[nSize];
	for(unsigned int count = 0; count < nSize; ++count)
	{
		if(count < size)
			copy[count] = data[count];
	}

	delete[] data; //Deallocate data
	data = copy; //Overwrite data with copy
	size = nSize; //Update size
	capacity = nSize; //Update capacity
}

template<class type> void vector1D<type>::resize(UINT32 nSize, type nInitial)
{
	//Copy data
	type *copy = new type[nSize];
	for(UINT32 count = 0; count < nSize; ++count)
	{
		if(count < size)
			copy[count] = data[count];
		else
			copy[count] = nInitial;
	}

	delete[] data; //Deallocate data
	data = copy; //Overwrite data with copy
	size = nSize; //Update size
	capacity = nSize; //Update capacity
}

//Clear
template<class type> void vector1D<type>::clear()
{
	delete[] data; //Deallocate data
	data = new type[0]; //Allocate data
	size = 0; //Update size
	capacity = 0; //Update capacity
}

//Insert
template<class type> void vector1D<type>::insert(UINT32 index, type nElement)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(index > size)); //Error: cVector1D - Failed to insert element! Index out of range!
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
		assert(!(index >= size)); //Error: cVector1D - Failed to erase element! Index out of range!
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

#endif