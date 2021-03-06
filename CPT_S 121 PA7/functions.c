#include "header.h"

// displays menu options to user
void displayMenu(void) {
	printf("\n------ 5 Card Draw Poker ------ \n");
	printf("1. Display Game Rules \n");
	printf("2. Play game \n");
	printf("3. Quit \n");
}

// reads an integer value from the user
int readInt(void) {
	int choice = 0;

	scanf("%d", &choice);
	return choice;
}

// this uses displayMenu and readInt to both display menu and get the user input for which option
int menuChoice(void) {
	int choice = 0;

	do {
		displayMenu();
		choice = readInt();
	} while (choice < 1 || choice > 3);
	return choice;
}

//this function prints the rules of 5 card draw poker to the user
void printGameRules(void) {
	printf("\nThis version of poker uses an ante (a forced bet in which all players put \nan equal amount of money into the pot before the deal begins.) \nthe first betting round begins with the player to the dealer's left, \nand the second round begins with the player who opened the first round.\n");
	printf("Play begins with each player being dealt five cards, one at a time, all face down. \nThe remaining deck is placed aside, often protected by placing a chip or other marker on it. \n");
	printf("Players pick up the cards and hold them in their hands, being careful to \n");
	printf("keep them concealed from the other players, then a round of betting occurs.\n");
	printf("If more than one player remains after the first round, the draw phase begins. \nEach player specifies how many of their cards they wish to replace and discards them.\n");
	printf("The deck is retrieved, and each player is dealt in turn from the deck the \nsame number of cards they discarded so that each player again has five cards.\n");
	printf("A second after the draw betting round occurs beginning with the player to the dealer's \n");
	printf("left or else beginning with the player who opened the first round \n");
	printf("This is followed by a showdown, if more than one player remains, ");
	printf("in which the player with the best hand wins the pot.");
	printf("\n\n");
}

// this function uses a switch statement that takes in a choice from the user
// to decide which part of the menu to access
void determineChoice(int choice) {
	switch (choice) {
	case 1:
		printGameRules();
		break;
	case 2:
		playGame();
		break;
	case 3:
		break;
	}
}

// this function assigns each face and suit to a random card value between 1 and 52
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck. replaces cards that the user/computer want to replace */
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand * hand, int replace[], int card)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int originalCardNumber = card;

		for (card; card < originalCardNumber + 5; card++) {
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						if (replace[card - originalCardNumber] == 1) {
							hand->cardArr[card - originalCardNumber].face = column;
							hand->cardArr[card - originalCardNumber].suit = row;
							//printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
						}
					}
				}
			}
		}
	//}
}

// prints the all five cards in a hand to the screen
void displayCards(const char* wFace[], const char* wSuit[], Hand hand) {
	for (int i = 0; i < 5; i++) {
		printf("%5s of %-8s%c", wFace[hand.cardArr[i].face], wSuit[hand.cardArr[i].suit], i % 2 == 0 ? '\n' : '\t');
	}
}

// must have array for which cards you want replaced
// must ask user each time if they want to replace each card
// must shuffle after every deal out of a card

// calculates how many times a card value was obtained and stores the values in an array
void calculateFreq(Hand hand1, int cardFreq[13]) {
	// calculates freq for ones through sixes
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 13; j++) {
			if (hand1.cardArr[i].face == j) {
				cardFreq[j] = cardFreq[j] + 1;
			}
		}
	}
}

// checks if there are at least two cards with the same face in the hand. returns 1 if there is
int hasPair(int cardFreq[]) {
	int hasPair = 0;
	for (int i = 0; i < 13; i++) {
		if (cardFreq[i] > 1) {
			hasPair = 1;
		}
	}
	return hasPair;
}

// checks if there are two instances of two cards with the same face in the hand. returns 1 if there is
int hasTwoPairs(int cardFreq[]) {
	int hasPairs = 0;
	int numPairs = 0;
	for (int i = 0; i < 13; i++) {
		if (cardFreq[i] > 1) {
			numPairs += 1;
		}
	}
	if (numPairs > 1) {
		hasPairs = 1;
	}
	return hasPairs;
}

// checks if there are at least three cards with the same face in the hand. returns 1 if there is
int hasThreeOfAKind(int cardFreq[]) {
	int hasThree = 0;
	for (int i = 0; i < 13; i++) {
		if (cardFreq[i] > 2) {
			hasThree = 1;
		}
	}
	return hasThree;
}

// checks if there are at least four cards with the same face in the hand. returns 1 if there is
int hasFourOfAKind(int cardFreq[]) {
	int hasFour = 0;
	for (int i = 0; i < 13; i++) {
		if (cardFreq[i] > 3) {
			hasFour = 1;
		}
	}
	return hasFour;
}

// checks if there are at least three cards with the same face in the hand. returns 1 if there is
int hasStraight(int cardFreq[]) {
	int hasStraight = 0;
	for (int i = 0; i < 10; i++) {
		if (cardFreq[i] > 0 && cardFreq[i+1] > 0 && cardFreq[i+2] > 0 && cardFreq[i+3] > 0) {
			hasStraight = 1;
		}
	}
	return hasStraight;
}

// checks if all cards in a hand have the same suit. returns 1 if it does
int hasFlush(Hand hand1) {
	int hasFlush = 0;
	int hasZero = 0;
	int has1, has2, has3 = 0;

	for (int i = 0; i < 4; i++) {
		if (hand1.cardArr[i].suit = 0) {
			hasZero = 1;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (hand1.cardArr[i].suit = 1) {
			has1 = 1;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (hand1.cardArr[i].suit = 2) {
			has2 = 1;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (hand1.cardArr[i].suit = 3) {
			has3 = 1;
		}
	}

	if (hasZero == 1 && has1 == 1 && has2 == 1 && has3 == 1) {
	hasFlush = 1;
	}

	return hasFlush;
}

void playGame(void) {
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	srand((unsigned)time(NULL)); /* seed random-number generator */

	// initializes variables
	int keepPlaying = 1;
	int keepBetting = 1;
	int playerBalance = 1000;
	int compBalance = 1000;
	int betAmount = 10;
	int card = 1;
	int playerReplace[5] = { 1, 1, 1, 1, 1 };
	int compReplace[5] = { 1, 1, 1, 1, 1 };
	int roundDone = 0;
	int compCardFreq[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int playerCardFreq[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//initializes playerHand and compHand
	Hand playerHand;
	playerHand.cardArr[0].face = 0;
	playerHand.cardArr[0].suit = 0;
	playerHand.cardArr[1].face = 0;
	playerHand.cardArr[1].suit = 0;
	playerHand.cardArr[2].face = 0;
	playerHand.cardArr[2].suit = 0;
	playerHand.cardArr[3].face = 0;
	playerHand.cardArr[3].suit = 0;
	playerHand.cardArr[4].face = 0;
	playerHand.cardArr[4].suit = 0;

	Hand compHand;
	compHand.cardArr[0].face = 0;
	compHand.cardArr[0].suit = 0;
	compHand.cardArr[1].face = 0;
	compHand.cardArr[1].suit = 0;
	compHand.cardArr[2].face = 0;
	compHand.cardArr[2].suit = 0;
	compHand.cardArr[3].face = 0;
	compHand.cardArr[3].suit = 0;
	compHand.cardArr[4].face = 0;
	compHand.cardArr[4].suit = 0;

	// variables for whether players want to fold, check, or raise
	int playerOption = 0;
	int compOption = 0;

	// variables to keep track of who has folded
	int playerFold = 0;
	int compFold = 0;

	// variables to keep track of the best result in each hand (two pairs, three of a kind, etc.)
	int playerBestInHand = 0;
	int compBestInHand = 0;

	// variables to keep track of all values of the cards together in a hand
	int playerTotalFace = 0;
	int compTotalFace = 0;

	// variables for how much is in the pot, and how much a player has raised
	int potAmount = 0;
	int raiseAmount = 0;

	// variable for whether a certain result (pair, three of a kind, etc.) is in a hand
	int hasInHand = 0;

	// for y/n questions later
	char option = '\0';

	while (keepBetting == 1 && keepPlaying == 1 && playerBalance > 0 && compBalance > 0) {
		// reset key variables each round
		potAmount = 0;
		betAmount = 10;
		card = 1;
		playerFold = 0;
		compFold = 0;

		// both players pay the ante
		compBalance -= betAmount;
		potAmount += betAmount;

		playerBalance -= betAmount;
		potAmount += betAmount;

			system("cls");
			printf("The ante is 10\n");
			printf("You and the computer both put 10 into the pot\n");
			printf("The cards will now be dealt\n");

			// assigns each face and suit to different random card values
			shuffle(deck);

			// deals cards into player's hand
			deal(deck, face, suit, &playerHand, playerReplace, card);
			card += 5;

			// deals cards into the computer's hand
			deal(deck, face, suit, &compHand, compReplace, card);
			card += 5;

			// show user their hand
			printf("Here are your cards: \n");
			displayCards(face, suit, playerHand);
			
			system("pause");

			// ask for choice
			printf("1. Fold \n2. Check \n3. Raise\n");
			scanf("%d", &playerOption);

			// determines which option the user chose
			switch (playerOption) {
			case 1:
				playerFold = 1;
				break;
			case 2:
				playerBalance -= betAmount;
				potAmount += betAmount;
				break;
			case 3:
				do {
					printf("How much would you like to raise the bet by?\n");
					scanf("%d", &raiseAmount);
				} while (playerBalance <= raiseAmount);
				betAmount += raiseAmount;
				potAmount += betAmount;
				playerBalance -= betAmount;
				break;
			}

			// finds frequency of cards in comp's hand
			calculateFreq(compHand, compCardFreq);

			// comp decision
			if (betAmount <= compBalance && playerFold == 0) {
				compOption = compDecision(compHand, compCardFreq, &raiseAmount, compBalance, compReplace, &compBestInHand);

				switch (compOption) {
				case 0:
					printf("The computer has folded\n");
					compFold = 1;
					system("pause");
					break;
				case 1:
					printf("The computer will check\n");
					compBalance -= betAmount;
					potAmount += betAmount;
					break;
				case 2:
					betAmount += raiseAmount;
					potAmount += betAmount;
					compBalance -= betAmount;
					break;
				}
			}
			else if (betAmount > compBalance) {
				printf("The bet amount is higher than the computer's balance. It's showdown time! \n");
				roundDone = 1;
			}

			// draw round if neither player has folded
			if (playerFold == 0 && compFold == 0 && roundDone == 0) {

				// asks which cards the user wants to replace
				for (int i = 0; i < 5; i++) {
					printf("Do you want to replace card %d?", i + 1);
					scanf(" %c", &option);
					if (option == 'Y' || option == 'y') {
						playerReplace[i] = 1;
					}
					else {
						playerReplace[i] = 0;
					}
				}

				//replaces cards the player wanted to replace
				deal(deck, face, suit, &playerHand, playerReplace, card);
				card += 5;

				// replaces cards the computer wanted to replace
				deal(deck, face, suit, &compHand, compReplace, card);
				card += 5;

				// if the bet amount is lower than the player's balance, bet again
				if (betAmount <= playerBalance) {
					// show user their hand
					printf("Here are your cards: \n");
					displayCards(face, suit, playerHand);

					// ask for choice
					printf("1. Fold \n2. Check \n3. Raise\n");
					scanf("%d", &playerOption);

					// determines which option the user chose
					switch (playerOption) {
					case 1:
						playerFold = 1;
						break;
					case 2:
						playerBalance -= betAmount;
						potAmount += betAmount;
						break;
					case 3:
						do {
							printf("How much would you like to raise the bet by?\n");
							scanf("%d", &raiseAmount);
						} while (playerBalance <= raiseAmount);
						betAmount += raiseAmount;
						potAmount += betAmount;
						playerBalance -= betAmount;
						break;
					}
				}
				// if the bet amount is higher than player balance, it goes straight to the showdown
				else {
					printf("The bet amount is higher than your balance. It's showdown time! \n");
					roundDone = 1;
				}

				// computer bets again if the round isn't done and the bet amount isn't above the comp's balance
				if (betAmount <= compBalance && roundDone == 0 && playerFold == 0) {
					// reset freq array
					for (int i = 0; i < 13; i++) {
						compCardFreq[i] = 0;
					}
					// computer bets again
					calculateFreq(compHand, compCardFreq);
					compOption = compDecision(compHand, compCardFreq, &raiseAmount, compBalance, compReplace, &compBestInHand);
					switch (compOption) {
					case 0:
						printf("The computer has folded\n");
						compFold = 1;
						system("pause");
						break;
					case 1:
						printf("The computer will check\n");
						compBalance -= betAmount;
						potAmount += betAmount;
						break;
					case 2:
						betAmount += raiseAmount;
						potAmount += betAmount;
						compBalance -= betAmount;
						break;
					}
				}
			}
				// showdown
				if (playerFold == 0 && compFold == 0) {
					// shows both hands to user
					printf("Here is the computer's hand: \n");
					displayCards(face, suit, compHand);
					system("pause");
					printf("Here is your hand: ");
					displayCards(face, suit, playerHand);
					system("pause");
					// calculates frequency of user's cards
					calculateFreq(playerHand, playerCardFreq);

					// finds highest score in player's hand
					hasInHand = hasPair(playerCardFreq);
					if (hasInHand == 1) {
						playerBestInHand = 1;
					}

					hasInHand = hasTwoPairs(playerCardFreq);
					if (hasInHand == 1) {
						playerBestInHand = 2;
					}

					hasInHand = hasThreeOfAKind(playerCardFreq);
					if (hasInHand == 1) {
						playerBestInHand = 3;
					}

					hasInHand = hasFourOfAKind(playerCardFreq);
					if (hasInHand == 1) {
						playerBestInHand = 4;
					}

					hasInHand = hasStraight(playerCardFreq);
					if (hasInHand == 1) {
						playerBestInHand = 5;
					}

					hasInHand = hasFlush(playerHand);
					if (hasInHand == 1) {
						playerBestInHand = 6;
					}

					// assesses which player has the better hand

					//if user's hand is better than comp's hand, the user wins the pot
					if (playerBestInHand > compBestInHand) {
						printf("Your hand is better than the computer's hand!\n");
						printf("You take the %d\n", potAmount);
						playerBalance += potAmount;
						potAmount = 0;
					}
					// vice vesa
					else if (compBestInHand > playerBestInHand) {
						printf("The computer's hand is better than your hand!\n");
						printf("The computer takes the %d\n", potAmount);
						compBalance += potAmount;
						potAmount = 0;
					}
					// if each player has the same result (one pair, three of a kind, etc.), whoever has the highest face values in their hand wins the round
					else {
						playerTotalFace = playerHand.cardArr[0].face + playerHand.cardArr[1].face + playerHand.cardArr[2].face + playerHand.cardArr[3].face + playerHand.cardArr[4].face;
						compTotalFace = compHand.cardArr[0].face + compHand.cardArr[1].face + compHand.cardArr[2].face + compHand.cardArr[3].face + compHand.cardArr[4].face;
						if (playerTotalFace > compTotalFace) {
							printf("Your hand is better than the computer's hand!\n");
							printf("You take the %d\n", potAmount);
							playerBalance += potAmount;
							potAmount = 0;
						}
						else {
							printf("The computer's hand is better than your hand!\n");
							printf("The computer takes the %d\n", potAmount);
							compBalance += potAmount;
							potAmount = 0;
						}
						//
					}

				}
			// round is cut short if one player folds. the other player gets the money and wins the round
				if (playerFold == 1) {
					printf("The computer takes the %d\n", potAmount);
					compBalance += potAmount;
					potAmount = 0;
				}
				else if (compFold == 1) {
					printf("You take the %d\n", potAmount);
					playerBalance += potAmount;
					potAmount = 0;
				}


				// lets user know what the balances are
				printf("Your balance is %d\n", playerBalance);
				printf("The computer's balance is %d\n", compBalance);
				system("pause");

				// asks user if they want to keep playing
				if (playerBalance > 0 || compBalance > 0) {
					printf("Do you want to stop playing? (Y/N)\n");
					option = '\0';
					scanf(" %c", &option);
					if (option == 'Y' || option == 'y') {
						keepPlaying = 0;
					}
				}
				// if a player doesn't have any money left, notify the user and end the game
				if (playerBalance < 1) {
					printf("Oh no! You don't have any more money. Better luck next time!\n");
					keepPlaying = 0;
				}
				if (compBalance < 1) {
					printf("Congratulations! The computer has no more money to bet. Good job!\n");
					keepPlaying = 0;
				}

				// set deck back to all 0s so shuffle() can work
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 13; j++) {
						deck[i][j] = 0;
					}
				}
				// set card frequency arrays back to 0
				for (int i = 0; i < 13; i++) {
					playerCardFreq[i] = 0;
					compCardFreq[i] = 0;
				}
				// set Replace arrays back to all 1s
				for (int i = 0; i < 5; i++) {
					playerReplace[i] = 1;
					compReplace[i] = 1;
				}
				// reset roundDone to 0
				roundDone = 0;
	}
	/*if (playerBalance > 0 || compBalance > 0) {
		printf("Do you want to keep playing? (Y/N)\n");
		option = '\0';
		scanf(" %c", &option);
		if (option == 'Y' || 'y') {
			keepPlaying = 0;
		}
	}*/
	//if (playerBalance < 1) {
	//	printf("Oh no! You don't have any more money. Better luck next time!\n");
	//}
	//if (compBalance < 1) {
	//	printf("Congratulations! The computer has no more money to bet. Good job!\n");
	//}

	//printf("Your final balance is %d\n", playerBalance);
}

// this function is the AI of the computer. it determines whether to fold, check, or raise, and which cards to replace, based on the computer's current hand
int compDecision(Hand compHand, int cardFreq[5], int * raiseAmount, int balance, int replace[5], int * best) {
	int option = 0;

	// variable that will equal face value of cards we don't want to replace.
	int dontReplace1 = 0;

	//variable that will equal face value of card we do want to replace
	int replaceCard = 0;

	// checks if hand has a flush. raises by 200 and returns 2 (raise) if it does
	option = hasFlush(compHand);
	if (option == 1) {
		*best = 6;
		if (balance >= 200) {
			*raiseAmount = 200;
			printf("The computer has raised by 200!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in!\n");
			system("pause");
		}

		// don't replace any cards
		replace[0] = 0;
		replace[1] = 0;
		replace[2] = 0;
		replace[3] = 0;
		replace[4] = 0;

		printf("The computer will not replace any cards\n");

		return 2;
	}
	option = 0;

	// checks if hand has a straight. raises by 100 and returns 2 (raise) if it does
	option = hasStraight(cardFreq);
	if (option == 1) {
		*best = 5;
		if (balance >= 100) {
			*raiseAmount = 100;
			printf("The computer has raised by 100!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in!\n");
			system("pause");
		}

		// don't replace any cards
		replace[0] = 0;
		replace[1] = 0;
		replace[2] = 0;
		replace[3] = 0;
		replace[4] = 0;

		printf("The computer will not replace any cards\n");

		return 2;
	}

	option = 0;
	// checks if hand has a four of a kind. raises by 60 and returns 2 (raise) if it does
	option = hasFourOfAKind(cardFreq);
	if (option == 1) {
		*best = 4;
		if (balance >= 60) {
			*raiseAmount = 60;
			printf("The computer has raised by 60!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in!\n");
			system("pause");
		}

		// don't replace any cards
		replace[0] = 0;
		replace[1] = 0;
		replace[2] = 0;
		replace[3] = 0;
		replace[4] = 0;

		printf("The computer will not replace any cards\n");

		return 2;
	}

	option = 0;
	// checks if hand has a three of a kind. raises by 40 and returns 2 (raise) if it does
	option = hasThreeOfAKind(cardFreq);
	if (option == 1) {
		*best = 3;
		if (balance >= 40) {
			*raiseAmount = 40;
			printf("The computer has raised by 40!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in!\n");
			system("pause");
		}

		// finds which face values in the hand have three of a kind
		for (int i = 0; i < 5; i++) {
			if (cardFreq[i] > 2) {
				dontReplace1 = i;
			}
		}

		// replaces the cards that aren't in the three of a kind
		for (int i = 0; i < 5; i++) {
			if (compHand.cardArr[i].face == dontReplace1) {
				replace[i] = 0;
			}
			else {
				replace[i] = 1;
			}
		}

		printf("The computer will replace 2 cards\n");

		return 2;
	}

	option = 0;
	// checks if hand has two pairs. raises by 20 and returns 2 (raise) if it does
	option = hasTwoPairs(cardFreq);
	if (option == 1) {
		*best = 2;
		if (balance >= 20) {
			*raiseAmount = 20;
			printf("The computer has raised by 20!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in!\n");
			system("pause");
		}

		// find out which card in the hand doesn't have a pair and replace that card
		for (int i = 0; i < 5; i++) {
			if (cardFreq[i] < 1) {
				replace[i] = 1;
			}
			else {
				replace[i] = 0;
			}
		}

		printf("The computer will replace 1 card \n");

		return 2;
	}

	option = 0;

	// checks if hand has a pair. raises by 10 and returns 2 (raise) if it does
	option = hasPair(cardFreq);
	if (option == 1) {
		*best = 1;
		if (balance >= 10) {
			*raiseAmount = 10;
			printf("The computer has raised by 10!\n");
			system("pause");
		}
		else {
			*raiseAmount = balance;
			printf("The computer is all in\n");
			system("pause");
		}
		

		// replace cards that don't have a pair
		for (int i = 0; i < 5; i++) {
			if (cardFreq[i] < 2) {
				replace[i] = 1;
			}
			else {
				replace[i] = 0;
			}
		}


		printf("The computer will replace 3 cards\n");

		return 2;
	}

	// if it has none of the above, replace all cards
	for (int i = 0; i < 5; i++) {
		replace[i] = 1;
	}

	// if it has none of the above, 50% chance to check, 50% chance to fold
	option = rand() % 2;

	return option;
}