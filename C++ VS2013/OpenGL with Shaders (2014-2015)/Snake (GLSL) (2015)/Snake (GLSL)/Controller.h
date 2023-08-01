#ifndef CONTROLLER_H
#define CONTROLLER_H

//////
//Controller
class Controller
{
public:
	//Base
		Controller(bool SingleInput);
	//Get
		unsigned int GetX();
		unsigned int GetY();
		bool GetCoordUsage();
		bool GetUp();
		bool GetDown();
		bool GetLeft();
		bool GetRight();
	//Set
		void SetX(unsigned int X);
		void SetY(unsigned int Y);
		void SetCoordUsage(bool Use);
		void SetUp(bool Pressed);
		void SetDown(bool Pressed);
		void SetLeft(bool Pressed);
		void SetRight(bool Pressed);
	//Data
		bool singleinput;
private:
		unsigned int x, y;
		bool usecoords;
		bool up, down, left, right;
};
//////

#endif