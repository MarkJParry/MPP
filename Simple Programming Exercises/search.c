#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};


struct Product add_products()
{
char* name;
double price;
for (int i = 0; i < 4; i++)
    {
        printf("Enter data for product %d\n", i + 1);
        printf("Enter product name, price\n");
        scanf("%s %lf", name, &price);
        struct Product product[i] = {name, price};

    }
}




int main(void) 
{
    struct Product product = add_products();
    char input[10];
    printf("Enter product name to search for its price:\n");
    scanf("%s", &input); 
	
    return 0;
}