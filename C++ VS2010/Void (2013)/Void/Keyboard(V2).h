//Requires that you #include <conio.h>
//Nics keyboard plugin 
//MADE IN FEBRUARY 2013 (V1)

//V2 enhancements: (MAY 17 2013)
//-Removed +300 from keystate() and now have look up table enables

//Keys
int const UP = 72+300;
int const DOWN = 80+300;
int const LEFT = 75+300;
int const RIGHT = 77+300;
int const SPACE = 32;
int const LESS = 44;
int const GREATER = 46;
int const QUESTION = 47;

int keystate()
{
  int input = 0;
  if(_kbhit())
  {

    //Get keypress
    input = _getch();

    //Special arrowkey function
	if(input == 72) input = UP;
	if(input == 80) input = DOWN;
	if(input == 75) input = LEFT;
	if(input == 77) input = RIGHT;
  }
  return input;
}
