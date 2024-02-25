/*
 Suprise2.c
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
	// allocates to heap instead of stack

	char* list;	// skapar vektor med n element första 2 element används inte
	long sum = 0;	// summan av alla primtal mindre än n
	int lastprime = 2; // första primtalet
	int primecount = 0;
	double avg_distance = 0;

	list = (char*)malloc(n * sizeof(char));

	for (int i = 2; i < n; i++){

		list[i] = 1; 		// according to sieves, all nummbers should initially be set to true
	}

	for (long i = 2; i * i< n; i++){	// i*i < n same as i < sqrt (n) - uses long for large numbers of n
	
		if (list[i]){		// if list[i] is true (== 1)
			
			for (long j = i*i; j < n; j += i){
				
				list[j] = 0;		// sets all composite numbers to false 
			}
		}
	}

	for (int i = 2; i < n; i++)
		if (list[i]){
			print_numbers(i);		// prints all primes less than n
			sum += i - lastprime;		// get sum of all distance  
			lastprime = i;			// lastprime takes the value of the current prime
			primecount++;			// the count (amount) of primes adds with 1
		}	

	if (primecount > 1)
		avg_distance = (double) sum / (primecount - 1);	// calculates the average distance of all primes - 1 for begi

	printf("\n Distanace between all primes = %d", sum);
	printf("\n Amount of primes below %d = %d", n, primecount);
	printf("\n Average distance between all primes = %f", avg_distance);
	

	free(list);

	      
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
