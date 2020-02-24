/*
Name: Gabriel Byram
Date: November 26, 2019
Description: This program runs a variant of Five-Card-Draw Poker.
*/
#include "header.h"

int main(void)
{
															// menu
	// variable to keep track of user choice for menu
	int choice = 0;

	// runs menu
	do {
		choice = menuChoice();
		determineChoice(choice);
	} while (choice <= 1 || choice > 3);

	return 0;
}
