// MPP - Week 6 - A Menu in C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void askName()
{
	fflush(stdin);
	printf("What is your name?\n");
	char name[10];
	fgets(name,10,stdin);
	printf("Glad to meet you, %s\n",name);
	return;
}

void print_menu(){

	printf( "+================================+\n");
	printf( "|          Shop Menu             |\n");
	printf( "+================================+\n");
	printf( "|1. Load Shop from csv           |\n");
	printf( "|2. Load Customer Order from csv |\n");
	printf( "|3. Process Customer Order       |\n");
	printf( "|4. Add Stock                    |\n");
	printf( "|5. Change Price                 |\n");
	printf( "|6. Change Budget                |\n");
	printf( "|9. Quit                         |\n");
	printf( "+================================+\n");
}

int main(void) 
{
	#ifdef __unix__
	 	printf("Linux OS\n");
		system("clear");
	#else
		#ifdef  _WIN32
			printf("Windows OS");
	  		system("cls");
	  	#endif	
	#endif
	int choice = -1;
	char input[3];
	print_menu();
	while (choice != 9){
		
		fflush(stdin);
		printf("\nPlease choose an option ");
		fgets(input,3,stdin);
		choice = atoi(input);

		if (choice == 1)
		{
	        	//load_shop();
			printf("The user pressed 1\n");
		} else if (choice == 2){
			//load_order();
			printf("The user pressed 2\n");
		} else if (choice == 3){
			//process_order();
			printf("The user pressed 3\n");
		}  else if (choice == 4){
			//add_stock();
			printf("The user pressed 4\n");
		} else if (choice == 5){
			//change_price();
			printf("The user pressed 5\n");
		} else if (choice == 6){
			//change_budget();
			printf("The user pressed 6\n");
		}
	}
	printf("Buh bye\n");
}
