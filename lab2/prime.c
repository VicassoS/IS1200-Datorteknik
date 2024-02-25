/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.

 File modified: 2022-02-08
 By Viggo Schütt Lab 2 assignment 2
*/


#include <stdio.h>

int is_prime(int n){
  
	// returns 1 if n is a prime number else return 0.
	
	int prime = 1;
	for (long i = 2; i * i <= n; i++){	// i * i < n same as i < sqrt(n)
	
		if (n % i == 0 || n <= 1){
			prime = 0;
			break;		// avslutar loop om den finner ett delbart tal
		}	
	}
	return prime;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}


