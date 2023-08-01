#include <Custom/Memory/File.h>
#include <stdexcept>
#include <assert.h>

namespace ctm
{

//Constructor
File::File():
filesize(0),
fmode(READ)
{}

File::File(const char *FileName, FileMode Mode, bool MakeNewfile)
{
	Open(FileName, Mode, MakeNewfile);
}

//Destructor
File::~File()
{
	//Flush and close file
	if(stream.is_open())
	{
		stream.flush();
		stream.close();
	}
}

//Open
void File::Open(const char *FileName, FileMode Mode, bool Makenewfile)
{
	assert(FileName != nullptr);

	//Check that file is not already open
	if(stream.is_open())
		throw std::runtime_error("File - Failed to open file! File is already opened!\n");

	//Open stream
	if(Mode == READ)
		if(Makenewfile)
			stream.open(FileName, std::fstream::binary | std::fstream::in | std::fstream::ate | std::fstream::trunc);
		else
			stream.open(FileName, std::fstream::binary | std::fstream::in | std::fstream::ate);
	else
		if(Makenewfile)
			stream.open(FileName, std::fstream::binary | std::fstream::out | std::fstream::ate | std::fstream::trunc);
		else
			stream.open(FileName, std::fstream::binary | std::fstream::out | std::fstream::ate);

	//Record file size
	if(Mode == READ)
		filesize = stream.tellg();
	else
		filesize = stream.tellp();

	//Seek to start of file
	if(Mode == READ)
		stream.seekg(0);
	else
		stream.seekp(0);

	//Register file fmode
	fmode = Mode;

	//Check for errors
	if(!stream.good())
		throw std::runtime_error("File - Failed to open file!\n");
}

//Close
void File::Close()
{
	//Check that file is open
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to close file! File has not been opened!\n");

	stream.flush();
	stream.close();
}

//Write
void File::Write(char *Data, std::streamsize Length)
{
	assert(Data != nullptr);
	assert(Length > 0);

	//Check that file is opened
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to write to file! File has not been opened!\n");

	stream.write(Data, Length);

	//Check for errors
	if(!stream.good())
		throw std::runtime_error("File - Failed to write to file!\n");
}

//Read
void File::Read(char *Data, std::streamsize Length)
{
	assert(Data != nullptr);
	assert(Length > 0);

	//Check that file is opened
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to read from file! File has not been opened!\n");

	stream.read(Data, Length);

	//Check for errors
	if(!stream.good())
		throw std::runtime_error("File - Failed to read from file!\n");
}

//Seek
void File::Seek(std::streamoff Distance)
{
	//Check that file is open
	if(!stream.is_open())
		throw std::runtime_error("File - Seek failed! File has not been opened!");

	//Check that distance is in range
	if(fmode == READ)
	{
		if((stream.tellg() + Distance >= filesize) || (stream.tellg() + Distance < 0))
			throw std::runtime_error("File - Seek failed! Out of range!\n");
	}
	else
	{
		if((stream.tellp() + Distance >= filesize) || (stream.tellp() + Distance < 0))
			throw std::runtime_error("File - Seek failed! Out of range!\n");
	}

	if(fmode == READ)
		stream.seekg(Distance, std::ios::cur);
	else
		stream.seekp(Distance);
}

//Reposition
void File::Reposition(std::streampos Position)
{
	//Check that File is open
	if(!stream.is_open())
		throw std::runtime_error("File - Reposition failed! File has not been opened!");
	
	//Check that reposition is in range
	if((Position >= filesize) || (Position < 0))
		throw std::runtime_error("File - Reposition failed! Out of range!\n");

	if(fmode == READ)
		stream.seekg(Position);
	else
		stream.seekp(Position);
}

//Position
std::streampos File::Position()
{
	//Check that file is open
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to get position! File has not been opened!");

	if(fmode == READ)
		return stream.tellg();
	else
		return stream.tellp();
}

//Size
std::streampos File::Size()
{
	//Check that file is open
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to get file size! File has not been opened!");

	return filesize;
}

//Is open
bool File::IsOpen()
{
	return stream.is_open();
}

//Mode
File::FileMode File::Mode()
{
	//Check that file is opened
	if(!stream.is_open())
		throw std::runtime_error("File - Failed to get mode! File has not been opened!\n");

	return fmode;
}

}