struct Customer readCustomerOrder(struct Shop shop)
{
	system("clear");
	printf("Loading Customer Order from file\n");
	struct Customer customer;
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
			printf("Product %s Price %.2f Quantity %d added to Customer Order\n\n", pname, pprice, order_quantity);
  			}
	}
	 /* Close the file now that we are done with it */
	fclose(fp1);
	printf("Finished Loading Order - ");
	prtc();
	system("clear");
	return customer;
}