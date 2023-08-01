#include "cFile.h"

namespace ctm
{

const endianness DEF_FILE_ENDIANNESS_LITTLE = false;
const endianness DEF_FILE_ENDIANNESS_BIG = true;
const filestate DEF_FILE_STATE_READ = false;
const filestate DEF_FILE_STATE_WRITE = true;

//Reverse bytes
inline void reverse_bytes(char *data, std::streamoff sizebytes)
{
	char temp = 0;
	for(std::streamoff count = 0; count < sizebytes / 2; ++count)
	{
		temp = data[count];
		data[count] = data[sizebytes - 1 - count];
		data[sizebytes - 1 - count] = temp;
	}
}

//Constructor
file::file():
systemendianness(false),
fileendianness(false),
state(false)
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
bool file::open(string nFilename, filestate nFileState, endianness nSystemEndianness, endianness nFileEndianness)
{
	#ifdef CTM_DEBUG_FAST
	if(stream.is_open() == true)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cFile - Failed to open file! File is already open!\n",true);
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
	state = nFileState;
	
	//Get file size
	if(state == DEF_FILE_STATE_READ)
		size = stream.tellg();
	else
		size = stream.tellp();

	//Seek to start of file
	if(state == DEF_FILE_STATE_READ)
		stream.seekg(0,std::fstream::beg);
	else
		stream.seekp(0,std::fstream::beg);

	return true;
}

//Close file
bool file::close()
{
	#ifdef CTM_DEBUG_FAST
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to close file! File is not open!\n",true);
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
		}
	#endif

	stream.flush();
}

//Reposition
bool file::reposition(std::streamoff nPosition)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Reposition failed! File is not open!\n",true);
			return false;
		}
	#endif

	if(state == DEF_FILE_STATE_READ)
		stream.seekg(nPosition,std::fstream::beg);
	else
		stream.seekp(nPosition,std::fstream::beg);

	#ifdef CTM_DEBUG_SLOW
		if(stream.good() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Reposition failed! Position is out of range!\n",true);
			return false;
		}
	#endif

	return true;
}

//Seek
bool file::seek(std::streamoff nDistance)
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Seek failed! File is not open!\n",true);
			return false;
		}
	#endif
	
	if(state == DEF_FILE_STATE_READ)
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
bool file::read(char *nData, std::streamoff nSizeBytes, bool nHandleEndianness)
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
	stream.read(nData,nSizeBytes);

	//Handle endianness
	if(nHandleEndianness == true)
		if(systemendianness != fileendianness)
			reverse_bytes((char*)nData,nSizeBytes);

	return true;
}

//Write
bool file::write(char *nData, std::streamoff nSizeBytes, bool nHandleEndianness)
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
			reverse_bytes((char*)nData,nSizeBytes);

	//Write data
	stream.write((char*)nData,nSizeBytes);

	return true;
}

//Get size
std::streamoff file::get_size()
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to get size! File is not open!\n",true);
			return 0;
		}
	#endif

	return size;
}

//Get position
std::streamoff file::get_position()
{
	#ifdef CTM_DEBUG_SLOW
		if(stream.is_open() == false)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cFile - Failed to get position! File is not open!\n",true);
			return 0;
		}
	#endif
	
	if(state == DEF_FILE_STATE_READ)
		return stream.tellg();
	else
		return stream.tellp();
}

}