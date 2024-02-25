/*
 sieves.c
 By Viggo Schütt.
 Last modified: 2022-02-09
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int row = 0;			// global variable for amount of rows that been printed

void print_numbers(int n){

	if (row >= COLUMNS){	// if rows is more than columns --> print new row & row = 0
		printf("\n");
		row = 0;
	}
	printf("%10d ", n);
	row++;
}

void print_sieves(int n){

	// n is parameter which states the max prime number value
	// prints out all prime numbers less than n
	// Uses char instead of int to save memory 

	char arr[n];			// skapar vektor med n element första 2 element används inte
	for (int i = 0; i < n; i++){

		arr[i] = 1; 		// according to sieves, all nummbers should initially be set to true
	}

	for (long i = 2; i * i < n; i++){	// i*i < n same as i < sqrt (n) - uses long for large numbers
	
		if (arr[i]){		// if arr[i] is true (== 1)
			
			for (long j = i*i; j < n; j += i){
				
				arr[j] = 0;		// sets all composite numbers to false 
			}
		}
	}

	for (int i = 2; i < n; i++)
		if (arr[i])
			print_numbers(i);

	      
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
