#ifndef CTM_FILE_H
#define CTM_FILE_H

#include "../Base/Base.h"
#include "../Data/cHeapAllocator.h"
#include "../Data/cString.h"

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

namespace ctm
{

typedef bool endianness;
typedef bool filestate;
extern const endianness DEF_FILE_ENDIANNESS_LITTLE;
extern const endianness DEF_FILE_ENDIANNESS_BIG;
extern const filestate DEF_FILE_STATE_READ;
extern const filestate DEF_FILE_STATE_WRITE;

inline void reverse_bytes(char *data, std::streamoff sizebytes); //Reverses the byte order of specified bytes

/////////////////////
//File class
class file
{
public:
	//System
		file();
		~file();
	//Management
		bool open(string nFilename, filestate nFileState, endianness nSystemEndianness, endianness nFileEndianness); //Opens a file
		bool close(); //Closes any opened files
		void flush(); //Flushes the file
	//Read/Write
		bool reposition(std::streamoff nPosition); //Moves to an arbitrary file location
		bool seek(std::streamoff nDistance); //Moves to different position in the file relative to the current position
		template<class type> bool read(type *nData, bool nHandleEndianness = true); //Reads data into a specified object
		bool read(char *nData, std::streamoff nSizeBytes, bool nHandleEndianness = true); //Reads data into a specified object
		template<class type> bool write(type *nData, bool nHandleEndianness = true); //Writes data of a specified object
		bool write(char *nData, std::streamoff nSizeBytes, bool nHandleEndianness = true); //Writes data of a specified object
	//Get/Set
		std::streamoff get_size(); //Returns the size of the file in bytes
		std::streamoff get_position(); //Returns the current position within the file
		bool get_systemendianness() { return systemendianness; } //Returns the system endianness (That was previously set)
		bool get_fileendianness() { return fileendianness; } //Returns the file endianness (That was previously set)
		void set_systemendianness(bool nSystemEndianness) { systemendianness = nSystemEndianness; } //Sets the system endianness
		void set_fileendianness(bool nFileEndianness) { fileendianness = nFileEndianness; } //Sets the file endianness
private:
	//Inaccessible
		file(file &rhs);
		file &operator=(file &rhs);
		std::streamoff size; //Size of file in bytes
		endianness systemendianness; //Endianness of system
		endianness fileendianness; //Endianness of file
		filestate state; //State of file (Read/Write)
		std::fstream stream; //File stream
};

//Read
template<class type> bool file::read(type *nData, bool nHandleEndianness)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not open!\n",true);
			return false;
		}
		else
			if(filestate != DEF_FILE_STATE_READ)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not opened for reading!\n",true);
				return false;
			}
	#endif

	//Read data
	stream.read((char*)nData,sizeof(type));

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((char*)nData,sizeof(type));
	return true;
}

//Write
template<class type> bool file::write(type *nData, bool nHandleEndianness)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to write to file! File is not open!\n",true);
			return false;
		}
		else
			if(filestate != DEF_FILE_STATE_WRITE)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not opened for writing!\n",true);
				return false;
			}
	#endif

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((char*)nData,sizeof(type));

	//Write data
	stream.write((char*)nData,sizeof(type));

	return true;
}
/////////////////////

}

#endif