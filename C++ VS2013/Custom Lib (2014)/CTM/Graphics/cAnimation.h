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
		bool add_frame(string &iImageFilename, float nTime); //Adds a frame
		bool add_frame(texture &nImg, float nTime); //Adds a frame
		bool add_frames(vector1D<texture> &nImgs, vector1D<float> &nTimes); //Adds frames
		void clear_frames(); //Clears all the frames
		void update_frames(); //Applies added frames to animation
	//Playback
		void restart(); //Restarts the animation
		void update(float timepassed = 1); //Updates the animation
		void draw(float x, float y); //Draws the current frame
		void draw(float x, float y, unsigned int frame); //Draws a specified frame
	//Get/Set
		unsigned int get_framecount() { return imgs.get_clipcount(); } //Returns the amount of frames
		float &get_playspeed() { return playspeed; } //Returns the play speed 
private:
	//Temporary frames
		vector1D<texture> tempimgs; //Holds newly added frame images
		vector1D<float> temptimes; //Holds newly added frame times
	//Frames
		texturesheet imgs; //Frame images
		vector1D<float> times; //Frame times
	//Playback
		float playspeed; //Amount of time to elapse for update(1)
		unsigned int currentframe; //Frame currently playing
		float currentelapsed; //Time elapsed on current frame
	//Allocation
		heapallocator *alloc; //Allocator
};
///////////////////////

}

#endif