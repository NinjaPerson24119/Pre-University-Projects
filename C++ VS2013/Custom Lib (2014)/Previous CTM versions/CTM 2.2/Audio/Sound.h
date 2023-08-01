#ifndef CTM_SOUND_H
#define CTM_SOUND_H

#include "../Base/Base.h"
#include "../External/OpenAL.h"
#include "../Data/cString.h" 

namespace ctm
{

	//////////////////
	//Sound class
	class sound
	{
	public:
		//System
		sound();
		sound(sound &rhs);
		~sound();
		sound &operator=(sound &rhs);
		BOOL8 load_sound(string &iWavFilename);

	private:

	};
	//////////////////

}

#endif