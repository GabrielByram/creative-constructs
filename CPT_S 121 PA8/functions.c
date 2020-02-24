#include "header.h"

// this function takes in two strings (a destination string and a source string) and an integer that corresponds to how many characters from the source string the user
// wants to copy over onto the end of the destination string. this function copies a certain number of user-determined characters from the source string onto the end of the destination string,
// then returns the destination string
char* my_str_n_cat(char* destination, const char* source, int n) {
	int destSize = 0;
	int sourceSize = 0;
	char check = 'm';
	while (check != '\0') {
		check = destination[destSize];
		destSize++;
	}
	check = 'm';

	while (check != '\0') {
		check = source[sourceSize];
		sourceSize++;
	}
	sourceSize--;
	destSize--;

	check = 'm';
	for (int i = 0; i < n; i++) {
		if (check != '\0') {
			check = source[i];
			destination[destSize + i] = source[i];
		}
	}
	return destination;
}

// this function takes in an array of integers, an integer corresponding to the length of the array, and a target number. it determines whether that target number is within the array.
// if it is, it returns the index in the array at which the target value is found. if the target value is not in the array, it returns -1
int binarySearch(int list[], int n, int target) {
	int left = 1;
	int right = n;
	int targetIndex = -1;
	int mid = 0;
	int found = 0;

	while (!found && left <= right) {
		mid = (right + left) / 2;
		if (target == list[mid]) {
			found = 1;
			targetIndex = mid;
		}
		else if (target < list[mid]) {
			right = mid - 1;
		}
		else if (target > list[mid]) {
			left = mid + 1;
		}
	}
	return targetIndex;
}

// this function takes in array of strings and the number of strings in the array, and sorts the array of strings into alphabetical order using bubble sort
void bubbleSort(char* arr[], int numStrings) {
	int uMarker = numStrings;
	int cMarker = 0;
	while (uMarker > 1) {
		cMarker = 1;
		while (cMarker < uMarker) {
			if (*arr[cMarker] < *arr[cMarker - 1]) {
				char * temp = arr[cMarker - 1];
				arr[cMarker - 1] = arr[cMarker];
				arr[cMarker] = temp;
			}
			cMarker++;
		}
		uMarker--;
	}
}

// this function takes in a string, then determines whether the string is a palindrome. returns 1 if it is. returns 0 if it is not.
int isPalindrome(char arr[], int length) {
	removeWhiteSpace(arr, length + 1);

	int left = 0;
	int right = length - 1;
	int isPalindrome = 1;

	while (left <= right && isPalindrome) {
		if (arr[left] != arr[right]) {
			isPalindrome = 0;
		}
		left++;
		right--;
	}
	return isPalindrome;
}

// this function takes in a string and it's length, and changes the string to a copy of itself without white space
void removeWhiteSpace(char arr[], int length) {
	int whiteSpaces[100] = { 0 };
	char newStr[100];
	int numberOfWhiteSpaces = 0;

	for (int i = 0; i < length; i++) {
		if (arr[i] == ' ') {
			whiteSpaces[i] = 1;
		}
	}

	for (int i = 0; i < length; i++) {
		if (whiteSpaces[i] != 1) {
			newStr[i - numberOfWhiteSpaces] = arr[i];
		}
		else {
			numberOfWhiteSpaces++;
		}
	}
	strcpy(arr, newStr);
}

// this function recursively calculates how many prime number are from 2 to the number passed into this function
int sumOfPrimes(unsigned int n, int sum) {

	// returns sum if the number is less than 2
	if (n < 2) {
		return sum;
	}

	if (n == 2) {
		sum++;
	}

	// checks if the number it is on is prime
	// first checks if it is a multiple of 2
	if (checkIfPrime(n) == 1) {
		sum++;
	}

	// recursively call itself
	sumOfPrimes(n - 1, sum);
}

// this function takes in an unsigned integer and determines if it prime. if it is, the function returns 1. if it isn't, the function returns 0
int checkIfPrime(unsigned int n) {
	int prime = 1;
	// checks if the number it is on is prime
	// first checks if it is a multiple of 2
	if (n % 2 == 0) {
		return 0;
	}

	// cycles through all the odd numbers to if n is a multiple of any of them
	for (int i = 3; i < n / 2; i = i + 2) {
		if (n % i == 0) {
			return 0;
		}
	}

	return prime;
}

// this function takes in a string and an array of Occurrences structs, and determines which alphanumeric character is the most used in the string and
// how many times that character appears. this function also writes this information to the Occurrences structs, and determines the frequency of each character and writes it
// to the Occurrences structs
void maximumOccurrences(char* str, Occurrences occArr[], int* maxNum, char* maxChar) {
	int index = 0;
	int count[130] = { 0 };

	// calculates string length
	while (str[index] != '\0') {
		index++;
	}

	// changes string to all lowercase
	for (int i = 0; i < index; i++) {
		str[i] = tolower(str[i]);
	}

	index = 0;
	// count white space
	while (str[index] != '\0') {
		for (int i = 32; i < 33; i++) {
			if (str[index] == i) {
				count[i]++;
			}
		}
		index++;
	}
	index = 0;

	// count lowercase letters
	while (str[index] != '\0') {
		for (int i = 97; i < 123; i++) {
			if (str[index] == i) {
				count[i]++;
			}
		}
		index++;
	}

	// find largest index
	int largestIndex = 0;

	for (int i = 31; i < 123; i++) {
		if (count[i + 1] > count[largestIndex]) {
			largestIndex = i + 1;
		}
		occArr[i].num_occurrences += count[i];
		occArr[i].frequency = (occArr[i].num_occurrences / index);
	}

	*maxNum = count[largestIndex];
	*maxChar = largestIndex;
}

// this function takes in a 2D array of signed integers, and determines how many consecutive integers of the same number there are,
// and the address of the first integer in the list of most consecutive integers of the same number
void maxConsecutiveIntegers(signed int intArr[][5], int rows, int cols, int* startingPosPtr, int* numPtr) {
	int startingPosition = 0;
	int streak = 0;
	int maxStreak = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j == 0) {
				if (intArr[i][j] == intArr[i - 1][cols - 1]) {
					streak++;
					startingPosition = (&intArr[i][j] - streak * 4);
				}
				else {
					streak = 0;
				}
				if (streak > maxStreak) {
					maxStreak = streak;
				}
			}
			else {
				if (intArr[i][j] == intArr[i][j - 1]) {
					streak++;
					startingPosition = (&intArr[i][j] - streak * 4);
				}
				else {
					streak = 0;
				}
				if (streak > maxStreak) {
					maxStreak = streak;
				}
			}
		}
	}
	*startingPosPtr = startingPosition;
	*numPtr = maxStreak + 1;
}