#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shop.h"

// stock csv first line will be the cash for the shop
//all other lines will be products
struct Shop createAndStockShop()
{
    system("clear");
	printf("Loading Shop and Stock from file\n");
	struct Shop shop;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int line_count = 0;

    fp = fopen("../Data/stockcash.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length: %zu with contents: %s", read,line);
		line_count++;
        //printf("%s IS A LINE\n", line);
		if (line_count == 1)
			{
			char *n = strtok(line, ",");
			char *c = strtok(NULL, ",");
			float cash = atof(c);
			shop.cash = cash ;
			printf("Shop has been initialised with opening cash balance of : %.2f\n\n", cash);
			}
		else
			{
			char *n = strtok(line, ",");
			char *p = strtok(NULL, ",");
			char *q = strtok(NULL, ",");
			int quantity = atoi(q);
			double price = atof(p);
			char *name = malloc(sizeof(char) * 50);
			strcpy(name, n);
			struct Product product = { name, price };
			struct Stock stockItem = { product, quantity };
			shop.stock[shop.index++] = stockItem;
			//printf("shop index is %d\n",shop.index);
			printf("Product %s Price %.2f Quantity %d added to shop stock\n\n", name, price, quantity);
			}
	}
	fclose(fp);
	printf("Finished Loading Shop - ");
	prtc();
	return shop;
}


struct Customer readCustomerOrder(struct Shop shop)
{
	system("clear");
	printf("Loading Customer Order from file\n");
	struct Customer customer;
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int line_count = 0;
	/*char *sn = "";
	char *sname = malloc(sizeof(char) * 50);
	strcpy(sname, sn);*/


    fp1 = fopen("../Data/custorder.csv", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp1)) != -1){

        printf("Retrieved line of length %zu: with contents: %s", read,line);
		line_count++;
		if (line_count == 1)
			{
			char *cn = strtok(line, ",");
			char *cb = strtok(NULL, ",");

			char *cname = malloc(sizeof(char) * 50);
			strcpy(cname, cn);
			double budget = atof(cb);

			customer.name = cname;
			customer.budget = budget;
			printf("Customer %s with a budget of %.2f created\n\n", cname, budget);
			}
		else
			{
			char *pn = strtok(line, ",");
			char *oq = strtok(NULL, ",");

			char *pname = malloc(sizeof(char) * 50);
			strcpy(pname, pn);	

			int order_quantity = atoi(oq);
			//how do I get product price from the earlier load of stock to appear here instead of zero(don't want the price in the custs csv)?
			float pprice = get_product_price(shop, pname);
			
			struct Product product = {pname, pprice};
			struct Stock shoppingListItem = { product, order_quantity };
			customer.shoppingList[customer.index++] = shoppingListItem;
			printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", pname, pprice, order_quantity);
  			}
	}
	 /* Close the file now that we are done with it */
	fclose(fp1);
	printf("Finished Loading Order - ");
	prtc();
	system("clear");
	return customer;
}



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

	struct Shop shop = createAndStockShop();
	struct Customer customer = readCustomerOrder(shop);
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
			printCustomer(newcustomer);
			//struct Shop shop = createAndStockShop();
			//printShop(shop);
		} else if (choice == 2){
			//printf("The user pressed 2\n");
			printf("Loading Customer Order\n");
			struct Shop shop;
			struct Customer customer = readCustomerOrder(shop);
			printCustomer(customer);
		} else if (choice == 3){
			//process_order();
			printf("The user pressed 3\n");
		}  else if (choice == 4){
			printf("The user pressed 4\n");
			add_stock(&shop);
		} else if (choice == 5){
			printf("The user pressed 5\n");
			change_price(&shop);
		} else if (choice == 6){
			//change_budget();
			printf("The user pressed 6\n");
		} else if (choice == 7){
			printf("The user pressed 7\n");
			//struct Shop shop;
			printShop(shop);
		} else if (choice == 8){
			//struct Customer customer;
			printf("The user pressed 8\n");
			printCustomer(customer);
		}
	}
	printf("Buh bye\n");

	/*struct Shop shop = createAndStockShop();
	printShop(shop);
	printf("Loading Customer Order\n");
	struct Customer customer = readCustomerOrder(shop);
	printCustomer(customer);*/
	
    return 0;
}
