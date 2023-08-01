#include <iostream>

int main()
{
	for(int count = 0; count < 256; count++)
	{
		char symbol = count;
		std::cout << count << ": " << symbol << "\n";
	}
	int wait;
	std::cin >> wait;
}