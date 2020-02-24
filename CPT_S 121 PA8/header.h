#ifndef PA8
#define PA8

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// structs
typedef struct occurrences {
	int num_occurrences;
	double frequency;
} Occurrences;


//function prototypes
char* my_str_n_cat(char* destination, const char* source, int n);
int binarySearch(int list[], int n, int targetValue);
void bubbleSort(char* arr[], int numStrings);
int isPalindrome(char arr[], int length);
void removeWhiteSpace(char arr[], int length);
int sumOfPrimes(unsigned int n, int sum);
int checkIfPrime(unsigned int n);
void maximumOccurrences(char* str, Occurrences occArr[], int* maxNum, char* maxChar);
void maxConsecutiveIntegers(signed int intArr[][5], int rows, int cols, int* startingPosPtr, int* numPtr);

#endif