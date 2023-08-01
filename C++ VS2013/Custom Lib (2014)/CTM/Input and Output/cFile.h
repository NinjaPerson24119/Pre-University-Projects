#ifndef CTM_FILE_H
#define CTM_FILE_H

#include "../Base/Base.h"
#include "../Data/cRadAllocator.h"
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

inline void reverse_bytes(char *data, size_t sizebytes); //Reverses the byte order of specified bytes

/////////////////////
//File class
class file
{
public:
	//System
		file(radallocator *iAlloc = DEFAULT_RADALLOCATOR);
		file(string &nFileName, filestate nFileState, endianness nSystemEndianness, endianness nFileEndianness, radallocator *iAlloc = DEFAULT_RADALLOCATOR);
		~file();
	//Management
		bool open(string &nFileName, filestate nFileState, endianness nSystemEndianness, endianness nFileEndianness); //Opens a file
		bool close(); //Closes any opened files
		void flush(); //Flushes the file
	//Read/Write
		bool reposition(size_t nPosition); //Moves to an arbitrary file location
		bool seek(size_t nDistance); //Moves to different position in the file relative to the current position
		template<class type> bool read(type *nData, bool nHandleEndianness = true); //Reads data into a specified object
		bool read(char *nData, size_t nSizeBytes, bool nHandleEndianness = true); //Reads data into a buffer
		template<class type> bool write(type *nData, bool nHandleEndianness = true); //Writes data from a buffer
		bool write(char *nData, size_t nSizeBytes, bool nHandleEndianness = true); //Writes data of a specified object
		bool write(string &nData, bool nHandleEndianness = true); //Writes the contents of a string
	//Get/Set
		size_t get_size(); //Returns the size of the file in bytes
		size_t get_position(); //Returns the current position within the file
		bool get_systemendianness() { return systemendianness; } //Returns the system endianness (That was previously set)
		bool get_fileendianness() { return fileendianness; } //Returns the file endianness (That was previously set)
		void set_systemendianness(bool nSystemEndianness) { systemendianness = nSystemEndianness; } //Sets the system endianness
		void set_fileendianness(bool nFileEndianness) { fileendianness = nFileEndianness; } //Sets the file endianness
private:
	//Inaccessible
		file(file &rhs);
		file &operator=(file &rhs);
	std::fstream stream; //File stream
	size_t size; //Size of file in bytes
	radallocator *alloc; //Allocator
	endianness systemendianness; //Endianness of system
	endianness fileendianness; //Endianness of file
	filestate state; //State of file (Read/Write)
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
		{
			//Copy data to new buffer
			char *nBuffer = (char*)alloc->allocate(sizeof(type));
			memcpy(nBuffer,nData,sizeof(type));

			//Reverse byte order
			reverse_bytes((char*)nBuffer,sizeof(type));

			//Write data
			stream.write((char*)nBuffer, sizeof(type));

			//Delete buffer
			alloc->deallocate((void*)nBuffer);

			return true;
		}

	//Write data
	stream.write((char*)nData, sizeof(type));

	return true;
}
/////////////////////

}

#endif