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

struct Order {
	struct Customer customer;

};





// stock csv first line will be the cash for the shop
//all other lines will be products
struct Shop createAndStockShop()
{
	struct Shop shop = {};
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
	return shop;
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

struct Customer readCustomerOrder(struct Shop shop)
{
	struct Customer customer = {};
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
			strcpy(cname, cn);double budget = atof(cb);

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
			printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", pname, 0.0,order_quantity);
  			}
	}
	 /* Close the file now that we are done with it */
	fclose(fp1);
	return customer;
}


void printProduct(struct Product p)
{
	//printf("Product Name: %s Price: %.2f ", p.name, p.price);
	printf("| %s \t %.2f  \t ", p.name, p.price);

}

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash and the following products in stock:\n", s.cash);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf(" %3d |\n", s.stock[i].quantity);
	}
	printf("-------------------------------\n\n");
}

void printCustomer(struct Customer c)
{
	printf("Customer Name: %s  Budget: %.2f\n", c.name, c.budget);
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
	printf("Loading Stock\n");
	struct Shop shop = createAndStockShop();
	printShop(shop);
	printf("Loading Customer Order\n");
	struct Customer customer = readCustomerOrder(shop);
	printCustomer(customer);

	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}