#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define VERSION "3.11"

using namespace std;

int main(int argc, char* argv[])
{
	// TODO: Time as randomseed!!!
	if(argc > 1)
	{
		srand(atoi(argv[1]));
	}
	
	cout << "Random Number Game v" << rand() % 9 << "." << rand() % 999 << endl;
	
	unsigned int number = rand() % 20;
	unsigned int inputNumber = 0;

	char buffer[512];
	
	while(inputNumber != number)
	{
		cout << "Input a number: ";
		cin >> inputNumber;
		//fgets(buffer, sizeof(buffer), stdin);
		//inputNumber = atoi(buffer);
		
		if(inputNumber > number)
			cout << "Your number is greater than my one" << endl;
		else if(inputNumber < number)
			cout << "Your number is smaller than my one" << endl;
	}

	cout << "You won!" << endl;
	
	return 0;
}
