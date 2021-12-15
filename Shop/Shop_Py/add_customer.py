def addCustomerOrder(s):

	print("Add Customer Order")
	float cost_of_order = 0.0
	int counter = 0
	int finished = 0
	float budget =0.0
    while (finished != -1):
		counter++;
		if (counter == 1):
			#add name & budget
			cname = input("Enter customer name: ")
			budget =input("Enter customer budget: ")
			newcustomer.name = cname;
			newcustomer.budget = budget;
			print("Customer %s with a budget of %.2f created", cname, budget)
		else:
			#add order lines	
			pname = input("Enter a product or -1 to finish: ")
			if (pname == -1):
				finished = -1
				break
			//check to see if product exits
			int found = get_product_details(s, pname)

			if (found != -1):
				order_quantity = input("Enter the quantity to order: ")
				#check if enough stock to fulfil this line
				if (order_quantity <= shop->stock[found].quantity):
					float pprice = get_product_price(s, pname)
					cost_of_order += (order_quantity * pprice)
					#check to see if over budget by adding this line to order
					if (cost_of_order <= newcustomer.budget):
						struct Product product = {pname, pprice}
						struct Stock shoppingListItem = { product, order_quantity }
						newcustomer.shoppingList[newcustomer.index++] = shoppingListItem
						print(f"Product %s Price %.2f Quantity %d added to Customer Order", product.name, product.price, order_quantity)
					else:
						print(f"The cost %3.2f of the order exceeds the budget %3.2f",cost_of_order,newcustomer.budget)
						print("Line not added to the order")
						//remove this line from the cost of the order
						cost_of_order -= (order_quantity * pprice)
				else:
					print(f"There is insufficient stock of %s to fulfil this line\n", pname)
    
	prinf("Finished Loading Order - ")
	prtc()
	return newcustomer
}
