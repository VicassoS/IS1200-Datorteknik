/*
 * pointer.c
 * Last changed: 2020-02-09
 * By Viggo Schütt for lab 2 assignment 4
 */


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

	// declaring list1, list2, count

int list1[20]; 						// reserve 80 bytes in list1 and list2 - 1 int is 4 bytes --> [20]
int list2[20];
int count = 0;

void copycodes(char* text, int* list, int* counter){ 

							// pointers ökar med 1 betyder att de kollar på nästa datatyp i sekvensen
	while (*text != '\0') {				// do while pointer of string != null character (end of string) - ex. vid avreferenserar 

		*list = *text; 				// sw	$t0, 0($a1) - 
		*text++;				// addi $a0, $a0, 1
		*list++;				// *list++ ökar med 4 bytes 
		(*counter)++;				// counter ökar med 1 - parentes krävs för att öka korrekt
							// avreferenser när lb eller lw används i assembly (laddar in värde)
	}
}

void work (){	
	
	// calls on copycodes - gets text1 etc as they are global

	copycodes(text1, list1, &count);		// &count - addresen för vad pekaren ska peka på
	copycodes(text2, list2, &count);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);		
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));		// kan anta att datorn är little endian då den skriver ut värdet LSB adressen först
  									// syns i utskrift då den börjar med 0x23
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
