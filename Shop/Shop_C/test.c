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

struct OrderBook {
    struct Order order_entry[20];
    int index;
};

//struct Order ShopOrder[10];



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

int get_qty_oh(struct Shop *s, char *pname){
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
		return s->stock[i].quantity;
        }
	}
	return 0;
}

int update_qty_oh(struct Shop *s, char *pname,int ord_qty){
	for (int i = 0; i < s->index; i++)
	{
		if (strcmp(pname,s->stock[i].product.name) == 0)
        {
        s->stock[i].quantity -= ord_qty;
		return s->stock[i].quantity;
        }
	}
	return 0;
}

void process_order(struct Order *o,struct Shop *s ){

    printf("Order No: %d Customer: %s Budget: %3.2f\n", o->order_no, o->customer.name, o->customer.budget);
    for (int i = 0; i < o->index+1; i++)
        {
            printf("Processing order line %d\n",i+1);
            float cost_of_line = o->order_line[i].product.price * o->order_line[i].quantity;
            print_product(o->order_line[i].product);
            printf(" Order Qty: %d, Cost: %3.2f\n",o->order_line[i].quantity,cost_of_line);

            //find the product in the shop and change the quantity on hand
            int qty_on_hand = get_qty_oh(s,o->order_line[i].product.name);
            printf("The shop has %d of these in stock\n",qty_on_hand);
            int update_qty_on_hand = update_qty_oh(s,o->order_line[i].product.name,o->order_line[i].quantity);
            printf("The shop now has %d of these in stock\n",update_qty_on_hand);

            //update shop cash and customer budget
            printf("Reducing the customers budget by %3.2f and adding it to shop's cash\n",cost_of_line);
            o->customer.budget -= cost_of_line;
            s->cash += cost_of_line;

        }
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

    struct OrderBook ob = {};
    ob.order_entry[0] = order1;
    ob.index = 0;

    /*struct CustOrder custorder = {};
    custorder.order[0] = order1;
    custorder.index = 0;

    struct ShopCust shopcust = {};
    shopcust.custorder[0] = custorder;
    shopcust.index = 0;

    */

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

    ob.order_entry[1] = order2;
    ob.index = 1;

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

    ob.order_entry[2] = order3;
    ob.index = 2;



    //print_order(order3);

    for ( int i=0; i <= ob.index; i++)
    {
        print_order(ob.order_entry[i]);
    }

    process_order(&ob.order_entry[0],&shop);
    print_order(ob.order_entry[0]);
    print_shop(shop);
/*
    for ( int i=0; i <= shopcust.index; i++)
    {
        for ( int j=0; j <= custorder.index; j++)
        {
            print_order(custorder.order[j]);
        }
    }
*/
}



