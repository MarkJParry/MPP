#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

struct Product {
	char* name;
	double price;
};

struct Stock {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct Stock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct Stock shoppingList[10];
	int index;

};

struct OrderBook {
    struct Customer order[20];
    int index;
};

struct data_File {
    int f_number;
	char* f_name;
};

struct csv_Folder {
	struct data_File data_file[20];
	int index;
};


void print_menu(){

	system("clear");

	printf( "+================================+\n");
	printf( "|          Shop Menu             |\n");
	printf( "+================================+\n");
	printf( "|1. Add Customer Order           |\n");
	printf( "|2. Load Customer Order from csv |\n");
	printf( "|3. Process Customer Order       |\n");
	printf( "|4. Add Stock                    |\n");
	printf( "|5. Change Price                 |\n");
	printf( "|6. Modify Order                 |\n");
	printf( "|7. View Shop                    |\n");
	printf( "|8. View Customer Order          |\n");
	printf( "|9. Quit                         |\n");
	printf( "+================================+\n");
}

void prtc(){
	printf("Press the return key to continue\n");
	char input[3];
	fgets(input,3,stdin);
	//system("clear");
	print_menu();
}
//the below #include is here as the compiler throws a wobble if above at start of file - to do with order of functions
#include "shop.h"

int main(void) 
{
	/*
	#ifdef __unix__
 		printf("Linux OS\n");
		system("clear");
	#else
		#ifdef  _WIN32
			printf("Windows OS");
		 	system("cls");
		#endif	
	#endif
	*/
	struct OrderBook ob = {};
	struct Shop shop = createAndStockShop();
	/*
	struct Customer customer = readCustomerOrder(shop);
	printf("Just finished loading shop and an order\n");
	ob.order[ob.index++] = customer;
	ob.OrderNo = ob.index;
	*/
	
	/*
	initialise structures to zero - do i need this?
	struct Shop shop = {0,0,0};
	struct Customer customer = {"",0,0,0};
	struct Stock stock = {0,0};
	struct Stock shoppingList = {0,0};
	struct Product product = {"",0};
	*/
	int choice = -1;
	char input[3];
	print_menu();
	while (choice != 9){
		fflush(stdin);
		printf("\nPlease choose an option ");
		fgets(input,3,stdin);
		choice = atoi(input);

		if (choice == 1)
		{
			struct Customer newcustomer = addCustomerOrder(shop);
			ob.order[ob.index++] = newcustomer;
			//ob.OrderNo = ob.index;
			//printf("index: %d", ob.index);
			printCustomer(newcustomer);
			//struct Shop shop = createAndStockShop();
			//printShop(shop);
		} else if (choice == 2){
			//printf("The user pressed 2\n");
			//printf("Loading Customer Order\n");
			//struct Shop shop;
			struct Customer customerfromcsv = readCustomerOrder(shop);
			//printf("Returned: %s\n",customerfromcsv.name);
			if (customerfromcsv.name != NULL)
				{
				ob.order[ob.index++] = customerfromcsv;
				//ob.OrderNo = ob.index;
				printCustomer(customerfromcsv);
				}
			//printf("index: %d", ob.index);
			
		} else if (choice == 3){
			int otp = get_order_to_process(ob);
			//printf("Order to process:%d\n",otp);
			if (otp != -1)
				{
				process_order(&ob.order[otp],&shop);
				}
			//process_order(otp);
			
			//printf("The user pressed 3\n");
		}  else if (choice == 4){
			//printf("The user pressed 4\n");
			add_stock(&shop);
		} else if (choice == 5){
			//printf("The user pressed 5\n");
			change_price(&shop);
		} else if (choice == 6){
			//change_budget();
			printf("The user pressed 6\n");
		} else if (choice == 7){
			//printf("The user pressed 7\n");
			//struct Shop shop;
			printShop(shop);
		} else if (choice == 8){
			//struct Customer customer;
			//printf("The user pressed 8\n");
			//printf("index: %d", ob.index);
			if (ob.index == 0)
				{
				printf("No orders have been added yet - option 1 will allow order entry, option 2 allows upload from a csv file\n");
				}
			else
				{
				print_menu();
				for (int i = 0; i < ob.index; i++)
					{
					printf("Order Number: %d\n",i+1);
					printCustomer(ob.order[i]);
					}
				}
		}
	}
	printf("Thank you for your custom - call again soon\n");

	/*struct Shop shop = createAndStockShop();
	printShop(shop);
	printf("Loading Customer Order\n");
	struct Customer customer = readCustomerOrder(shop);
	printCustomer(customer);*/
	
    return 0;
}
