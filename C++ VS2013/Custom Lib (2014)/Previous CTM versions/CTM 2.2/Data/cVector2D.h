#ifndef VECTOR2D_H
#define VECTOR2D_H

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
		vector2D(UINT32 iWidth, UINT32 iHeight, type &iInital, heapallocator *iAlloc);
		vector2D(vector2D &rhs);
		~vector2D();
		vector2D<type> &operator=(vector2D<type> &rhs);
	//Memory
		type &at(UINT32 x, UINT32 y); //Returns an element
		void resize(UINT32 nWidth, UINT32 nHeight); //Resizes the vector
		void resize(UINT32 nWidth, UINT32 nHeight, type &nInitial); //Resizes the vector
		void clear(); //Clears the vector
		void fill(type &nInitial); //Fills the vector with an element
		UINT32 get_width() { return width; } //Returns the width of the vector
		UINT32 get_height() { return height; } //Returns the height of the vector
private:
	type *data; //Data
	UINT32 width; //Width
	UINT32 height; //Height
	heapallocator *alloc; //Allocator
};

//Constructor
template<class type> vector2D<type>::vector2D(heapallocator *iAlloc):
data(0),
width(0),
height(0),
alloc(iAlloc)
{}

template<class type> vector2D<type>::vector2D(UINT32 iWidth, UINT32 iHeight, type &iInitial, heapallocator *iAlloc):
data(0),
width(iWidth),
height(iHeight),
alloc(iAlloc)
{
	//Allocate data
	if(alloc == 0)
		data = (type*)new CHAR8[sizeof(type)*width*height];
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
			delete[] (CHAR8*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new CHAR8[sizeof(type)*rhs.width*rhs.height]
	else
		data = (type*)alloc->allocate(sizeof(type)*rhs.width*rhs.height);

	//Copy elements
	for(UINT32 x = 0; x < rhs.width; ++x)
	{
		for(UINT32 y = 0; y < rhs.height; ++y)
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
			delete[] (CHAR8*)data;
		else
			alloc->deallocate((void*)data);

	//Allocate data
	if(alloc == 0)
		data = (type*)new CHAR8[sizeof(type)*rhs.width*rhs.height];
	else
		data = (type*)alloc->allocate(sizeof(type)*rhs.width*rhs.height);

	//Copy elements
	for(UINT32 x = 0; x < rhs.width; ++x)
	{
		for(UINT32 y = 0; y < rhs.height; ++y)
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
template<class type> type &vector2D<type>::at(UINT32 x, UINT32 y)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if((x >= width) || (y >= width))
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cVector2D - Failed to access element! Position is out of range!\n",true);
		assert(0);
	}
	#endif
	return data[y*width+x];
}

//Resize
template<class type> void vector2D<type>::resize(UINT32 nWidth, UINT32 nHeight)
{
	//Allocate new data
	type *newdata = 0;
	if(alloc == 0)
		newdata = (type*)new CHAR8[sizeof(type)*nWidth*nHeight];
	else
		newdata = (type*)alloc->allocate(sizeof(type)*nWidth*nHeight);

	//Initialize new data
	for(UINT32 x = 0; x < width; ++x)
	{
		for(UINT32 y = 0; y < height; ++y)
		{
			newdata[y*nHeight+x] = data[y*nHeight+x];
		}
	}

	//Deallocate data
	if(data != 0)
		if(alloc == 0)
			delete[] (CHAR8*)data;
		else
			alloc->deallocate((void*)data);

	data = newdata; //Reassign pointer to data

	//Update dimensions
	width = nWidth;
	height = nHeight;
}

template<class type> void vector2D<type>::resize(UINT32 nWidth, UINT32 nHeight, type &nInitial)
{
	//Allocate new data
	type *newdata = 0;
	if(alloc == 0)
		newdata = (type*)new CHAR8[sizeof(type)*nWidth*nHeight];
	else
		newdata = (type*)alloc->allocate(sizeof(type)*nWidth*nHeight);

	//Initialize new data
	for(UINT32 x = 0; x < nWidth; ++x)
	{
		for(UINT32 y = 0; y < nHeight; ++y)
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
			delete[] (CHAR8*)data;
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
			delete[] (CHAR8*)data;
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
	for(UINT32 x = 0; x < width; ++x)
	{
		for(UINT32 y = 0; y < height; ++y)
		{
			data[y*width+x] = iInitial;
		}
	}
}
///////////////////////

}

#endif