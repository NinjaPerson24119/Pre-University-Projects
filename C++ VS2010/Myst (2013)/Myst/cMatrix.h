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
	matrix(int iWidth, int iHeight, type iInitial);
	void set_data(type value) { std::fill(data.begin(),data.end(),std::vector(height,value)); } //Sets all of matrix to a value
	void set_data(int x, int y, type value) { data.at(x).at(y) = value; } //Sets a value in the matrix
	void resize(int nWidth, int nHeight, type initial); //Resize
	type get_data(int x, int y) { return data.at(x).at(y); } //Gets a value in the matrix
	int get_width() { return width; } //Get dimensions
	int get_height() { return height; }
private:
	std::vector< std::vector<type> > data;
	int width;
	int height;
};

//Constructor
template <class type> matrix<type>::matrix(int iWidth, int iHeight, type iInitial):
width(iWidth),
height(iHeight),
data(iWidth,std::vector<type>(iHeight,iInitial)) {}

//Resize
template <class type> void matrix<type>::resize(int nWidth, int nHeight, type initial)
{
	//Resize matrix
	data.resize(nWidth);
	for(unsigned int count = 0; count < data.size(); count++)
	{
		data.at(count).resize(nHeight);
	}

	//Fill matrix
	for(int x = 0; x < nWidth; x++)
	{
		for(int y = 0; y < nHeight; y++)
		{
			data.at(x).at(y) = initial;
		}
	}

	//Register new dimensions
	width = nWidth;
	height = nHeight;
}
///////////////////

#endif