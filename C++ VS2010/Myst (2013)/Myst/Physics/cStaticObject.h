#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

////////////////////////
//Static object class
template <class t> class static_object
{
public:
	//System
		static_object(t iBinded) { binded = iBinded; }
		static_object(t iBinded, float x, float y) { binded = iBinded; position.set_point(x,y); }
	//Data
		t binded; //Thing binded to position
		point position; //Position
};
////////////////////////

#endif