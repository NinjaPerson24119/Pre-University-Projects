#ifndef CTM_ANIMATION_H
#define CTM_ANIMATION_H

#include "../Base/Base.h"
#include "../Data/cHeapAllocator.h"
#include "cTextureSheet.h"
#include "../Data/cVector1D.h"
#include "../Data/cString.h"

namespace ctm
{

///////////////////////
//Animation class
class animation
{
public:
	//System
		animation(heapallocator *iAlloc);
		animation(animation &rhs);
		~animation();
		animation &operator=(animation &rhs);
	//Frames
		BOOL8 add_frame(string &iImageFilename, FLOAT32 nTime); //Adds a frame
		BOOL8 add_frame(texture &nImg, FLOAT32 nTime); //Adds a frame
		BOOL8 add_frames(vector1D<texture> &nImgs, vector1D<FLOAT32> &nTimes); //Adds frames
		void clear_frames(); //Clears all the frames
		void update_frames(); //Applies added frames to animation
	//Playback
		void restart(); //Restarts the animation
		void update(FLOAT32 timepassed = 1); //Updates the animation
		void draw(FLOAT32 x, FLOAT32 y); //Draws the current frame
		void draw(FLOAT32 x, FLOAT32 y, UINT32 frame); //Draws a specified frame
	//Get/Set
		UINT32 get_framecount() { return imgs.get_clipcount(); } //Returns the amount of frames
		FLOAT32 &get_playspeed() { return playspeed; } //Returns the play speed 
private:
	//Temporary frames
		vector1D<texture> tempimgs; //Holds newly added frame images
		vector1D<FLOAT32> temptimes; //Holds newly added frame times
	//Frames
		texturesheet imgs; //Frame images
		vector1D<FLOAT32> times; //Frame times
	//Playback
		FLOAT32 playspeed; //Amount of time to elapse for update(1)
		UINT32 currentframe; //Frame currently playing
		FLOAT32 currentelapsed; //Time elapsed on current frame
	//Allocation
		heapallocator *alloc; //Allocator
};
///////////////////////

}

#endif