// Name: Gabriel Byram
// Class: CPT_S 121
// Program: PA8
// Description: Interview questions
// Date: December 8, 2019

#include "header.h"

int main(void) {
	// test code

	// 1. str_n_cat
	char str1[10] = "man";
	char str2[10] = "plan";

	my_str_n_cat(str1, str2, 3);
	puts(str1);

	// 2. binary search
	int list[5] = { 1, 3, 5, 7, 9 };
	int result = 0;

	result = binarySearch(list, 5, 4);
	printf("%d\n", result); // should print -1

	result = binarySearch(list, 5, 5);
	printf("%d\n", result); // should print 2

	// 3. bubble sort
	char s1[10] = "mall";
	char s2[10] = "call";
	char s3[10] = "ball";
	char* strings[3] = { s1, s2, s3 };

	// print out strings
	for (int i = 0; i < 3; i++) {
		puts(strings[i]);
	}

	// sorts strings
	bubbleSort(strings, 3);

	// print out sorted strings
	for (int i = 0; i < 3; i++) {
		puts(strings[i]);
	}

	// 4. palindrome
	char s4[10] = "race car";
	result = -1;
	result = isPalindrome(s4, 7);
	printf("%d\n", result); // should print 1

	char s5[10] = "popcorn";
	result = -1;
	result = isPalindrome(s5, 7);
	printf("%d\n", result); // should print 0

	// 5. sum of primes
	int primes = 0;
	primes = sumOfPrimes(20, 0);
	printf("There are %d prime numbers starting from 2, and going to 20\n", primes);

	// 6. max occurrences
	Occurrences arr[150] = { 0 };
	char s6[100] = "Thanks for being an awesome TA";
	int occ = 0;
	char ch1 = '\0';

	maximumOccurrences(s6, arr, &occ, &ch1);

	printf("The most used character in that string was %c, which was used %d times\n", ch1, occ);

	// 7. max consecutive
	int conArr[3][5] = { {1, 2, 2, 2, 2}, {2, 6, 8, 8, 8}, {3, 5, 7, 9, 0} };
	int maxNum = 0;
	int maxNumAddress = 0;

	maxConsecutiveIntegers(conArr, 3, 5, &maxNumAddress, &maxNum);

	printf("The highest number of consecutive integers is %d, starting with the address %d", maxNum, maxNumAddress);
}