////////////////////////
//Rectangle class
class rectangle
{
public:
	rectangle(float iLeft, float iTop, float iRight, float iBottom); 
	float left, top, right, bottom;
};

//Constructor
rectangle::rectangle(float iLeft, float iTop, float iRight, float iBottom):
left(iLeft),
top(iTop),
right(iRight),
bottom(iBottom) {}
////////////////////////