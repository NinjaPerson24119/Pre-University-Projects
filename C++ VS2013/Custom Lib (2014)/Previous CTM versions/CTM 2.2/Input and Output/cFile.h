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

extern const BOOL8 DEF_FILE_ENDIANNESS_LITTLE;
extern const BOOL8 DEF_FILE_ENDIANNESS_BIG;
extern const BOOL8 DEF_FILE_STATE_READ;
extern const BOOL8 DEF_FILE_STATE_WRITE;

/////////////////////
//File class
class file
{
public:
	//System
		file();
		~file();
	//Management
		BOOL8 open(string nFilename, BOOL8 nFileState, BOOL8 nSystemEndianness, BOOL8 nFileEndianness); //Opens a file
		BOOL8 close(); //Closes any opened files
		void flush(); //Flushes the file
	//Read/Write
		BOOL8 reposition(LONGLONG64 nPosition); //Moves to an arbitrary file location
		BOOL8 seek(LONGLONG64 nDistance); //Moves to different position in the file relative to the current position
		template<class type> BOOL8 read(type *nData, BOOL8 nHandleEndianness = true); //Reads data into a specified object
		BOOL8 read(CHAR8 *nData, UINT32 nSizeBytes, BOOL8 nHandleEndianness = true); //Reads data into a specified object
		template<class type> BOOL8 write(type *nData, BOOL8 nHandleEndianness = true); //Writes data of a specified object
		BOOL8 write(CHAR8 *nData, UINT32 nSizeBytes, BOOL8 nHandleEndianness = true); //Writes data of a specified object
	//Get/Set
		LONGLONG64 get_size(); //Returns the size of the file in bytes
		LONGLONG64 get_position(); //Returns the current position within the file
		BOOL8 get_systemendianness() { return systemendianness; } //Returns the system endianness (That was previously set)
		BOOL8 get_fileendianness() { return fileendianness; } //Returns the file endianness (That was previously set)
		void set_systemendianness(BOOL8 nSystemEndianness) { systemendianness = nSystemEndianness; } //Sets the system endianness
		void set_fileendianness(BOOL8 nFileEndianness) { fileendianness = nFileEndianness; } //Sets the file endianness
private:
	//Inaccessible
		file(file &rhs);
		file &operator=(file &rhs);
	//Size
		LONGLONG64 size; //Size of file in bytes
	//Endianness
		BOOL8 systemendianness; //Endianness of system
		BOOL8 fileendianness; //Endianness of file
	//Stream
		BOOL8 filestate; //State of file (Read/Write)
		std::fstream stream; //File stream
};

//Read
template<class type> BOOL8 file::read(type *nData, BOOL8 nHandleEndianness)
{
	#ifdef CTM_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not open!\n",true);
			assert(0);
			return false;
		}
		else
			if(filestate != DEF_FILE_STATE_READ)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not opened for reading!\n",true);
				assert(0);
				return false;
			}
	#endif

	//Read data
	stream.read((CHAR8*)nData,sizeof(type));

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((CHAR8*)nData,sizeof(type));
	return true;
}

//Write
template<class type> BOOL8 file::write(type *nData, BOOL8 nHandleEndianness)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to write to file! File is not open!\n",true);
			assert(0);
			return false;
		}
		else
			if(filestate != DEF_FILE_STATE_WRITE)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not opened for writing!\n",true);
				assert(0);
				return false;
			}
	#endif

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((CHAR8*)nData,sizeof(type));

	//Write data
	stream.write((CHAR8*)nData,sizeof(type));

	return true;
}
/////////////////////

//Reverse bytes
inline void reverse_bytes(CHAR8 *data, UINT32 sizebytes)
{
	CHAR8 temp = 0;
	for(UINT32 count = 0; count < sizebytes/2; ++count)
	{
		temp = data[count];
		data[count] = data[sizebytes-1-count];
		data[sizebytes-1-count] = temp;
	}
}

}

#endif