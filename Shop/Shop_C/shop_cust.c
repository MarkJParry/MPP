// shop_cust.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "newshop.h"


struct csv_Folder get_files()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0; 
    struct csv_Folder csv_folder = {};

    folder = opendir("../Data");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return csv_folder;
    }
   

    while( (entry=readdir(folder)) )
    {

        if(strstr(entry->d_name,"cust") != NULL)
            {
            files++;
            //printf("File %3d: %s\n", files, entry->d_name);
            struct data_File data_file ={};
            data_file.f_number= files;
            data_file.f_name = entry->d_name;
            csv_folder.data_file[csv_folder.index++] = data_file;

            }
    }

    closedir(folder);

    return csv_folder;
}

int validate_input(int choice,int min,int max){
    //printf("Input:%d Min:%d Max:%d\n",choice,min,max);
    int validated = 0;
    if((choice >= min)&&(choice <= max)){
        
        validated = 1;
    }
    else{

        validated = 0;
    }
    return validated;
}

int get_input(){
	char input[4];
	
	fgets(input,4,stdin);
	int choice = atoi(input);
    return choice;
    
}

const char* get_csv_file_name(){
    struct csv_Folder csv_folder = get_files();
    if (csv_folder.index > 0)
        {
        
		printf("The data folder contains the following files:\n");
		printf("-----------------------------------------\n");
		printf("|File Number | File Name                |\n");
		printf("-----------------------------------------\n");

        for(int i = 0;i < csv_folder.index; i++)
            {
            printf("| %3d        | %-24s |\n",csv_folder.data_file[i].f_number,csv_folder.data_file[i].f_name);
            }

		printf("-----------------------------------------\n");
        printf("Please choose a file to upload by inputting its number or enter -1 to exit\n");

        int choice = 0;
        while (choice != -1)
            {
            int choice = get_input();
            //printf("Chosen:%d\n",choice);
            if (choice == -1)
                {
				char *csv_file_name = "";
                return csv_file_name;
                }
            int validated = validate_input(choice,1,csv_folder.index);
            if (validated == 1)
                {
                int idx = choice -1;
                //printf("You have chosen to upload %s\n",csv_folder.data_file[idx].f_name);
				char *csv_file_name = csv_folder.data_file[idx].f_name;
				return csv_file_name;
                //break;
                }
            else
                {
                printf("Please enter a valid file number\n");
                }
            }
        }
    else
        {
        printf("The data folder is empty - please add an order file in csv format to the folder\n");   
        }

    
}

float calculate_order_cost(struct Customer c){
	float total_cost = 0;
	for(int i = 0; i < c.index; i++)
		{
		//printProduct(c.shoppingList[i].product);
		//printf(" %3d \t", c.shoppingList[i].quantity);
		//printf("Quantity Ordered %d\n", c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		total_cost += cost;
		//printf(" %6.2f |\n", cost);
		}
	return total_cost;
}

int get_order_to_process(struct OrderBook ob){
	if (ob.index > 0)
        {
        printf("The order book contains the following orders:\n");
		printf("-----------------------------------------\n");
		printf("|OrderNo| Customer   | Items   | Value  |\n");
		printf("-----------------------------------------\n");
        for(int i = 0;i < ob.index; i++)
          	{
        	printf("| %d\t", i+1);
			printf("| %-11s",ob.order[i].name);
			printf("| %3d     " ,ob.order[i].index);
			float order_value = calculate_order_cost(ob.order[i]);
			printf("| %6.2f |\n",order_value);
           	}
		printf("-----------------------------------------\n");
        printf("Please choose an order to process by inputting its number or enter -1 to exit\n");
        int choice = 0;
        while (choice != -1)
        	{
        	int choice = get_input();
        	//printf("Chosen:%d\n",choice);
        	if (choice == -1)
            	{
				//char *csv_file_name = "";
                //return csv_file_name;
                return -1;
                }
            int validated = validate_input(choice,1,ob.index);
            if (validated == 1)
            	{
            	int idx = choice -1;
               	printf("You have chosen to process order no: %d\n",choice);
				//char *csv_file_name = csv_folder.data_file[idx].f_name;
				return idx;
            	//break;
                }
            else
                {
                printf("Please enter a valid order number\n");
                }
            }
        }
    else
        {
        printf("No orders have been added yet - option 1 will allow order entry, option 2 allows upload from a csv file\n");
		return -1;   
        }

}
int get_qty_oh(struct Shop *s, char *pname){
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		return s->stock[i].quantity;
        }
	}
	return 0;
}

int update_qty_oh(struct Shop *s, char *pname,int ord_qty){
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
        s->stock[i].quantity -= ord_qty;
		return s->stock[i].quantity;
        }
	}
	return 0;
}
/*
int update_order_qty(int ord_qty){
	// no need to search as will already have order and line
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
        s->stock[i].quantity -= ord_qty;
		return s->stock[i].quantity;
        }
	}
	return 0;
}
*/


float get_product_price(struct Shop *s, char *pname){
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		return s->stock[i].product.price;
		break;
        }
	}
	return 0;
}





struct Customer readCustomerOrder(struct Shop *shop)
{
	//printf("Loading Customer Order from file\n");
	struct Customer customer ={};
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int line_count = 0;
	const char *csv_file_name = get_csv_file_name();
	if (csv_file_name != "")
		{
		printf("You have chosen to upload csv file:%s\n",csv_file_name);
		}
	else
		{
		return customer;
		}
	
	char csv_path[8] = "../Data/";

	char *csv_full_file_name = malloc(sizeof(char) * 50);

	strcpy(csv_full_file_name, csv_path);

	strcat(csv_full_file_name,csv_file_name);
	
	//printf("File name %s\n",csv_full_file_name);
	//prtc();
	
	fp1 = fopen(csv_full_file_name, "r");
	
    //fp1 = fopen("../Data/custorderMark.csv", "r");
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
	return customer;
}







int  get_product_details( struct Shop *s, char *pname){

	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		printf("Found product %s price %3.2f  quantity in stock %d\n",s->stock[i].product.name,s->stock[i].product.price,s->stock[i].quantity);
		return i;
        }
	}	
	printf("Product %s not found\n",pname);
	return -1;
	


}


struct Customer addCustomerOrder(struct Shop *shop)
{
	//system("clear");
	printf("Add Customer Order\n");
	struct Customer newcustomer ={};
	float cost_of_order = 0.0;
	int counter = 0;
	int finished = 0;
	float budget =0.0;
    while (finished != -1)
		{
		counter++;
		if (counter == 1)
			{
			//add name & budget
			char input[50];
			printf("Enter customer name:\n");
			fgets(input,50,stdin);

			char *cn = strtok(input, "\n");
			char *cname = malloc(sizeof(char) * 50);
			strcpy(cname, cn);

			printf("Enter customer budget:\n");
			fgets(input,50,stdin);
			double budget = atof(input);

			newcustomer.name = cname;
			newcustomer.budget = budget;
			printf("Customer %s with a budget of %.2f created\n\n", cname, budget);
			}
		else
			{
			//add order lines	
			char input[50];
			printf("Enter a product or -1 to finish:\n");
			fgets(input,50,stdin);
			//check for -1 to finish
			if (strcmp(input,"-1\n") == 0)
				{	
				finished = -1;
				break;
				}
			//strip the return character form the input
			char *pn = strtok(input,"\n");
			char *pname = malloc(sizeof(char) * 50);
			strcpy(pname, pn);

			//check to see if product exits
			int found = get_product_details(shop, pname);

			if (found != -1)
				{
				//char input[10];
				printf("Enter the quantity to order:\n");
				fgets(input,10,stdin);
				int order_quantity = atoi(input);
				//check if enough stock to fulfil this line
				if (order_quantity <= shop->stock[found].quantity)
					{
					float pprice = get_product_price(shop, pname);
					cost_of_order += (order_quantity * pprice);
					//check to see if over budget by adding this line to order
					if (cost_of_order <= newcustomer.budget)
						{
						struct Product product = {pname, pprice};
						struct Stock shoppingListItem = { product, order_quantity };
						newcustomer.shoppingList[newcustomer.index++] = shoppingListItem;
						printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", product.name, product.price, order_quantity);
						}
					else{
						printf("The cost %3.2f of the order exceeds the budget %3.2f\n",cost_of_order,newcustomer.budget);
						printf("Line not added to the order\n");
						//remove this line from the cost of the order
						cost_of_order -= (order_quantity * pprice);
						}
					}							
				else{
					printf("There is insufficient stock of %s to fulfil this line\n", pname);
					}
				}
  			}
	}
	 /* Close the file now that we are done with it */
    //struct OrderBook ob = {};
    
	printf("Finished Loading Order - ");
	prtc();
	//system("clear");
	return newcustomer;
}

void printCustomer(struct Customer c)
{
	//printf("ob ind3ex: %d",ob.index);
	printf("Customer Name: %s  Budget: %3.2f\n", c.name, c.budget);
	//printf("Order No:%d\tOrder  Details:\n",i);
	printf("-----------------------------------------\n");
	printf("|Product Name | Price | OrderQty | Cost |\n");
	printf("-----------------------------------------\n");
	double total_cost = 0;

	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf(" %3d \t", c.shoppingList[i].quantity);
		//printf("Quantity Ordered %d\n", c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		total_cost += cost;
		printf(" %6.2f |\n", cost);
	}
	printf("-----------------------------------------\n");
	printf("| Total Cost of Order:          €%6.2f |\n",total_cost);
	printf("-----------------------------------------\n");
	if (total_cost > c.budget){
		printf("Warning - Order exceeds Customer Budget by €%5.2f\n", (total_cost - c.budget));
		}
	prtc();
	
}

void process_order(struct Customer *c,struct Shop *s ){
	//printf("Order No: %d Customer: %s Budget: %3.2f\n", o->order_no, o->customer.name, o->customer.budget);
    for (int i = 0; i < c->index; i++)
        {
            printf("Processing order line %d\n",i+1);
            float cost_of_line = c->shoppingList[i].product.price * c->shoppingList[i].quantity;
            printProduct(c->shoppingList[i].product);
            printf(" Order Qty: %d, Cost: %3.2f\n",c->shoppingList[i].quantity,cost_of_line);

            //find the product in the shop and change the quantity on hand
            int qty_on_hand = get_qty_oh(s,c->shoppingList[i].product.name);
            printf("The shop has %d of these in stock\n",qty_on_hand);
            int update_qty_on_hand = update_qty_oh(s,c->shoppingList[i].product.name,c->shoppingList[i].quantity);
            printf("The shop now has %d of these in stock\n",update_qty_on_hand);

            //update shop cash and customer budget
            printf("Reducing the customers budget by %3.2f and adding it to shop's cash\n",cost_of_line);
            c->budget -= cost_of_line;
            s->cash += cost_of_line;

        }
}
struct OrderBook add_customer(int choice, struct Shop *shop){
	//printf("In add customer function  choice: %d\n",choice);
	if (choice == 1){
		struct OrderBook ob1 ={};
		struct Customer newcustomer = addCustomerOrder(shop);
		if (newcustomer.name != NULL)
			{
			ob1.order[ob1.index++] = newcustomer;
			printCustomer(newcustomer);
			}
		return ob1;

	}
	else if (choice == 2){
		struct OrderBook ob2 ={};
		struct Customer newcustomer = readCustomerOrder(shop);
		if (newcustomer.name != NULL)
			{
			ob2.order[ob2.index++] = newcustomer;
			printCustomer(newcustomer);
			}
		return ob2;
	}
	
}
int get_line_to_modify(struct Customer *c ){
	if (c->index > 0)
        {
        printf("The order contains the following lines:\n");
		printf("------------------------------------\n");
		printf("|LineNo | Item         | Order Qty |\n");
		printf("------------------------------------\n");
        for(int i = 0;i < c->index; i++)
          	{
        	printf("| %d\t", i+1);
			printf("| %-13s",c->shoppingList[i].product.name);
			printf("| %3d       |\n" ,c->shoppingList[i].quantity);
			//float order_value = calculate_order_cost(ob.order[i]);
			//printf("| %6.2f |\n",order_value);
           	}
		printf("------------------------------------\n");
        printf("Please choose a line item to modify by inputting its number or enter -1 to exit\n");
        int choice = 0;
        while (choice != -1)
        	{
        	int choice = get_input();
        	//printf("Chosen:%d\n",choice);
        	if (choice == -1)
            	{
				//char *csv_file_name = "";
                //return csv_file_name;
                return -1;
                }
            int validated = validate_input(choice, 1, c->index);
            if (validated == 1)
            	{
            	int idx = choice -1;
               	printf("You have chosen to modify order line no: %d\n",choice);
				//char *csv_file_name = csv_folder.data_file[idx].f_name;
				return idx;
            	//break;
                }
            else
                {
                printf("Please enter a valid order line number\n");
                }
            }
        }
    else
        {
        printf("No lines have been added to this order yet - option 1 will allow order entry, option 2 allows upload from a csv file\n");
		return -1;   
        }
}

void modify_order(struct Customer *c,struct Shop *s){
	printf("In modify order\n");
	printf("index:%d\n",c->index);
	int ltm = get_line_to_modify(c);
	if (ltm != -1)
		{
		char input[50];
		printf("Enter the new order quantity:\n");
		fgets(input,10,stdin);
		int nqty = atoi(input);
		c->shoppingList[ltm].quantity = nqty;
		}
	prtc();
}