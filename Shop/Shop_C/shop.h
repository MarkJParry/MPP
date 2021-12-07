struct csv_Folder get_files()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0; 
    struct csv_Folder csv_folder = {};

    folder = opendir("../Data");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return csv_folder;
    }
   

    while( (entry=readdir(folder)) )
    {

        if(strstr(entry->d_name,"cust") != NULL)
            {
            files++;
            //printf("File %3d: %s\n", files, entry->d_name);
            struct data_File data_file ={};
            data_file.f_number= files;
            data_file.f_name = entry->d_name;
            csv_folder.data_file[csv_folder.index++] = data_file;

            }
    }

    closedir(folder);

    return csv_folder;
}

int validate_input(int choice,int min,int max){
    //printf("Input:%d Min:%d Max:%d\n",choice,min,max);
    int validated = 0;
    if((choice >= min)&&(choice <= max)){
        
        validated = 1;
    }
    else{

        validated = 0;
    }
    return validated;
}

int get_input(){
	char input[4];
	
	fgets(input,4,stdin);
	int choice = atoi(input);
    return choice;
    
}

const char* get_csv_file_name(){
    struct csv_Folder csv_folder = get_files();
    if (csv_folder.index > 0)
        {
        printf("The data folder contains the following files:\n");
        for(int i = 0;i < csv_folder.index; i++)
            {
            printf("File %3d: %s\n",csv_folder.data_file[i].f_number,csv_folder.data_file[i].f_name);
            }
        printf("Please choose a file to upload by inputting its number or enter -1 to exit\n");
        int choice = 0;
        while (choice != -1)
            {
            int choice = get_input();
            //printf("Chosen:%d\n",choice);
            if (choice == -1)
                {
				char *csv_file_name = "";
                return csv_file_name;
                }
            int validated = validate_input(choice,1,csv_folder.index);
            if (validated == 1)
                {
                int idx = choice -1;
                printf("You have chosen to upload %s\n",csv_folder.data_file[idx].f_name);
				char *csv_file_name = csv_folder.data_file[idx].f_name;
				return csv_file_name;
                //break;
                }
            else
                {
                printf("Please enter a valid file number\n");
                }
            }
        }
    else
        {
        printf("The data folder is empty - please add an order file in csv format to the folder\n");   
        }

    
}

int get_order_to_process(struct OrderBook ob){
	if (ob.index > 0)
        {
        printf("The order book contains the following orders:\n");
        for(int i = 0;i < ob.index; i++)
          	{
        	printf("Order Number: %d\n", i+1);
           	}
        printf("Please choose an order to process by inputting its number or enter -1 to exit\n");
        int choice = 0;
        while (choice != -1)
        	{
        	int choice = get_input();
        	//printf("Chosen:%d\n",choice);
        	if (choice == -1)
            	{
				//char *csv_file_name = "";
                //return csv_file_name;
                return -1;
                }
            int validated = validate_input(choice,1,ob.index);
            if (validated == 1)
            	{
            	int idx = choice -1;
               	printf("You have chosen to process order no: %d\n",idx);
				//char *csv_file_name = csv_folder.data_file[idx].f_name;
				return idx;
            	//break;
                }
            else
                {
                printf("Please enter a valid order number\n");
                }
            }
        }
    else
        {
        printf("The order book is empty - please add an order  via option 1 or 2\n");
		return -1;   
        }

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


float get_product_price(struct Shop s, char *pname){
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(pname,s.stock[i].product.name) == 0)
        {
		return s.stock[i].product.price;
		break;
        }
	}
	return 0;
}

/*
struct Order {
	struct Customer customer;

};
*/
//struct Customer customer;
// stock csv first line will be the cash for the shop
//all other lines will be products
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


struct Customer readCustomerOrder(struct Shop shop)
{
	//system("clear");
	printf("Loading Customer Order from file\n");
	struct Customer customer ={};
    FILE *fp1;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int line_count = 0;
	/*char *sn = "";
	char *sname = malloc(sizeof(char) * 50);
	strcpy(sname, sn);*/


	// this is causing stack overflow somewhere? - solved by malloc
	const char *csv_file_name = get_csv_file_name();
	if (csv_file_name != "")
		{
		printf("csv file:%s\n",csv_file_name);
		prtc();
		}
	else
		{
		return customer;
		}
	
	char csv_path[8] = "../Data/";

	char *csv_full_file_name = malloc(sizeof(char) * 50);

	strcpy(csv_full_file_name, csv_path);

	strcat(csv_full_file_name,csv_file_name);
	
	//printf("File name %s\n",csv_full_file_name);
	prtc();
	
	fp1 = fopen(csv_full_file_name, "r");
	
    //fp1 = fopen("../Data/custorderMark.csv", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp1)) != -1){

        printf("Retrieved line of length %zu: with contents: %s\n", read,line);
		line_count++;
		if (line_count == 1)
			{
			char *cn = strtok(line, ",");
			char *cb = strtok(NULL, ",");

			char *cname = malloc(sizeof(char) * 50);
			strcpy(cname, cn);
			double budget = atof(cb);

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
			printf("Product %s Price %.2f Quantity %d added to Customer Order\n", pname, pprice, order_quantity);
  			}
	}
	 /* Close the file now that we are done with it */
	fclose(fp1);
	//struct OrderBook ob = {};
    //ob.order[ob.index++] = customer;
	printf("Finished Loading Order - ");
	prtc();
	//system("clear");
	return customer;
	//return;
}







int  get_product_details(struct Shop s, char *pname){

	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(pname,s.stock[i].product.name) == 0)
        {
		printf("Found product %s price %3.2f  quantity in stock %d\n",s.stock[i].product.name,s.stock[i].product.price,s.stock[i].quantity);
		return i;
        }
	}	
	printf("Product %s not found\n",pname);
	return -1;
	


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

//struct Shop add_stock(struct Shop s1){
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
	prtc();
	//return s1;
}

struct Customer addCustomerOrder(struct Shop shop)
{
	//system("clear");
	printf("Add Customer Order\n");
	struct Customer newcustomer ={};
	float cost_of_order = 0.0;
	int counter = 0;
	int finished = 0;
	float budget =0.0;
    while (finished != -1)
		{
		counter++;
		if (counter == 1)
			{
			//add name & budget
			char input[50];
			printf("Enter customer name:\n");
			fgets(input,50,stdin);

			char *cn = strtok(input, "\n");
			char *cname = malloc(sizeof(char) * 50);
			strcpy(cname, cn);

			printf("Enter customer budget:\n");
			fgets(input,50,stdin);
			double budget = atof(input);

			newcustomer.name = cname;
			newcustomer.budget = budget;
			printf("Customer %s with a budget of %.2f created\n\n", cname, budget);
			}
		else
			{
			//add order lines	
			char input[50];
			printf("Enter a product or -1 to finish:\n");
			fgets(input,50,stdin);
			//check for -1 to finish
			if (strcmp(input,"-1\n") == 0)
				{	
				finished = -1;
				break;
				}
			//strip the return character form the input
			char *pn = strtok(input,"\n");
			char *pname = malloc(sizeof(char) * 50);
			strcpy(pname, pn);

			//check to see if product exits
			int found = get_product_details(shop, pname);

			if (found != -1)
				{
				//char input[10];
				printf("Enter the quantity to order:\n");
				fgets(input,10,stdin);
				int order_quantity = atoi(input);
				//check if enough stock to fulfil this line
				if (order_quantity <= shop.stock[found].quantity)
					{
					float pprice = get_product_price(shop, pname);
					cost_of_order += (order_quantity * pprice);
					//check to see if over budget by adding this line to order
					if (cost_of_order <= newcustomer.budget)
						{
						struct Product product = {pname, pprice};
						struct Stock shoppingListItem = { product, order_quantity };
						newcustomer.shoppingList[newcustomer.index++] = shoppingListItem;
						printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", product.name, product.price, order_quantity);
						}
					else{
						printf("The cost %3.2f of the order exceeds the budget %3.2f\n",cost_of_order,newcustomer.budget);
						printf("Line not added to the order\n");
						//remove this line from the cost of the order
						cost_of_order -= (order_quantity * pprice);
						}
					}							
				else{
					printf("There is insufficient stock of %s to fulfil this line\n", pname);
					}
				}
  			}
	}
	 /* Close the file now that we are done with it */
    //struct OrderBook ob = {};
    
	printf("Finished Loading Order - ");
	prtc();
	//system("clear");
	return newcustomer;
}

void printProduct(struct Product p)
{
	//printf("Product Name: %s Price: %.2f ", p.name, p.price);
	printf("| %s \t %3.2f  \t ", p.name, p.price);

}

void printShop(struct Shop s)
{
	printf("Shop has %3.2f in cash and the following products in stock:\n", s.cash);
	printf("-------------------------------\n");
	printf("|Product Name | Price | Qty OH|\n");
	printf("-------------------------------\n");
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf(" %3d |\n", s.stock[i].quantity);
	}
	printf("-------------------------------\n\n");
	prtc();
}

void printCustomer(struct Customer c)
{
	//printf("ob ind3ex: %d",ob.index);
	printf("Customer Name: %s  Budget: %3.2f\n", c.name, c.budget);
	//printf("Order No:%d\tOrder  Details:\n",i);
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
	prtc();
	
}

void process_order(struct Customer *c,struct Shop *s ){
	//printf("Order No: %d Customer: %s Budget: %3.2f\n", o->order_no, o->customer.name, o->customer.budget);
    for (int i = 0; i < c->index; i++)
        {
            printf("Processing order line %d\n",i+1);
            float cost_of_line = c->shoppingList[i].product.price * c->shoppingList[i].quantity;
            printProduct(c->shoppingList[i].product);
            printf(" Order Qty: %d, Cost: %3.2f\n",c->shoppingList[i].quantity,cost_of_line);

            //find the product in the shop and change the quantity on hand
            int qty_on_hand = get_qty_oh(s,c->shoppingList[i].product.name);
            printf("The shop has %d of these in stock\n",qty_on_hand);
            int update_qty_on_hand = update_qty_oh(s,c->shoppingList[i].product.name,c->shoppingList[i].quantity);
            printf("The shop now has %d of these in stock\n",update_qty_on_hand);

            //update shop cash and customer budget
            printf("Reducing the customers budget by %3.2f and adding it to shop's cash\n",cost_of_line);
            c->budget -= cost_of_line;
            s->cash += cost_of_line;

        }
}

