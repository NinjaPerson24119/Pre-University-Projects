#include "ReadyCheck.h"

namespace ctm
{

BOOL8 ready_check()
{
	//Check type sizes
	if(sizeof(CHAR8) != 1) return false; 
	if(sizeof(BOOL8) != 1) return false;
	if(sizeof(UCHAR8) != 1) return false;
	if(sizeof(INT32) != 4) return false;
	if(sizeof(UINT32) != 4) return false;
	if(sizeof(LONG32) != 4) return false;
	if(sizeof(ULONG32) != 4) return false;
	if(sizeof(LONGLONG64) != 8) return false;
	if(sizeof(ULONGLONG64) != 8) return false;
	if(sizeof(FLOAT32) != 4) return false;
	if(sizeof(DOUBLE64) != 8) return false;
	
	//Check defaults
	if(DEFAULT_DEBUGLOG == 0)
	{
		return false; //Debug log must be specified
	}

	return true;
}

}