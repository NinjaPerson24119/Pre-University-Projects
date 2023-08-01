#ifndef MATRIX_H
#define MATRIX_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

///////////////////
//Matrix class
template <class type> class matrix
{
public:
	matrix(type iInitial, int iWidth, int iHeight, int iDepth);
	void set_data(type value) { std::fill(data.begin(),data.end(),std::vector(height,value)); } //Sets all of matrix to a value
	void set_data(type value, int x, int y, int z = 0) { data.at(x).at(y).at(z) = value; } //Sets a value in the matrix
	void resize(type initial, int nWidth, int nHeight, int nDepth); //Resize
	type get_data(int x, int y, int z = 0) { return data.at(x).at(y).at(z); } //Gets a value in the matrix
	int get_width() { return width; } //Get dimensions
	int get_height() { return height; }
	int get_depth() { return depth; }
private:
	std::vector< std::vector< std::vector<type> > > data;
	int width;
	int height;
	int depth;
};

//Constructor
template <class type> matrix<type>::matrix(type iInitial, int iWidth, int iHeight, int iDepth = 1):
width(iWidth),
height(iHeight),
depth(iDepth),
data(iWidth,std::vector< std::vector<type> >(iHeight,std::vector<type>(iDepth,iInitial))) {}

//Resize
template <class type> void matrix<type>::resize(type initial, int nWidth, int nHeight, int nDepth = 1)
{
	//Resize matrix
	data.resize(nWidth);
	for(unsigned int y = 0; y < data.size(); y++)
	{
		data.at(y).resize(nHeight);
		for(unsigned int z = 0; z < data.at(0).size(); z++)
		{
			data.at(y).at(z).resize(nDepth);
		}
	}

	//Fill matrix
	for(int x = 0; x < nWidth; x++)
	{
		for(int y = 0; y < nHeight; y++)
		{
			for(int z = 0; z < nDepth; z++)
			{
				data.at(x).at(y).at(z) = initial;
			}
		}
	}

	//Register new dimensions
	width = nWidth;
	height = nHeight;
	depth = nDepth;
}
///////////////////

#endif