#include "header.h"

int main()
{
	int i = 0;
	int option, quantity, tableNumber;
	char prodName[TABLES];
	FILE* ins;
	FILE* manot;
	Prod* head = NULL;
	Prod* kitchen = NULL;
	PTable tableList[TABLES];


	for (i = 0; i < TABLES; i++) {
		tableList[i] = NULL;
	}

	if (!(ins = fopen("Instructions.txt", "r")))
		ErrorMsg("Error! the file 'Instructions' does not exist.");
	while (fscanf(ins, "%d", &option) != EOF)
	{
		switch (option) {
		case 1:
			if (!(manot = fopen("Manot.txt", "r+")))
				ErrorMsg("Error, the file 'Manot' does not found.");
			kitchen = CreateProducts(manot, head);
			fclose(manot);
			break;
		case 2:
			fscanf(ins, "%s %d", prodName, &quantity);
			kitchen = addItem(kitchen, prodName, quantity);
			break;
		case 3:
			fscanf(ins, "%d %s %d", &tableNumber, prodName, &quantity);
			OrderItem(kitchen, tableList, prodName, quantity, tableNumber);
			break;
		case 4:
			fscanf(ins, "%d", &tableNumber);
			tableList[tableNumber - 1] = RemoveItem(tableList, tableList[tableNumber - 1], tableNumber);
			break;
		case 5:
			fscanf(ins, "%d", &tableNumber);
			RemoveTable(tableList[tableNumber - 1], tableNumber);
			break;
		}
	}
	fclose(ins);
	deleteKitchen(kitchen);

	return 0;
}