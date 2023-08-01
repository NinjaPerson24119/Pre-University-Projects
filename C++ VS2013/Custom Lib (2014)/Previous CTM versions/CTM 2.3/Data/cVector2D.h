#ifndef CTM_VECTOR2D_H
#define CTM_VECTOR2D_H

#include "../Base/Base.h"
#include "cHeapAllocator.h"

namespace ctm
{

///////////////////////
//Two dimensional vector class
template<class type>
class vector2D
{
public:
	//System
		vector2D(heapallocator *iAlloc);
		vector2D(size_t iWidth, size_t iHeight, type &iInital, heapallocator *iAlloc);
		vector2D(vector2D &rhs);
		~vector2D();
		vector2D<type> &operator=(vector2D<type> &rhs);
	//Memory
		type &at(size_t x, size_t y); //Returns an element
		void resize(size_t nWidth, size_t nHeight); //Resizes the vector
		void resize(size_t nWidth, size_t nHeight, type &nInitial); //Resizes the vector
		void clear(); //Clears the vector
		void fill(type &nInitial); //Fills the vector with an element
		size_t get_width() { return width; } //Returns the width of the vector
		size_t get_height() { return height; } //Returns the height of the vector
private:
	type *data; //Data
	heapallocator *alloc; //Allocator
	size_t width; //Width
	size_t height; //Height
};

//Constructor
template<class type> vector2D<type>::vector2D(heapallocator *iAlloc):
data(0),
width(0),
height(0),
alloc(iAlloc)
{}

template<class type> vector2D<type>::vector2D(size_t iWidth, size_t iHeight, type &iInitial, heapallocator *iAlloc):
data(0),
width(iWidth),
height(iHeight),
alloc(iAlloc)
{
	//Allocate data
	if(alloc == 0)
		data = (type*)new char[sizeof(type)*width*height];
	else
		data = (type*)alloc->allocate(sizeof(type)*width*height);

	fill(iInitial); //Initialize elements
}

//Copy constructor
template<class type> vector2D<type>::vector2D(vector2D &rhs)
{
	//Deallocate data
	if(data != 0) 
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[sizeof(type)*rhs.width*rhs.height]
	else
		data = (type*)alloc->allocate(sizeof(type)*rhs.width*rhs.height);

	//Copy elements
	for(size_t x = 0; x < rhs.width; ++x)
	{
		for(size_t y = 0; y < rhs.height; ++y)
		{
			data[y*rhs.width+x] = rhs.data[y*rhs.width+x];
		}
	}

	//Update dimensions
	width = rhs.width;
	height = rhs.height;
}

//Destructor
template<class type> vector2D<type>::~vector2D()
{
	clear(); //Clear data
}

//Operator =
template<class type> vector2D<type> &vector2D<type>::operator=(vector2D<type> &rhs)
{
	//Deallocate data
	if(data != 0) 
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new char[sizeof(type)*rhs.width*rhs.height];
	else
		data = (type*)alloc->allocate(sizeof(type)*rhs.width*rhs.height);

	//Copy elements
	for(size_t x = 0; x < rhs.width; ++x)
	{
		for(size_t y = 0; y < rhs.height; ++y)
		{
			data[y*rhs.width+x] = rhs.data[y*rhs.width+x];
		}
	}

	//Update dimensions
	width = rhs.width;
	height = rhs.height;
	return *this;
}

//At
template<class type> type &vector2D<type>::at(size_t x, size_t y)
{
	#ifdef CTM_DEBUG_SLOW
	if((x >= width) || (y >= width))
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector2D - Failed to access element! Position is out of range!\n",true);
	}
	#endif
	return data[y*width+x];
}

//Resize
template<class type> void vector2D<type>::resize(size_t nWidth, size_t nHeight)
{
	//Allocate new data
	type *newdata = 0;
	if(alloc == 0)
		newdata = (type*)new char[sizeof(type)*nWidth*nHeight];
	else
		newdata = (type*)alloc->allocate(sizeof(type)*nWidth*nHeight);

	//Initialize new data
	for(size_t x = 0; x < width; ++x)
	{
		for(size_t y = 0; y < height; ++y)
		{
			newdata[y*nHeight+x] = data[y*nHeight+x];
		}
	}

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	data = newdata; //Reassign pointer to data

	//Update dimensions
	width = nWidth;
	height = nHeight;
}

template<class type> void vector2D<type>::resize(size_t nWidth, size_t nHeight, type &nInitial)
{
	//Allocate new data
	type *newdata = 0;
	if(alloc == 0)
		newdata = (type*)new char[sizeof(type)*nWidth*nHeight];
	else
		newdata = (type*)alloc->allocate(sizeof(type)*nWidth*nHeight);

	//Initialize new data
	for(size_t x = 0; x < nWidth; ++x)
	{
		for(size_t y = 0; y < nHeight; ++y)
		{
			if((x < width) && (y < height))
				newdata[y*nWidth+x] = at(x,y);
			else
				newdata[y*nWidth+x] = nInitial;
		}
	}

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);

	data = newdata; //Reassign pointer to data

	//Update dimensions
	width = nWidth;
	height = nHeight;
}

//Clear
template<class type> void vector2D<type>::clear()
{
	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (char*)data;
		else
			alloc->deallocate((void*)data);
	data = 0;

	//Update dimensions
	width = 0;
	height = 0;
}

//Fill
template<class type> void vector2D<type>::fill(type &iInitial)
{
	for(size_t x = 0; x < width; ++x)
	{
		for(size_t y = 0; y < height; ++y)
		{
			data[y*width+x] = iInitial;
		}
	}
}
///////////////////////

}

#endif