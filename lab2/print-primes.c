/*
 print-prime.c
 By David Broman.
 Last modified: 2022-02-08
 By Viggo Schütt for Lab 2 Assignment 2
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

int is_prime(int n){
	
	int prime = 1;
	for (long i = 2; i * i <= n; i++){	// i * i < n --> same as i < sqrt(n)
		
		if (n % i == 0 || n <= 1){
			prime = 0;
			break;
		}
	}
	return prime;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
 
	// i starts with 2 as it is the first prime number 
	
	for (int i = 2; i < n; i++){

		if (is_prime(i)){ 		// all values != 0 are true
			
			print_numbers(i);
		}

	} 
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
