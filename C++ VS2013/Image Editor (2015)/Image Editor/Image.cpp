#include "Image.h"

#include <iostream>

namespace ctm
{

//Constructor
Image::Image():
width(0),
height(0),
data(nullptr),
format(RGB),
res(0)
{}

//Copy Constructor
Image::Image(Image &Rhs)
{
	if(Rhs.data != nullptr)
	{
		if(data != nullptr)
			delete[] data;

		data = new char[Rhs.width * Rhs.height * Rhs.pixelsize];
		memcpy(data, Rhs.data, width * height);

		width = Rhs.width;
		height = Rhs.height;
		format = Rhs.format;
		res = Rhs.res;
	}
	else
		throw std::runtime_error("Image - Failed to copy image! Image has not been loaded!\n");
}

//Destructor
Image::~Image()
{
	if(data != nullptr)
		delete[] data;
}

//Load Bitmap
void Image::LoadBitmap(const char *FileName)
{
	//Open bitmap
	ctm::File file(FileName, ctm::File::FileMode::READ);

	//Read file header
	BitmapFileHeader fileheader;
	file.Read((char*)&fileheader, sizeof(BitmapFileHeader));

	//Check that file is a bitmap
	std::cout << fileheader.signature << "\n";
	if((short)fileheader.signature != (short)"BM")
		throw std::runtime_error("Image - Failed to load bitmap! File could not be recognized!\n");

	//Check info header type
	unsigned int infoheadersize = 0;
	file.Read((char*)&infoheadersize, sizeof(unsigned int));
	
	if(infoheadersize != sizeof(BitmapInfoHeader))
		throw std::runtime_error("Image - Failed to load bitmap! Unrecognized DIB header!\n");	

	//Read info header
	BitmapInfoHeader infoheader;
	file.Read((char*)&infoheader, sizeof(BitmapInfoHeader));

	//Check compression
	if(infoheader.compression != 0)
		throw std::runtime_error("Image - Failed to load bitmap! Unrecognized compression format!\n");

	//Calculate row size and pixel array size
	unsigned int rowsize = ((infoheader.bitsperpixel * infoheader.width + 31) / 32) * 4;
	unsigned int pixelarraysize = rowsize * (unsigned int)infoheader.height;

	//Allocate pixel memory
	data = new char[infoheader.bitsperpixel * infoheader.width * (unsigned int)infoheader.height];
	char *raw = new char[pixelarraysize];

	//Read pixels
	file.Reposition(fileheader.imageoffset);
	file.Read(raw, pixelarraysize);
	file.Close();

	//Convert pixels
	if(infoheader.height < 0) //Bottom up
	{
		for(unsigned int count = (unsigned int)infoheader.height - 1; count != 0; --count)
		{
			memcpy(&data[infoheader.width * count], &raw[rowsize * count], infoheader.width);
		}
	}
	else //Top down
	{
		for(unsigned int count = 0; count < (unsigned int)infoheader.height; ++count)
		{
			memcpy(&data[infoheader.width *count], &raw[rowsize * count], infoheader.width);
		}
	}

	//Deallocate raw pixels
	delete[] raw;

	//Set image properties
	width = infoheader.width;
	height = (unsigned int)infoheader.height;
	res = infoheader.horizontalres;
	format = RGB;
	pixelsize = infoheader.bitsperpixel / 8;
}

//Save Bitmap
void Image::SaveBitmap(const char *FileName)
{

}

//Set Format
void Image::SetFormat(Format F)
{

}

}