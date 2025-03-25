#include "header.h"


void ErrorMsg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}


void deleteKitchen(PProd head)
{
	PProd temp = head;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->ProductName);
		free(temp);
	}
}

//the function create a linked list of all the dishes and save them in manager list 
PProd CreateProducts(FILE* manot, Prod* head)
{
	char name[TABLES];
	Prod* kitchen = NULL;
	Prod* tail = NULL;
	Prod* newProd = NULL;
	Prod* temp = NULL;
	int flag;
	int check;

	newProd = (Prod*)malloc(sizeof(Prod));
	while (fscanf(manot, "%s %g %g", name, &newProd->Quantity, &newProd->Price) != EOF)
	{
		temp = head;
		flag = 0;          //if the flas is 0 so the hea empty
		while (temp != NULL)
		{
			if (strcmp(temp->ProductName, name) == 0)
			{
				printf("\nWe already have %s in kitchen\n", name);
				flag = 1;    
			}
			temp = temp->next;
		}
		if (flag == 1)
			continue;
		newProd->ProductName = (char*)malloc(sizeof(char) * strlen(name) + 1); 
		//allocate place in the memmory to the name of the product
		if (newProd->ProductName == NULL)
		{
			deleteKitchen(head);
			ErrorMsg("\nDynamic memory allocation error!!!");  
			//check if the allocation is succeeded
		}
		strcpy(newProd->ProductName, name);
		check = newProd->Quantity - (int)newProd->Quantity;
		if (check != 0)
		{
			printf("\nError, the quantity must be integer!\n");
			continue;
		}
		if (newProd->Price < 0 || newProd->Quantity < 0)
		{
			printf("\nError, you cant enter nagative price/quantity to dish.\n");
			continue;
		}
		newProd->next = NULL;
		if (head == NULL)
			head = newProd;
		else
			tail->next = newProd;
		tail = newProd;
		//allocate memmory to new node in the list
		newProd = (Prod*)malloc(sizeof(Prod));
		if (newProd == NULL)
		{
			deleteKitchen(head);
			ErrorMsg("\nDynamic memory allocation error!");
		}
	}
	printf("\nThe kitchen was created\n");
	return head;
}

//Function that gets a pointer to the top of the list and updating quantity to the required prodact
PProd addItem(PProd* kitchen, char* prodName, int quantity)
{
	Prod* temp = kitchen; //pointer to head of the list 
	if (quantity <= 0)
	{
		printf("\nYou cant add %d products\n", quantity);
		return kitchen;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->ProductName, prodName) == 0)
		{
			temp->Quantity += quantity;
			printf("\n%d %s were added to the kitchen\n", quantity, prodName);
			return kitchen;
		}
		temp = temp->next;
	}
	printf("\nWe dont found %s in the menu\n", prodName);
	return kitchen;
}
//Function that allaw to open a order to table ,the function gets a pointer to "kitchen" (top manager list of al the products) 
void OrderItem(Prod* kitchen, PTable* tableList, char* prodName, int quantity, int tableNumber) {
	Table neworder;
	Prod* temp;
	temp = kitchen;
	if (TABLES < tableNumber)   //check if the table number is legal
	{
		printf("\nCant choose nagative table!\n");
		return;
	}
	while ((temp != NULL) && (strcmp(temp->ProductName, prodName) != 0))  //check if the product is exists in the menu
	{
		temp = temp->next;
	}
	if (temp == NULL)
	{
		printf("\nWe dont found %s in the menu.\n", prodName);
		return;
	}
	
	if (quantity > temp->Quantity)  //check if the quantity of the dish is available 
	{
		printf("\nThere are not enough products in stock.\n");
		return;
	}
	if (quantity <= 0)
	{

		printf("\nYou cant order %d products.\n", quantity);
		return;
	}
	neworder.head= (Prod*)malloc(sizeof(Prod));
	if (neworder.head == NULL)
	{
		deleteKitchen(kitchen);
		
		ErrorMsg("\nDynamic memory allocation error!");
	}
	neworder.head->next = NULL;
	//allocate in the size of the leghnth of the the name of the product 
	neworder.head->ProductName= (char*)malloc(sizeof(char) * strlen(prodName) + 1);
	if (neworder.head->ProductName == NULL)
	{
		free(neworder.head);
		deleteKitchen(kitchen);
		
		ErrorMsg("\nDynamic memory allocation error!");
	}
	strcpy(neworder.head->ProductName, prodName);
	neworder.head->Quantity = quantity;
	kitchen->Quantity = kitchen->Quantity - quantity;
	neworder.head->Price = kitchen->Price;
	if (tableList[tableNumber - 1] == NULL)
		tableList[tableNumber - 1] = neworder.head;
	else
	{
		neworder.head->next = tableList[tableNumber-1];
		tableList[tableNumber - 1] = neworder.head;

	}
	return;
}
//Function that cancell the last order of the table and updating the quantity in the kitchen
PTable RemoveItem(Table* tableList, Table* currentTable, int tableNumber) {
	Prod temp, deleteItem;
	Prod* P_temp;
	if (currentTable != NULL)
	{
		P_temp = (Prod*)malloc(sizeof(Prod));
		if (P_temp == NULL)
		{
			ErrorMsg("\nDynamic memory allocation error!");
		}
		//allocate in the size of the leghnth of the the name of the product 
		temp.ProductName = (char*)malloc(sizeof(char) * strlen(currentTable->ProductName) + 1);
		if (temp.ProductName == NULL)
		{
			free(P_temp);
			ErrorMsg("\nDynamic memory allocation error!");
		}
		strcpy(temp.ProductName, currentTable->ProductName);
		temp.Quantity = currentTable->Quantity;
		temp.Price = currentTable->Price;
		printf("%d %s was returned to the kitchen from table number %d\n", currentTable->Quantity,currentTable->ProductName, tableNumber);
		free(temp.ProductName);
		return currentTable->next;
	}
	else
		printf("The table number %d is not ordered yet\n", tableNumber);
	return currentTable;
}
//Function that "close" the table by sum of all the products and calculate the bil and the tip 
void RemoveTable(Table* tableList, int tableNumber) {
	float bill = 0;
	Prod* temp = NULL;
	if (tableList == NULL)
	{
		printf("table number %d is not ordered yet\n", tableNumber);
	}
	else
	{
		temp = tableList;
		while (temp != NULL)
		{
			printf("%d %s .", temp->Quantity, temp->ProductName);
			bill += temp->Quantity * temp->Price;
			temp = temp->next;
		}
		temp = tableList;
		
		printf("%g nis + %g nis for tips, please!\n",bill, 0.15 * bill);
		deleteKitchen(tableList);
	}

}
