#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "../Base/Base.h"

///////////////////////
//Two dimensional vector class
template<class type>
class vector2D
{
public:
	//System
		vector2D();
		vector2D(UINT32 iWidth, UINT32 iHeight);
		vector2D(UINT32 iWidth, UINT32 iHeight, type iInital);
		vector2D(vector2D &rhs);
		~vector2D();
		vector2D<type> &operator=(vector2D<type> &rhs);
	//Memory
		type &at(UINT32 x, UINT32 y); //Returns an element
		void resize(UINT32 nWidth, UINT32 nHeight); //Resizes the vector
		void resize(UINT32 nWidth, UINT32 nHeight, type nInitial); //Resizes the vector
		void clear(); //Clears the vector
		void fill(type nInitial); //Fills the vector with an element
		UINT32 get_width() { return width; } //Returns the width of the vector
		UINT32 get_height() { return height; } //Returns the height of the vector
private:
	type *data; //Data
	UINT32 width; //Width
	UINT32 height; //Height
};

//Constructor
template<class type> vector2D<type>::vector2D():
data(0),
width(0),
height(0)
{}

template<class type> vector2D<type>::vector2D(UINT32 iWidth, UINT32 iHeight):
data(0),
width(iWidth),
height(iHeight)
{
	data = new type[width*height]; //Allocate data
}

template<class type> vector2D<type>::vector2D(UINT32 iWidth, UINT32 iHeight, type iInitial):
data(0),
width(iWidth),
height(iHeight)
{
	data = new type[width*height]; //Allocate data
	fill(iInitial); //Initialize elements
}

//Copy constructor
template<class type> vector2D<type>::vector2D(vector2D &rhs)
{
	if(data != 0) delete data; //Deallocate data
	data = new type[rhs.width*rhs.height]; //Allocate data

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
	if(data != 0) delete data; //Deallocate data
	data = new type[rhs.width*rhs.height]; //Allocate data

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
		assert(!((x >= width) || (y >= width))); //Error: cVector2D - Failed to access element! Position is out of range!
	#endif
	return data[y*width+x];
}

//Resize
template<class type> void vector2D<type>::resize(UINT32 nWidth, UINT32 nHeight)
{
	type *newdata = new type[nWidth*nHeight]; //Allocate new data

	//Initialize new data
	for(UINT32 x = 0; x < width; ++x)
	{
		for(UINT32 y = 0; y < height; ++y)
		{
			newdata[y*nHeight+x] = data[y*nHeight+x];
		}
	}

	if(data != 0) delete[] data; //Deallocate data
	data = newdata; //Reassign pointer to data

	//Update dimensions
	width = nWidth;
	height = nHeight;
}

template<class type> void vector2D<type>::resize(UINT32 nWidth, UINT32 nHeight, type nInitial)
{
	type *newdata = new type[nHeight*nWidth]; //Allocate new data

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

	if(data != 0) delete data; //Deallocate data
	data = newdata; //Reassign pointer to data

	//Update dimensions
	width = nWidth;
	height = nHeight;
}

//Clear
template<class type> void vector2D<type>::clear()
{
	if(data != 0) delete data; //Deallocate data
	data = 0;

	//Update dimensions
	width = 0;
	height = 0;
}

//Fill
template<class type> void vector2D<type>::fill(type iInitial)
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

#endif