#include "cFile.h"

namespace ctm
{

const BOOL8 CTM_FILE_ENDIANNESS_LITTLE = false;
const BOOL8 CTM_FILE_ENDIANNESS_BIG = true;
const BOOL8 CTM_FILE_STATE_READ = false;
const BOOL8 CTM_FILE_STATE_WRITE = true;

//Constructor
file::file():
systemendianness(false),
fileendianness(false),
filestate(false)
{}

//Copy constructor
file::file(file &rhs)
{}

//Destructor
file::~file()
{
	//Close file
	if(stream.is_open() == true)
		stream.close();
}

//Operator =
file &file::operator=(file &rhs)
{
	return *this;
}

//Open file
BOOL8 file::open(string nFilename, BOOL8 nFileState, BOOL8 nSystemEndianness, BOOL8 nFileEndianness)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(stream.is_open() == true)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cFile - Failed to open file! File is already open!\n",true);
		assert(0);
		return false;
	}
	#endif

	if(nFileState == CTM_FILE_STATE_READ)
		stream.open(nFilename.get_cstr(),std::fstream::binary | std::fstream::in); //Open for input
	else
		stream.open(nFilename.get_cstr(),std::fstream::binary | std::fstream::out); //Open for output
	
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to open file!\n",true);
			return false;
		}
	#endif

	//Set file info
	systemendianness = nSystemEndianness;
	fileendianness = nFileEndianness;
	filestate = nFileState;

	return true;
}

//Close file
BOOL8 file::close()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to close file! File is not open!\n",true);
			assert(0);
			return false;
		}
	#endif

	stream.close();
	return true;
}

//Flush
void file::flush()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to flush file! File is not open!\n",true);
			assert(0);
		}
	#endif

	stream.flush();
}

//Read
BOOL8 file::read(CHAR8 *nData, UINT32 nSizeBytes, BOOL8 nHandleEndianness)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not open!\n",true);
			assert(0);
			return false;
		}
		else
			if(filestate != CTM_FILE_STATE_READ)
			{
				if(DEFAULT_DEBUGLOG != 0)
					DEFAULT_DEBUGLOG->send("Error: cFile - Failed to read from file! File is not opened for reading!\n",true);
				assert(0);
				return false;
			}
	#endif

	//Read data
	stream.read(nData,nSizeBytes);

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((CHAR8*)nData,nSizeBytes);

	return true;
}

//Write
BOOL8 file::write(CHAR8 *nData, UINT32 nSizeBytes, BOOL8 nHandleEndianness)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to write to file! File is not open!\n",true);
			assert(0);
			return false;
		}
		else
			if(filestate != CTM_FILE_STATE_WRITE)
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
			reverse_bytes((CHAR8*)nData,nSizeBytes);

	//Write data
	stream.write((CHAR8*)nData,nSizeBytes);

	return true;
}

}