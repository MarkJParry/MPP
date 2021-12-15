def get_line_to_modify(c):
	if (len(c.shopping_list) > 0):
        
        print(f"The order contains the following lines")
		print(f"------------------------------------")
		print(f"|LineNo | Item         | Order Qty |")
		print(f"------------------------------------")
        for i,item in enumerate(c.shopping_list):
          	
        	print(f"| {i+1:d} ")
			print(f"| {item.product.name:13s}")
			print(f"| {item.quantity:3d}       |" )
           	
		print(f"------------------------------------")
        print(f"Please choose a line item to modify by inputting its number or enter -1 to exit")
        choice = 0
        while (choice != -1):
        	
        	choice = get_input()
        	#print(f"Chosen%d",choice)
        	if (choice == -1):
            	
				#char *csv_file_name = ""
                #return csv_file_name
                return -1
                
            validated = validate_input(choice, 1, c->index)
            if (validated == 1):
            	
            	idx = choice -1
               	print(f"You have chosen to modify order line no {choice:d}")
				#char *csv_file_name = csv_folder.data_file[idx].f_name
				return idx
            	#break
                
            else:
                
                print(f"Please enter a valid order line number")
                
            
        
    else:
        
        print(f"No lines have been added to this order yet - option 1 will allow order entry, option 2 allows upload from a csv file")
		return -1   
        


def modify_order(c,s)
	print(f"In modify order")
	print(f"index%d",c->index)
	ltm = get_line_to_modify(c)
	if (ltm != -1):
		
		char input[50]
		print(f"Enter the new order quantity")
		fgets(input,10,stdin)
		nqty = atoi(input)
		c.shoppingList[ltm].quantity = nqty
		
	prtc()
