// newshop.h
/*
#ifdef __unix__
	printf("Linux OS\n");
	system("clear");
#else
	#ifdef  _WIN32
		printf("Windows OS");
	 	system("cls");
	#endif	
#endif
*/
#ifndef NEWSHOP_H  
#define NEWSHOP_H 


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

struct OrderBook {
    struct Customer order[20];
    int index;
};

struct data_File {
    int f_number;
	char* f_name;
};

struct csv_Folder {
	struct data_File data_file[20];
	int index;
};

void prtc();
struct Shop createAndStockShop();
void printProduct();
void printShop();
void printCustomer();
void add_stock();
void change_price();
struct OrderBook add_customer();
void process_order();
void modify_order();
int get_order_to_process();
int get_line_to_modify();
#endif