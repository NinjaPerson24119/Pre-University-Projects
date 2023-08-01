//Nics keyboard plugin 
//Requires conio.h
//MADE IN FEBRUARY 2013

//Keys
//Space=32
//left=75
//right=77
//up=72
//down=80
//enter=13

int keystate()
{
  if(_kbhit())
  {
	//Return variable
    int input = 0;

    //Get keypress
    input = _getch();

    //Get secondary
    if(input = 224)
             input = _getch();

    //Return
	return input;
  }
}
