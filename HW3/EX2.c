#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#define N 4

void printArray(long arr[], int size);
int getFirstDigit(long num);
void buildNum(long* src, int firstDigit);
void left_circulat_shift(long* arr, int size);  //declaration about the functions 

void main() {
	long arr[N];  
	int i;
	printf("Enter %d numbers: ", N);
	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);   //input numbers from user to arry 

	}
	printf("original arry: ");
	printArray(arr, N);
	

	left_circulat_shift(arr, N);
	printf("shifted arry: ");
	printArray(arr, N); // call to the functions 
}

void printArray(long arr[], int size) {  //function that print the arry 
	int i;
	for (i = 0; i < size; i++) { 
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//extract the digit from the number by division the number until the number is only the first digit     
int getFirstDigit(long num) {  
	int firstDigit = 0;
	while (num > 0) {
		firstDigit = num % 10;
		num /= 10;
	}
	return firstDigit;
}

//the funcion take the digit and chain this digit to the next number 
void buildNum(long* src, int firstDigit) {  
	int num = firstDigit, temp = *src;
	int j = 1, temp2 = 0;
	while (temp >= 10) {  // condition that refer to the number until it lower than 10 
		temp2 = temp % 10;  //verable that save the last digit 
		num += (temp2 * pow(10, j));  //chain the digit to the number by multiplication 10 in pow his place 
		j++; // increes the operator, evaluator of the power 
		temp /= 10; //cuts the last digit
	}
	*src = num; //put the number in the correct address 
}

void left_circulat_shift(long* arr, int size) {  
	int i, first, firstTemp;
	firstTemp = getFirstDigit(arr[0]); //put in vrable the value that return from the function  
	for (i = 0; i < size-1; i++) {
	//put in vrable the value that return from the function with his neighbor
		first = getFirstDigit(arr[i + 1]);   
	//call to the function with the address of the correct value in arr and the firs digit of the neighbor
		buildNum(&arr[i], first);   
	}
	//call to the fanction with the adress of the last index and the first digit(of the first index) ...
	//that we put in first temp  
	buildNum(&arr[size - 1], firstTemp); 
}

