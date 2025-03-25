#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define N 8   

void histograma(char *str,int num);  //declaration about the functions 


void main3() {
	char str[40];  //define string with maximum 40 chars
	printf("Enter a string pleas: "); 
	scanf("%s", &str);  //input string to str 
	histograma(str, N);  //caling to the function 

}

void histograma(char *str,int num) {   
	int countlist[26] = { 0 }; 
	//build a count list of all the "abc" , and reset all the valuse to "0"
	int i,j, len;
	len = strlen(str);   //the lenght of str 
	for (i = 0; i < len; i++) {  
		if (str[i] == '!')
			break;          //condition that stop the loop when the operator find "!"
		if (str[i] - 'a' < N && str[i] - 'a' >= 0) //if the index value is char between the N first letters 
			countlist[str[i] - 'a'] += 1; // increas the count list in the correct place 
		
	}
	for (i = 0; i < N; i++) {
		printf("\n%c: ", i + (int)'a');//print the letters from 'a' to  N letter 
		for(j = 0; j < countlist[i]; j++) { // print "*" as number of the values in the count list 
			printf("*");  
		}
	}
	
}