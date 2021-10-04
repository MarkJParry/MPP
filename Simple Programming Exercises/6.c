#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int n, sum = 0;
	int product = 1;
	char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter a Number: ");
	scanf("%d", &n);
	printf("Do you want to do product or sum?");
	scanf("%s", choice);
		
	if (strcmp(choice, "product")==0)
	{
		for(int i = 1; i<=n; i++)
		{
			product *= i;
		}
	
		printf("The product of 1 to %d, was %d\n", n, product);
		
	} else if (strcmp(choice, "sum")==0)
	{
		for(int i = 1; i<=n; i++)
		{
			sum += i;
		}
	
		printf("The sum of 1 to %d, was %d\n", n, sum);
		
	}
	return 0;
}