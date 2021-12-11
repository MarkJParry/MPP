#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "newshop.h"



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

int get_choice(){
	char input[3];
	fflush(stdin);
	printf("\nPlease choose an option ");
	fgets(input,3,stdin);
	int choice = atoi(input);
	return choice;
}

//the below #include is here as the compiler throws a wobble if above at start of file - to do with order of functions
//#include "shop.h"

int main(void) 
{
	int choice = -1;

	struct OrderBook ob = {};
	struct Shop shop = createAndStockShop();



	print_menu();


	while (choice != 9){
		int choice = get_choice();

		switch(choice){
			case 1:
				//printf("The user pressed %d\n",choice);
				printf("Option 1 - Add Customer Order\n");

				struct OrderBook ob1 = add_customer(choice,&shop);
				if (ob1.index != 0)
					{
					ob.order[ob.index++] = ob1.order[0];
					}
				break;

			case 2:
				//printf("The user pressed %d\n",choice);
				printf("Option 2 - Load Customer Order from csv\n");
				struct OrderBook ob2 = add_customer(choice,&shop);
				//printf("Returned %d\n",ob2.index);
				if (ob2.index != 0)
					{
					ob.order[ob.index++] = ob2.order[0];
					}
				//printf("ob index:%d\n",ob.index);
				//printf("about to print customer using item returned\n");
				//printCustomer(ob2.order[0]);
				//prtc();
				break;

			case 3:
				//printf("The user pressed %d\n",choice);
				printf("Option 3 - Process Customer Order\n");
				int otp = get_order_to_process(ob);
				//printf("Order to process:%d\n",otp);
				if (otp != -1)
					{
					process_order(&ob.order[otp],&shop);
					}
				prtc();
				break;

			case 4:
				//printf("The user pressed %d\n",choice);
				printf("Option 4 - Add Stock to Shop\n");
				add_stock(&shop);
				prtc();
				break;

			case 5:
				//printf("The user pressed %d\n",choice);
				printf("Option 5 - Change stock product price\n");
				change_price(&shop);
				prtc();
				break;

			case 6:
				//printf("The user pressed %d\n",choice);
				printf("Option 6 - Modify Customer Order\n");
				int otm = get_order_to_process(ob);
				//printf("Order to process:%d\n",otp);
				if (otm != -1)
					{
					modify_order(&ob.order[otm],&shop);
					}
				prtc();
				break;

			case 7:
				//printf("The user pressed %d\n",choice);
				printf("Option 7 - Print Shop\n");
				printShop(&shop);
				prtc();
				break;

			case 8:
				printf("The user pressed %d\n",choice);
				printf("Option 8 - Print Customer\n");
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
				//printCustomer(&ob);
				break;

			case 9:
				//printf("Option 9 - Exit\n");
				printf("Option 9 - Now exiting program\n");

				return choice;
			default:
				//printf("The user pressed %d\n",choice);
				printf("Please enter a number between 1 and 9\n");
				break;
		}
	}

/*		if (choice == 1)
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
	*/

	/*struct Shop shop = createAndStockShop();
	printShop(shop);
	printf("Loading Customer Order\n");
	struct Customer customer = readCustomerOrder(shop);
	printCustomer(customer);*/
	
    return 0;
}
