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
	struct Order order[10];
	int index;
};
struct Order {
	struct Stock orderLine[10];
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
        printf("%s IS A LINE", line);
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
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	/* Close the file now that we are done with it */
	fclose(fp);
	return shop;
}

struct Order readCustomerOrders()
{
	struct Order order = {};
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp1 = fopen("orders.csv", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp1)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s IS A LINE\n", line);
		char *cn = strtok(line, ",");
		char *cb = strtok(NULL, ",");
		char *op = strtok(NULL, ",");
		char *oq = strtok(NULL, ",");
		
		int order_quantity = atoi(oq);
		printf("%d is the order quantity\n", order_quantity);
		
		double budget = atof(cb);
		printf("%.2f is the budget\n", budget);

		char *name = malloc(sizeof(char) * 50);
		strcpy(name, cn);
		printf("%s is the customer name\n", name);
		
		char *product = malloc(sizeof(char) * 50);
		strcpy(product, op);
		printf("%s is the ordered product\n", product);
		struct Customer customer = { name, budget };
		struct Stock orderItem = { product, order_quantity };
		order.orderLine[order.index++] = orderItem;
		printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", customer.name, customer.budget);
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
		
    }
	 /* Close the file now that we are done with it */
	fclose(fp1);
	return order;
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

void printOrder(struct Order o)
{

	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", o.customer.name, o.customer.budget);
	printf("-------------\n");
	for(int i = 0; i < o.index; i++)
	{
		printProduct(o.orderLine[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", o.customer.name, o.orderLine[i].quantity);
		double cost = o.orderLine[i].quantity * o.orderLine[i].product.price; 
		printf("The cost to %s will be €%.2f\n", o.customer.name, cost);
	}
}

int main(void) 
{
	// struct Customer dominic = { "Dominic", 100.0 };
	//
	// struct Product coke = { "Can Coke", 1.10 };
	// struct Product bread = { "Bread", 0.7 };
	// // printProduct(coke);
	//
	// struct ProductStock cokeStock = { coke, 20 };
	// struct ProductStock breadStock = { bread, 2 };
	//
	// dominic.shoppingList[dominic.index++] = cokeStock;
	// dominic.shoppingList[dominic.index++] = breadStock;
	//
	// printCustomer(dominic);
	
	//struct Shop shop = createAndStockShop();
	//printShop(shop);
	
	struct Order order = readCustomerOrders();
	printOrder(order);
	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}