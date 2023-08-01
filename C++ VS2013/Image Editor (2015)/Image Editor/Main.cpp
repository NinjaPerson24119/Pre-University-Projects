#include "File.h"
#include "Image.h"
#include "StringConversions.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

//Predefine functions
void Clean(ctm::Image &Target, unsigned int R, unsigned int G, unsigned int B, unsigned int Tolerance);

int main(int argc, char **argv)
{
	try
	{
		if(argv[1] == "help")
		{
			std::cout << "Commands: \n";
			std::cout << "Clean - Removes pixels outside of a given range\n";
			std::cout << "\t -filename -clean -red -green -blue -tolerance (RGBT range from 0 to 100)\n";
		}

		//Load Image
		ctm::Image image;
		image.LoadBitmap("dummy.bmp");

		//Clean Image
		if(argv[2] == "clean")
		{
			if(argc != 6)
				throw std::runtime_error("Main - Failed to clean image! Invalid parameters!");

			Clean(image, ctm::StringToUnsignedInteger(argv[3], strlen(argv[3])), ctm::StringToUnsignedInteger(argv[4], strlen(argv[4])), ctm::StringToUnsignedInteger(argv[5], strlen(argv[5])), ctm::StringToUnsignedInteger(argv[6], strlen(argv[6])));
		}

	}
	catch(std::runtime_error Error)
	{
		std::cout << Error.what();
		system("pause");
		return -1;
	}

	system("pause");
	return 0;
}

//Clean
void Clean(ctm::Image &Target, unsigned int R, unsigned int G, unsigned int B, unsigned int Tolerance)
{

}