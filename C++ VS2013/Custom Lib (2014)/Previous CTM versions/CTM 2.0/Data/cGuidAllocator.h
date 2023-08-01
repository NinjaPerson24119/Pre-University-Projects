#ifndef GUIDALLOCATOR_H
#define GUIDALLOCATOR_H

#include "../Base/Base.h"
#include "cVector1D.h"

//////////////////////
//GUID info
class guidinfo
{
	friend class guidallocator;
public:
	guidinfo(): ptr(0), size(0), guid(0) {}
private:
	void *ptr; //Pointer to data
	unsigned int size; //Size of data
	unsigned int guid; //Guid
};
//////////////////////

//////////////////////
//GUID allocator class
class guidallocator
{
public:
	//System
		guidallocator(unsigned int iSizeBytes);
		guidallocator(guidallocator &rhs);
		~guidallocator();
		guidallocator &operator=(guidallocator &rhs);
	//GUIDs
		unsigned int genguid(unsigned int nSizeBytes); //Generates a GUID to a block of memory of the specified size
		void freeguid(unsigned int guid); //Deletes a GUID
	//Get/Set
		unsigned int get_allowance() { return guids.get_allowance(); } //Generations called before each vector resize
		void set_allowance(unsigned int nAllowance) { guids.set_allowance(nAllowance); } //Generations called before each vector resize
private:
	//Data
		char *heap; //Heap
		unsigned int size; //Size of heap in bytes
	//GUIDs
		vector1D<guidinfo> guids; //GUID lookup list
};
//////////////////////

#endif