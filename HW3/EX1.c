#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#define N 8
int isZero(int* arr);
int isNegative(int* arr, int len);  // declaration about the functions  


void main1() {
	int i,arr[N],count = 0,max=0;  //define variables 
	printf("Enter the array: ");
	for (i = 0; i < N; i++)   // loop that input the numbers to arry 
		scanf("%d", &arr[i]);
	while (!isZero(arr)) {   // check condition , the last arry must be all "0" 
		printf("Enter the array: ");  
		for (i = 0; i < N; i++)   
			scanf("%d", &arr[i]);
		count = isNegative(arr, N); // save the leghth return from the arry 
		if (count > max) 
			max = count; // save the longest sequence from all the arrays
	}

	printf("Maximal negative sequence length is: %d", max);  
}

int isNegative(int* arr, int len) {   // function that count the sequence of negative numbers 
	int i, count = 0, max = 0, temp = 0;
	for (i = 0; i < len; i++) {   // loop that pass over the values 
		if (arr[i] < 0) {
			count++; // Increases the counter 
		}
		else {
			if (count > max) {
				max = count;   // check who the longet sequence in  this specific arry 

			}
			count = 0;   //reset the counter when finish sequence 
		}
	}
	return max; 
}

int isZero(int* arr) {  // function that check if all the values in the arry is "0" 
	int i;
	for (i = 0; i < N; i++) {
		if (arr[i] != 0) //condition to check if has a number different from "0"  
			return 0;   
	}
	return 1;  
}
