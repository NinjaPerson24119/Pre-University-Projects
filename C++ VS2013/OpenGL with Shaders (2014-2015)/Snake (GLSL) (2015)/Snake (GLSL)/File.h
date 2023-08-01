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
		File(const char *Filename, FileMode Mode, bool Makenewfile = false);
		~File();
	//State
		void open(const char *Filename, FileMode Mode, bool Makenewfile = false); //Opens the file
		void close(); //Flushes and closes the file
	//IO
		void write(char *Data, std::streamsize Length); //Writes binary data
		void read(char *Data, std::streamsize Length); //Reads binary data
	//Position
		void seek(std::streamoff Distance); //Moves the file IO location relative to the current one
		void reposition(std::streampos Position); //Moves the file IO location relative to the file start
	//Get
		std::streampos position(); //Returns the file IO position
		std::streampos size(); //Returns the file size
		bool isopen(); //Checks if the file is open
		FileMode mode(); //Returns the file mode
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