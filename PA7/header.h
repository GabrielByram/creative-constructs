// header guard
#ifndef PA7
#define PA7

// to use scanf, printf
#define _CRT_SECURE_NO_WARNINGS

//import libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structs

// struct for a card. has face and suit values
typedef struct card {
	int face;
	int suit;
} Card;

// struct for a hand of cards that a player has
typedef struct hand {
	Card cardArr[5];
} Hand;

//function prototypes
void displayMenu(void);
int readInt(void);
int menuChoice(void);
void printGameRules(void);
void determineChoice(int choice);
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand * hand, int replace[], int card);
void displayCards(const char* wFace[], const char* wSuit[], Hand hand);
int hasPair(int cardFreq[]);
int hasTwoPairs(int cardFreq[]);
void playGame(void);
int compDecision(Hand compHand, int cardFreq[13], int* betAmount);
int hasFlush(Hand hand1);
int hasStraight(int cardFreq[]);
int hasFourOfAKind(int cardFreq[]);
int hasThreeOfAKind(int cardFreq[]);


#endif