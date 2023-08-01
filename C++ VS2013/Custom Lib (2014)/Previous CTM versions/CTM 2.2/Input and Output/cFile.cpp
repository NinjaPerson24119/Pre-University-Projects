#include "cFile.h"

namespace ctm
{

const BOOL8 DEF_FILE_ENDIANNESS_LITTLE = false;
const BOOL8 DEF_FILE_ENDIANNESS_BIG = true;
const BOOL8 DEF_FILE_STATE_READ = false;
const BOOL8 DEF_FILE_STATE_WRITE = true;

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
	#ifdef CTM_DEBUG_FAST
	if(stream.is_open() == true)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cFile - Failed to open file! File is already open!\n",true);
		assert(0);
		return false;
	}
	#endif

	if(nFileState == DEF_FILE_STATE_READ)
		stream.open(nFilename.get_cstr(),std::fstream::binary | std::fstream::in | std::fstream::ate); //Open for input
	else
		stream.open(nFilename.get_cstr(),std::fstream::binary | std::fstream::out | std::fstream::ate); //Open for output
	
	#ifdef CTM_DEBUG_FAST
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
	
	//Get file size
	if(filestate == DEF_FILE_STATE_READ)
		size = stream.tellg();
	else
		size = stream.tellp();

	//Seek to start of file
	if(filestate == DEF_FILE_STATE_READ)
		stream.seekg(0,std::fstream::beg);
	else
		stream.seekp(0,std::fstream::beg);

	return true;
}

//Close file
BOOL8 file::close()
{
	#ifdef CTM_DEBUG_FAST
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
	#ifdef CTM_DEBUG_FAST
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to flush file! File is not open!\n",true);
			assert(0);
		}
	#endif

	stream.flush();
}

//Reposition
BOOL8 file::reposition(LONGLONG64 nPosition)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Reposition failed! File is not open!\n",true);
			assert(0);
			return false;
		}
	#endif

	if(filestate == DEF_FILE_STATE_READ)
		stream.seekg(nPosition,std::fstream::beg);
	else
		stream.seekp(nPosition,std::fstream::beg);

	#ifdef CTM_DEBUG_SLOW
		if(stream.good() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Reposition failed! Position is out of range!\n",true);
			assert(0);
			return false;
		}
	#endif

	return true;
}

//Seek
BOOL8 file::seek(LONGLONG64 nDistance)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Seek failed! File is not open!\n",true);
			assert(0);
			return false;
		}
	#endif
	
	if(filestate == DEF_FILE_STATE_READ)
		stream.seekg(nDistance,std::fstream::cur);
	else
		stream.seekp(nDistance,std::fstream::cur);

	#ifdef CTM_DEBUG_SLOW
		if(stream.good() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Seek failed! Position is out of range!\n",true);
			return false;
		}
	#endif

	return true;
}

//Read
BOOL8 file::read(CHAR8 *nData, UINT32 nSizeBytes, BOOL8 nHandleEndianness)
{
	#ifdef CTM_DEBUG_SLOW
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
			reverse_bytes((CHAR8*)nData,nSizeBytes);

	//Write data
	stream.write((CHAR8*)nData,nSizeBytes);

	return true;
}

//Get size
LONGLONG64 file::get_size()
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to get size! File is not open!\n",true);
			assert(0);
			return 0;
		}
	#endif

	return size;
}

//Get position
LONGLONG64 file::get_position()
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to get position! File is not open!\n",true);
			assert(0);
			return 0;
		}
	#endif
	
	if(filestate == DEF_FILE_STATE_READ)
		return stream.tellg();
	else
		return stream.tellp();
}

}