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
	int order_no;
    struct Customer customer;
    struct Stock order_line[10];
    int index;
};



struct ShopOrder {
    struct Order order[20];
    int index;
};


void print_product(struct Product p)
{
	//printf("Product Name: %s Price: %.2f ", p.name, p.price);
	printf("| %s \t %3.2f  \t ", p.name, p.price);

}

void print_order(struct Order o)
{
	
    printf("Order No: %d Customer: %s Budget: %3.2f\n", o.order_no, o.customer.name, o.customer.budget);
    printf("Order Details:\n");
        for (int i = 0; i < o.index+1; i++)
        {
            print_product(o.order_line[i].product);
            printf(" Order Qty: %d\n",o.order_line[i].quantity);
            //printf("Order No: %d Order Items: %d Total Cost: %3.2f\n",sc.customer[i].order->order_no,sc.customer[i].index,0.0);
        }
    
}

void print_shop(struct Shop s)
{
	printf("Shop has %3.2f in cash and the following products in stock:\n", s.cash);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s.index+1; i++)
	{
		print_product(s.stock[i].product);
		printf(" %3d |\n", s.stock[i].quantity);
	}
	printf("-------------------------------\n\n");
	//prtc();
}



int main(void){
    //set up shop and stock
    struct Product Bread = {"Bread",1.50};
    struct Product Cheese = {"Cheese",2.99};
    struct Product Butter = {"Butter",1.99};
    struct Product Pickle = {"Pickle",3.25};

    struct Stock stock1 = {Bread,10};
    struct Stock stock2 = {Cheese,20};
    struct Stock stock3 = {Butter,5};
    struct Stock stock4 = {Pickle,2};

    struct Shop shop = {100.00};
    shop.stock[0] = stock1;
    shop.stock[1] = stock2;
    shop.stock[2] = stock3;
    shop.stock[3] = stock4;

    /* works but editor doesn't like it
    shop.stock[0] = {Bread,10};
    shop.stock[1] = {Cheese,20};
    shop.stock[2] = {Butter,5};
    shop.stock[3] = {Pickle,2};
    */

    shop.cash = 100.00;
    shop.index = 3;

    print_shop(shop);


    //set up customer and order
    
    struct Customer mark = {"Mark",100.00};
    struct Stock order_line_1 = {Bread,3};
    struct Stock order_line_2 = {Cheese,2};
    struct Order order1 = {1};
    order1.customer = mark;
    order1.order_line[0] =  order_line_1;
    order1.order_line[1] =  order_line_2;
    order1.index = 1;
    struct ShopOrder shoporder = {};
    shoporder.order[0] = order1;
    shoporder.index = 0;

    //print_order(order1);

    //set up 2nd order for Mark
    struct Stock order_line_3 = {Bread,3};
    struct Stock order_line_4 = {Butter,2};
    struct Stock order_line_5 = {Pickle,1};
    struct Order order2 ={2};
    order2.customer = mark;
    order2.order_line[0] =  order_line_3;
    order2.order_line[1] =  order_line_4;
    order2.order_line[2] =  order_line_5;
    order2.index = 2;

    shoporder.order[1] = order2;
    shoporder.index += 1;

    //print_order(order2);

    //set up 1st order for Dominic
    struct Customer dominic = {"Dominic",100.00};
    struct Stock order_line_6 = {Cheese,2};
    struct Stock order_line_7 = {Butter,1};
    struct Stock order_line_8 = {Pickle,3};
    struct Stock order_line_9 = {Bread,4};
    struct Order order3 ={3};
    order3.customer = dominic;
    order3.order_line[0] =  order_line_6;
    order3.order_line[1] =  order_line_7;
    order3.order_line[2] =  order_line_8;
    order3.order_line[3] =  order_line_9;
    order3.index = 3;

    shoporder.order[2] = order3;
    shoporder.index += 1;
    
    //print_order(order3);

    for ( int i=0; i <= shoporder.index; i++)
    {
        print_order(shoporder.order[i]);
    }


}



