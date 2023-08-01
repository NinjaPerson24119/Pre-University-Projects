#ifndef METEOR_H
#define METEOR_H

///////////////////////
//Meteor class
class meteor
{
public:
	meteor(float PX, float PY, float VX, float VY);
	float px, py; //Position
	float vx, vy; //Vector
};

//Constructor
meteor::meteor(float PX, float PY, float VX, float VY):
px(PX), py(PY),
vx(VX), vy(VY) {}
///////////////////////

#endif