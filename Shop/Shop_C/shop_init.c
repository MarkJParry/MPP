// shop_init.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "newshop.h"

void add_stock(struct Shop* s1){
	//printf("Shop index is %d\n",s1->index);

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
	//printf("You entered %s for name, %3.2f for price, %d for quantity\n",pname,pprice,pqty);
	struct Product product = { pname, pprice };
	struct Stock stockItem = { product, pqty };
	s1->stock[s1->index++] = stockItem;
	//printf("shop index is %d\n",s1->index);
	printf("Product %s, Price %.2f, Quantity %d added to shop stock\n\n", pname, pprice, pqty);
	//printShop(s1);
	//prtc();
	//return s1;
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


void printProduct(struct Product p)
{
	//printf("Product Name: %s Price: %.2f ", p.name, p.price);
	printf("| %s \t %3.2f  \t ", p.name, p.price);

}

void printShop(struct Shop* s)
{
	printf("Shop has %3.2f in cash and the following products in stock:\n", s->cash);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s->index; i++)
	{
		printProduct(s->stock[i].product);
		printf(" %3d |\n", s->stock[i].quantity);
	}
	printf("-------------------------------\n");

}

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
