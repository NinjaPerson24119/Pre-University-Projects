#include "cGuidAllocator.h"

//Constructor
guidallocator::guidallocator(unsigned int iSizeBytes):
heap(0),
size(iSizeBytes)
{
	heap = new char[size]; //Allocate heap
	guids.set_allowance(10); //Set GUIDs vector resize rate
}

//Copy constructor
guidallocator::guidallocator(guidallocator &rhs)
{
	#ifdef CUSTOMLIB_DEBUG
		std::cout << "Error: cGuidAllocator - Failed to copy GUID allocator! GUID allocators cannot be copied!\n";
	#endif
}

//Destructor
guidallocator::~guidallocator()
{
	#ifdef CUSTOMLIB_DEBUG
		if(guids.get_size() != 0)
			std::cout << "Error: cGuidAllocator - " << guids.get_size() << " guids were not deleted!\n";
	#endif
	
	delete[] heap; //Deallocate heap
}

//Operator =
guidallocator &guidallocator::operator=(guidallocator &rhs)
{
	#ifdef CUSTOMLIB_DEBUG
		std::cout << "Error: cGuidAllocator - Failed to assign GUID allocator! GUID allocators cannot be assigned!\n";
	#endif
	return *this;
}

//Generate GUID
unsigned int guidallocator::genguid(unsigned int nSizeBytes)
{
	//Search for memory
	unsigned int difference = 0;
	void *newptr = 0;
	for(unsigned int target = 0; target < guids.get_size(); target++)
	{
		for(unsigned int check = 0; check < guids.get_size(); check++)
		{
			
		}
	}

	#ifdef CUSTOMLIB_DEBUG
		if(newptr == 0)
			std::cout << "Error: cGuidAllocator - Failed to generate GUID! Out of memory!\n";
	#endif
	if(newptr == 0) return 0; //Check that memory was allocated

	//Search for reusable GUID
	unsigned int newid = 0;
	for(unsigned int count = 0; count < guids.get_size(); ++count)
	{
		if(guids[count].ptr == 0)
			newid = guids[count].guid;
	}

	//Make new GUID if no old ones exist
	if(newid == 0) 
	{
		newid = guids.get_size()+1; //Set new GUID
		guids.push_back(guidinfo()); //Insert empty GUID info
	}

	//Set GUID info
	guids[newid].guid = newid; //Set GUID
	guids[newid].ptr = newptr; //Set GUID pointer
	guids[newid].size = nSizeBytes; //Set GUID memory size

	return newid;
}

//Delete GUID
void guidallocator::freeguid(unsigned int guid)
{
	//Clear memory
	char *address = 0;
	for(unsigned int count = 0; count < guids[guid].size; ++count)
	{
		address = (char*)guids[guid].ptr;
		address += count;
	}

	//Clear GUID info
	guids[guid].ptr = 0;
	guids[guid].size = 0;
}