#ifndef CTM_IMAGE_H
#define CTM_IMAGE_H

#include "File.h"

namespace ctm
{

//////
//Image
class Image
{
public:
	//Format
		enum Format { RGB, RGBA };
	//Base
		Image();
		Image(Image &Rhs);
		~Image();
	//Bitmap
		void LoadBitmap(const char *FileName);
		void SaveBitmap(const char *FileName);
	//Set
		void SetFormat(Format F);
	//Data
		unsigned int width, height, pixelsize, res;
		char *data;
		Format format;
};
//////

//////
//Bitmap File Header
class BitmapFileHeader
{
public:
	char signature[2];
	unsigned int filesize;
	char reserved[4];
	unsigned int imageoffset;
};
//////

//////
//Bitmap Info Header
class BitmapInfoHeader
{
public:
	unsigned int headersize;
	int width, height;
	unsigned short colorplanes;
	unsigned short bitsperpixel;
	unsigned int compression;
	unsigned int imagesize;
	int horizontalres, verticalres;
	unsigned int colorsinpalette;
	unsigned int importantcolors;
};
//////

}

#endif