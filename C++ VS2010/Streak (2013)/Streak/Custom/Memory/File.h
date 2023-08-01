#ifndef CTM_FILE_H
#define CTM_FILE_H

#include <fstream>

namespace ctm
{

//////
//File
class File
{
public:
	//File modes
		enum FileMode { READ, WRITE };
	//Base
		File();
		File(const char *FileName, FileMode Mode, bool MakeNewfile = false);
		~File();
	//State
		void Open(const char *FileName, FileMode Mode, bool MakeNewfile = false); //Opens the file
		void Close(); //Flushes and closes the file
	//IO
		void Write(char *Data, std::streamsize Length); //Writes binary data
		void Read(char *Data, std::streamsize Length); //Reads binary data
	//Position
		void Seek(std::streamoff Distance); //Moves the file IO location relative to the current one
		void Reposition(std::streampos Position); //Moves the file IO location relative to the file start
	//Get
		std::streampos Position(); //Returns the file IO position
		std::streampos Size(); //Returns the file size
		bool IsOpen(); //Checks if the file is open
		FileMode Mode(); //Returns the file mode
private:
	//Inaccessible
		File(File &Rhs);
		File &operator=(File &Rhs);
	std::fstream stream; //File stream
	std::streampos filesize; //The file size
	FileMode fmode; //File mode
};
//////

}

#endif