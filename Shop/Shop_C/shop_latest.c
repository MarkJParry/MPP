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


};

struct Order {
	struct Customer customer;
	struct Stock shoppingList[10];
	int index;
};




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
        printf("Retrieved line of length %zu: with contents: %s\n", read,line);
        //printf("%s IS A LINE\n", line);
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

struct Order readCustomerOrders()
{
	struct Order order = {};
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	char *sn = "";
	char *sname = malloc(sizeof(char) * 50);
	strcpy(sname, sn);


    fp1 = fopen("orders.csv", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp1)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE\n", line);
		//printf("line counter %d\n",lcount++);
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
		//printf("%s is the saved name\n", sname);
		
		char *pname = malloc(sizeof(char) * 50);
		strcpy(pname, op);
		//printf("%s is the ordered product\n", pname);
		//int result = strcmp(cname,sname);
		//printf("result is %d\n",result);
		//create a customer every time customer name changes and reset order index to 0
		if (strcmp(cname,sname) != 0 )
			{struct Customer customer = { cname, budget };
			strcpy(sname,cname);
			order.index = 0;
			//printf("sname is %s cname is %s\n",sname,cname);
			printf("Customer name is %s and their budget is %.2f\n",customer.name,customer.budget);}
		//above was restting customer index to 0 for each line


		struct Product product = {pname, 0};
		
		struct Stock shoppingListItem = { product, order_quantity };

		printf("Product name is %s price is %.2f and the quantity ordered is %d\n",shoppingListItem.product.name, shoppingListItem.product.price, shoppingListItem.quantity);	
		
		printf("order index is %d\n",order.index);
		//shop.stock[shop.index++] = stockItem;
		//dominic.shoppingList[dominic.index++] = cokeStock;
		order.shoppingList[order.index++] = shoppingListItem;
		/*printf("slp = %s\n",customer.shoppingList[0].product.name);
		printf("slp = %.2f\n",customer.shoppingList[0].product.price);
		printf("slq = %d\n",customer.shoppingList[0].quantity);
		printf("customer index is %d\n",customer.index);*/


		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
		
    }
	 /* Close the file now that we are done with it */
	fclose(fp1);
	return order;
}

void printProduct(struct Product p)
{
	printf("Product Name: %s Price: %.2f\n", p.name, p.price);
	printf("-------------\n");
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
	printf("Customer Name: %s  Budget: %.2f\n", c.name, c.budget);
	printf("-------------\n");
}

void printOrder(struct Order  o)
{
	//printf("in print order function c.index = %d\n", c.index);
	//printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printCustomer(o.customer);
	printf("-------------\n");
	for(int i = 0; i < o.index; i++)
	{
		printProduct(o.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", o.customer.name, o.shoppingList[i].quantity);
		double cost = o.shoppingList[i].quantity * o.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", o.customer.name, cost);
	}
}

int main(void) 
{
	
	//struct Customer dominic = { "Dominic", 100.0 };
	//
	//struct Product coke = { "Can Coke", 1.10 };
	//struct Product bread = { "Bread", 0.7 };
	//printProduct(coke);
	//
	//struct Stock cokeStock = { "Can Coke",1.10, 20 };
	//struct Stock breadStock = { bread, 2 };
	//
	//dominic.shoppingList[dominic.index++] = cokeStock;
	//dominic.shoppingList[dominic.index++] = breadStock;
	//
	//printCustomer(dominic);
	
	//struct Shop shop = createAndStockShop();
	//printShop(shop);
	
	struct Order order = readCustomerOrders();
	printOrder(order);
	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}