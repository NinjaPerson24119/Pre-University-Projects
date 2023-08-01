#ifndef ANGLE_H
#define ANGLE_H

////////////////////
//Angle class
class angle
{
public:
	angle(float iDegrees): degrees(iDegrees) {}
	void wrap() { degrees = (float)((int)degrees%360); }
	void set_degrees(float nDegrees) { degrees = nDegrees; wrap(); }
	void set_radians(float nRadians) { degrees = nRadians * RAD_TO_DEG; wrap(); }
	float get_degrees() { return degrees; }
	float get_radians() { return degrees * DEG_TO_RAD; }
private:
	float degrees;
};
////////////////////

#endif