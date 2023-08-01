#ifndef ANIMATION_H
#define ANIMATION_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

/////////////////////
//Animation class
class animation
{
public:
	//System
		animation();
		~animation();
		void update();
		void draw(float x, float y, float width, float height);
	//Functions
		void load_frame(std::string filename, int time = 1); //Loads a frame to the end of the animation
		void clear_frames(); //Clears all frames in animation
		void restart(); //Restarts the animation
private:
	//Data
		int frame; //Current frame number
		int frame_time; //How much time has passed for current frame
		std::vector<texture*> images; //Holds animation textures
		std::vector<int> image_time; //Holds time each texture stays in place
};

//Constructor
animation::animation():
frame(0),
frame_time(0),
image_time(0,0) {}

//Destructor
animation::~animation()
{
	/*
	for(int count = 0; (unsigned int)count < images.size(); count++)
	{
		if(images.at(count) != 0) delete images.at(count); //Delete images
	}
	*/
}

//Update
void animation::update()
{
	frame_time++; //Increment part of frame
	if(frame_time >= image_time.at(frame)) { frame_time = 0; frame++; } //Change frame if time elapsed
	if((unsigned int)frame >= images.size()) frame = 0; //Reset to start frame
}

//Draw
void animation::draw(float x, float y, float width = -1, float height = -1)
{
	images.at(frame)->draw_texture(x,y,width,height);
}

//Load frame
void animation::load_frame(std::string filename, int time)
{
	texture *temp = new texture(filename); //Make temp pointer to texture
	images.insert(images.end(),temp); //Store pointer
	image_time.push_back(time); //Store time
	restart();
}

//Clear frames
void animation::clear_frames()
{
	images.clear(); //Reset frame data
	image_time.clear(); //Reset frame time data
	restart();
}

//Restart
void animation::restart()
{
	frame = 0;
	frame_time = 0;
}
/////////////////////

#endif