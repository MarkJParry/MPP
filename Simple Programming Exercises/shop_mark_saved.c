#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}


struct Shop createAndStockShop()
{
	struct Shop shop = {200};
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s IS A LINE\n", line);
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
		printf("shop index is %d\n",shop.index);
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	/* Close the file now that we are done with it */
	fclose(fp);
	return shop;
}

struct Customer readCustomerOrders()
{
	struct Customer customer = {};
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int lcount = 0;
	int idx = 0;

    fp1 = fopen("orders.csv", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp1)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE\n", line);
		printf("line counter %d\n",lcount++);
		char *cn = strtok(line, ",");
		char *cb = strtok(NULL, ",");
		char *op = strtok(NULL, ",");
		char *oq = strtok(NULL, ",");
		
		int order_quantity = atoi(oq);
		//printf("%d is the order quantity\n", order_quantity);
		
		double budget = atof(cb);
		//printf("%.2f is the budget\n", budget);

		char *cname = malloc(sizeof(char) * 50);
		strcpy(cname, cn);
		//printf("%s is the customer name\n", cname);
		
		char *pname = malloc(sizeof(char) * 50);
		strcpy(pname, op);
		//printf("%s is the ordered product\n", pname);
		
		struct Customer customer = { cname, budget };
		printf("Customer name is %s and their budget is %.2f\n",customer.name,customer.budget);
		
		struct Stock shoppingListItem = { pname,0,order_quantity };

		printf("Product name is %s price is %.2f and the quantity ordered is %d\n",shoppingListItem.product.name, shoppingListItem.product.price, shoppingListItem.quantity);	
		

		//shop.stock[shop.index++] = stockItem;
		//dominic.shoppingList[dominic.index++] = cokeStock;
		customer.shoppingList[customer.index++] = shoppingListItem;
		printf("customer index is %d\n",customer.index);


		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
		
    }
	 /* Close the file now that we are done with it */
	fclose(fp1);
	return customer;
}
void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
	}
}

void printCustomer(struct Customer c)
{
	printf("in print customer function c.index = %d\n", c.index);
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------\n");
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

int main(void) 
{
	
	struct Customer dominic = { "Dominic", 100.0 };
	//
	struct Product coke = { "Can Coke", 1.10 };
	struct Product bread = { "Bread", 0.7 };
	//printProduct(coke);
	//
	struct Stock cokeStock = { "Can Coke",1.10, 20 };
	struct Stock breadStock = { bread, 2 };
	//
	dominic.shoppingList[dominic.index++] = cokeStock;
	dominic.shoppingList[dominic.index++] = breadStock;
	//
	printCustomer(dominic);
	
	//struct Shop shop = createAndStockShop();
	//printShop(shop);
	
	//struct Customer customer = readCustomerOrders();
	//printCustomer(customer);
	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}