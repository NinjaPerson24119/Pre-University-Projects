#include "cAnimation.h"

//Constructor
animation::animation():
playspeed(1),
currentframe(0),
currentelapsed(0)
{}

//Copy constructor
animation::animation(animation &rhs):
playspeed(rhs.playspeed),
currentframe(rhs.currentframe),
currentelapsed(rhs.currentelapsed)
{
	imgs = rhs.imgs;
	times = rhs.times;
}

//Destructor
animation::~animation()
{
	imgs.free_texture();
}

//Operator =
animation &animation::operator=(animation &rhs)
{
	playspeed = rhs.playspeed;
	currentframe = rhs.currentframe;
	currentelapsed = rhs.currentelapsed;
	imgs = rhs.imgs;
	times = rhs.times;
	return *this;
}

//Add frame
bool animation::add_frame(string nImageFilename, FLOAT32 nTime)
{
	texture temp;
	temp.load_texture(nImageFilename);
	return add_frame(temp,nTime);
}

//Add frame
bool animation::add_frame(texture nImg, FLOAT32 nTime)
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(nImg.get_id() == 0)
			{
				DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frame! Image has not been loaded!\n",false);
				return false;
			}
	#endif

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(imgs.get_clipcount() != 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				if((nImg.get_imgwidth() != imgs.get_clip(0).get_width()) || (nImg.get_imgheight() != imgs.get_clip(0).get_height()))
				{
					DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frame! New frame dimensions are not equal to existing frame dimensions!\n",false);
					return false;
				}
		}
	#endif

	tempimgs.push_back(nImg);
	temptimes.push_back(nTime);
	return true;
}

//Add frames
BOOL8 animation::add_frames(vector1D<texture> nImgs, vector1D<FLOAT32> nTimes)
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(nImgs.get_size() != nTimes.get_size())
			{
				DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frames! Image and time vectors are not the same size!\n",false);
				return false;
			}
	#endif

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
		{
			for(UINT32 count = 0; count < nImgs.get_size(); ++count)
			{
				if((nImgs[0].get_imgwidth() != nImgs[count].get_imgwidth()) || (nImgs[0].get_imgheight() != nImgs[count].get_imgheight()))
				{
					DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frames! Frames do not all have equal dimensions!\n",false);
					return false;
				}
			}
		}
	#endif

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
		{
			if(imgs.get_clipcount() != 0)
			{
				for(UINT32 count = 0; count < nImgs.get_size(); ++count)
				{
					if((imgs.get_clip(0).get_width() != nImgs[count].get_imgwidth()) || (imgs.get_clip(0).get_height() != nImgs[count].get_imgheight()))
					{
						DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frames! New frame dimensions are not equal to existing frame dimensions!\n",false);
						return false;
					}
				}
			}
		}
	#endif

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
		{
			for(UINT32 count = 0; count < nImgs.get_size(); ++count)
			{
				if(nImgs[count].get_id() == 0)
				{
					DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to add frames! One or more images have not been loaded!\n",false);
					return false;
				}
			}
		}
	#endif

	//Copy images to temp vector
	tempimgs.resize(tempimgs.get_size()+nImgs.get_size());
	for(UINT32 count = 0; count < nImgs.get_size(); ++count)
	{
		tempimgs[count+tempimgs.get_size()-nImgs.get_size()] = nImgs[count];
	}

	//Copy times to temp vector
	temptimes.resize(temptimes.get_size()+nTimes.get_size(),0);
	for(UINT32 count = 0; count < nTimes.get_size(); ++count)
	{
		temptimes[count+temptimes.get_size()-nTimes.get_size()] = nTimes[count];
	}
	return true;
}

//Clear frames
void animation::clear_frames()
{
	tempimgs.clear(); //Clear temporary images
	temptimes.clear(); //Clear temporary times
	times.clear(); //Clear times
}

//Update frames
void animation::update_frames()
{
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if((tempimgs.get_size() == 0) || (temptimes.get_size() == 0))
				DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to update frames! No new frames exist!\n",false);
	#endif
	
	//Make bigger texture sheet
	texturesheet newsheet;
	
	if(imgs.get_id() != 0)
		newsheet.load_texture(imgs.get_imgwidth()+(tempimgs[0].get_imgwidth()*tempimgs.get_size()),imgs.get_imgheight());
	else
		newsheet.load_texture(tempimgs[0].get_imgwidth()*tempimgs.get_size(),tempimgs[0].get_imgheight());
	newsheet.bind_texture(); //Bind new sheet for operations

	//Blit old frames to new sheet
	if(imgs.get_id() != 0)
	{
		imgs.bind_texture();
		imgs.blit_texture(0,0,newsheet);
		imgs.unbind_texture();
	}
		
	//Blit new frames to new sheet
	for(UINT32 count = 0; count < tempimgs.get_size(); ++count)
	{
		tempimgs[count].bind_texture();
		tempimgs[count].blit_texture(imgs.get_imgwidth()+(tempimgs[count].get_imgwidth()*count),0,newsheet);
		tempimgs[count].unbind_texture();
	}

	//Add clips
	rect region(0,0,0,(FLOAT32)tempimgs[0].get_imgheight());
	for(UINT32 count = 0; count < tempimgs.get_size()+imgs.get_clipcount(); ++count)
	{
		region.left = (FLOAT32)(count*tempimgs[0].get_imgwidth());
		region.right = (FLOAT32)(region.left + tempimgs[0].get_imgwidth());
		newsheet.add_clip(region);
	}
	newsheet.update_clips(); //Update clips

	//Add frame times
	times.resize(times.get_size()+temptimes.get_size(),0);
	for(UINT32 count = 0; count < temptimes.get_size(); ++count)
	{
		times[count+times.get_size()-temptimes.get_size()] = temptimes[count];
	}
	
	//Finalize sheet
	newsheet.unbind_texture(); //Unbind sheet
	imgs = newsheet; //Overwrite old sheet with new sheet

	//Clear temporary vectors
	tempimgs.clear();
	temptimes.clear();

	//Restart animation
	restart();
}

//Restart
void animation::restart()
{
	currentframe = 0; //Reset current frame
	currentelapsed = 0; //Reset elapsed time
}

//Update
void animation::update(FLOAT32 timepassed)
{
	#ifdef CUSTOMLIB_DEBUG_SLOW
		if(DEFAULT_DEBUGLOG != 0)
			if(imgs.get_clipcount() == 0)
				DEFAULT_DEBUGLOG->send_error("Error: cAnimation - Failed to update animation! No frames exist!\n",false);
	#endif

	currentelapsed += playspeed*timepassed; //Update elapsed time
	
	//Check to decrement current frame
	while(currentelapsed < 0)
	{
		currentelapsed += times[currentframe]; //Lock currentelapsed over 0
		--currentframe; //Decrement
		if(currentframe < 0) currentframe = imgs.get_clipcount()-1; //Stop frame from decrementing below 0
	}

	//Check to increment current frame
	while(currentelapsed >= times[currentframe])
	{
		currentelapsed -= times[currentframe]; //Lock currentelapsed below end of frame
		++currentframe; //Increment frame
		if(currentframe >= imgs.get_clipcount()) currentframe = 0; //Stop frame from incrementing over highest frame
	}
}

//Draw
void animation::draw(INT32 x, INT32 y)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(imgs.get_clipcount() == 0)); //Error: cAnimation - Failed to draw animation! Animation has not been loaded!
	#endif

	imgs.draw_clip(x,y,currentframe);
}

//Draw
void animation::draw(INT32 x, INT32 y, UINT32 frame)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		assert(!(frame >= imgs.get_clipcount())); //Error: cAnimation - Failed to draw animation! Invalid frame!
	#endif

	imgs.draw_clip(x,y,frame);
}