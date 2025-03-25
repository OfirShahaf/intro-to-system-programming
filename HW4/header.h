#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TABLES 50

typedef struct Prod {

	char* ProductName;
	float Price;
	int Quantity;
	struct Prod* next;

}Prod, * PProd;

typedef struct Table {

	char* ProductName;
	float Price;
	int Quantity;
	struct Table* next;
	Prod* head ;

}Table, * PTable;


//Function that create a linked list of all the dishes and save them in manager list 
PProd CreateProducts(FILE* in, Prod* head);  //Func_1
//Function that gets a pointer to the top of the list and updating quantity to the required prodact 
PProd addItem(Prod* head, char* prodName, int quantity);//Func_2
//Function that allaw to open a order to table ,the function gets a pointer to "kitchen" (top manager list of al the products) 
void OrderItem(Prod* kitchen, PTable* tableList, char* prodName, int quantity, int tableNumber);//Func_3
//Function that cancell the last order of the table and updating the quantity in the kitchen 
PTable RemoveItem(PTable tableList, PTable currentTable, int tableNumber);//Func_4
//Function that "close" the table by sum of all the products and calculate the bil and the tip 
void RemoveTable(PTable* tableList, int tableNumber);//Func_5
void ErrorMsg(char* msg);
void deleteKitchen(PProd head);