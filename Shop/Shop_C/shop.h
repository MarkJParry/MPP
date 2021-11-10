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
/*
struct Order {
	struct Customer customer;

};
*/
//struct Customer customer;

void print_menu(){

	printf( "+================================+\n");
	printf( "|          Shop Menu             |\n");
	printf( "+================================+\n");
	printf( "|1. Add Customer Order           |\n");
	printf( "|2. Load Customer Order from csv |\n");
	printf( "|3. Process Customer Order       |\n");
	printf( "|4. Add Stock                    |\n");
	printf( "|5. Change Price                 |\n");
	printf( "|6. Change Budget                |\n");
	printf( "|7. View Shop                    |\n");
	printf( "|8. View Customer Order          |\n");
	printf( "|9. Quit                         |\n");
	printf( "+================================+\n");
}

void prtc(){
	printf("Press the return key to continue\n");
	char input[3];
	fgets(input,3,stdin);
	system("clear");
	print_menu();
}


float get_product_price(struct Shop s, char *pname){
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(pname,s.stock[i].product.name) == 0)
        {
		return s.stock[i].product.price;
		break;
        //printProduct(s.stock[i].product);
		//printf(" %3d |\n", s.stock[i].quantity);
        }
	}
	return 0;
}

struct Stock get_product_details(struct Shop* s, char *pname){
	int found = 0;
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		found = 1;
		return s->stock[i];
		break;
        //printProduct(s.stock[i].product);
		//printf(" %3d |\n", s.stock[i].quantity);
        }
	}
	if (found != 1){
		printf("Product not found\n");
	}
	
}
void change_price(struct Shop* s){
	char input[50];
	printf("Enter  product for price change:\n");
	fgets(input,50,stdin);
	//strip the return character form the input
	char *pn = strtok(input,"\n");
	char *pname = malloc(sizeof(char) * 50);
	strcpy(pname, pn);
	int found = 0;
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		printf("Product %s is currently priced %3.2f\n",pname,s->stock[i].product.price);
		printf("Enter the new price:\n");
		char input[10];
		fgets(input,10,stdin);
		float pprice = atof(input);
		s->stock[i].product.price = pprice;
		printf("Product %s is now priced %3.2f\n",pname,s->stock[i].product.price);
		found = 1;
		break;
        //printProduct(s.stock[i].product);
		//printf(" %3d |\n", s.stock[i].quantity);
        }

	

	}
	if (found != 1){
	printf("Product %s not found",pname);
	}
	return;
}
//struct Shop add_stock(struct Shop s1){
void add_stock(struct Shop* s1){
	printf("Shop index is %d\n",s1->index);

	char input[50];
	printf("Enter a product:\n");
	fgets(input,50,stdin);
	//strip the return character form the input
	char *pn = strtok(input,"\n");
	char *pname = malloc(sizeof(char) * 50);
	strcpy(pname, pn);

	printf("Enter the price:\n");
	fgets(input,10,stdin);
	float pprice = atof(input);
	printf("Enter the quantity:\n");
	fgets(input,10,stdin);
	int pqty = atoi(input);
	printf("You entered %s for name, %3.2f for price, %d for quantity\n",pname,pprice,pqty);
	struct Product product = { pname, pprice };
	struct Stock stockItem = { product, pqty };
	s1->stock[s1->index++] = stockItem;
	printf("shop index is %d\n",s1->index);
	printf("Product %s Price %.2f Quantity %d added to shop stock\n\n", pname, pprice, pqty);
	//printShop(s1);
	prtc();
	//return s1;
}

struct Customer addCustomerOrder(struct Shop* shop)
{
	system("clear");
	printf("Add Customer Order\n");
	struct Customer newcustomer ={};
	int counter = 0;
	int finished = 0;
    while (finished != -1){


		counter++;
		if (counter == 1)
		//add name & budget
			{
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

		//add order lines
			{
			char input[50];
			printf("Enter a product or -1 to finish:\n");
			fgets(input,50,stdin);
			//check for -1 to finish
			if (strcmp(input,"-1\n") == 0){	
				finished = -1;
				break;
				}
			//strip the return character form the input
			char *pn = strtok(input,"\n");
			char *pname = malloc(sizeof(char) * 50);
			strcpy(pname, pn);
			
			struct Stock s = get_product_details(shop, pname);
			printf("Found product %s price %3.2f  quantity in stock %d\n",s.product.name,s.product.price,s.quantity);
			
			//char input[10];
			printf("Enter the quantity to order:\n");
			fgets(input,10,stdin);
			int order_quantity = atoi(input);
			//how do I get product price from the earlier load of stock to appear here instead of zero(don't want the price in the custs csv)?
			//float pprice = get_product_price(shop, pname);
			
			struct Product product = {pname, s.product.price};
			struct Stock shoppingListItem = { product, order_quantity };
			newcustomer.shoppingList[newcustomer.index++] = shoppingListItem;
			printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", pname, s.product.price, order_quantity);
  			}
	}
	 /* Close the file now that we are done with it */

	printf("Finished Loading Order - ");
	prtc();
	//system("clear");
	return newcustomer;
}

void printProduct(struct Product p)
{
	//printf("Product Name: %s Price: %.2f ", p.name, p.price);
	printf("| %s \t %3.2f  \t ", p.name, p.price);

}

void printShop(struct Shop s)
{
	printf("Shop has %3.2f in cash and the following products in stock:\n", s.cash);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf(" %3d |\n", s.stock[i].quantity);
	}
	printf("-------------------------------\n\n");
	prtc();
}

void printCustomer(struct Customer c)
{
	printf("Customer Name: %s  Budget: %3.2f\n", c.name, c.budget);
	printf("Order Details:\n");
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
