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

void searchShop(struct Shop s, char *sname)
{


    printf("Searching Shop for product %s: \n", sname);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(sname,s.stock[i].product.name) == 0)
        {
        printProduct(s.stock[i].product);
		printf(" %3d |\n", s.stock[i].quantity);
        }
	}
	printf("-------------------------------\n\n");
}
int main(void) 
{
	
	
	printf("Loading Stock\n");
	struct Shop shop = createAndStockShop();
	printShop(shop);
    char *sname = malloc(sizeof(char) * 50);
	strcpy(sname,"Bin Bags");
    searchShop(shop, sname);
	
    return 0;
}
