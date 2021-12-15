from dataclasses import dataclass, field
from typing import List
import csv
import os
import numpy as np

@dataclass
class Product:
    name: str
    price: float = 0.0

@dataclass 
class Stock:
    product: Product
    quantity: int

@dataclass 
class Shop:
    cash: float = 0.0
    stock: List[Stock] = field(default_factory=list)

@dataclass
class Customer:
    name: str = ""
    budget: float = 0.0
    shopping_list: List[Stock] = field(default_factory=list)

@dataclass
class OrderBook:
    order: List[Customer] = field(default_factory=list)

        
upload_folder = "../data/"

#set up the menu items and options to display
menu_items = [
"+================================+",
"|          Shop Menu  (Py)       |",
"+================================+",
"|1. Add Customer Order           |",
"|2. Load Customer Order from csv |",
"|3. Process Customer Order       |",
"|4. Add Stock                    |",
"|5. Change Price                 |",
"|6. Modify Order                 |",
"|7. View Shop                    |",
"|8. View Customer Order          |",
"|9. Quit                         |",
"+================================+"
]


#get the users selection from the menu choices
def get_choice():
    choices = "1,2,3,4,5,6,7,8,9"
    while True:
        choice = input("Please choose an option: ")
        if choice in choices:
            break
        else:
            print("Valid options are 1 - 9")
    return choice
        
def menu():
    for item in menu_items:
        print(item)
        



def prtc():
        input("Press the return key to continue");
        #menu();


def get_price(shop, pname):
    for item in shop.stock:
        if item.product.name  == pname:
            #print("found product")
            return item.product.price
    return 0

def update_product_price(shop, pname, nprice):
    for item in shop.stock:
        if item.product.name  == pname:
            item.product.price = nprice
            return 1
    return 0

def get_product_qty_oh(shop, pname):
    for item in shop.stock:
      if item.product.name  == pname:
    	#print("found product")
        return item.quantity
    return 0

def update_product_qty_oh(shop, pname,qty_on_hand):
    for item in shop.stock:
      if item.product.name  == pname:
        item.quantity -= qty_on_hand
        return item.quantity
    return 0

def check_if_exists(shop, pname):
    for item in shop.stock:
    	if item.product.name  == pname:
            #print("found product")
            return 1
    return 0

def check_if_float(inputStr):
    try:
        val = float(inputStr)
        return 1
    except ValueError:
        print("Please enter a valid number")
    return 0


def add_stock(s):
    pname = input("Enter a product: ").strip()
    in_stock = check_if_exists(s,pname)
    if in_stock:
        print("Product already in stock")
        return 0
    else:
        pprice = input("Enter the price: ")
        valid = check_if_float(pprice)
        if valid:
            p = (pname,price)
        pqty = input("Enter the quantity: ")
        valid = check_if_float(pqty)
        if valid:        
            ps = (p,pqty)
            s.append(ps)
        print(f"Product {pname:s}, Price {pprice:3.2f}, Quantity {pqty:d} added to shop stock")
        return 1


def change_price(s):
    pname = input("Enter  product for price change: ")
    in_stock = check_if_exists(s,pname)
    if in_stock:
        pprice = get_price(s,pname)
        print(f"Product {pname:s} is currently priced {pprice:3.2f}")
        nprice = input("Enter the new price: ")
        valid = check_if_float(nprice)
        if valid:
            updated = update_product_price(s,pname,nprice)
            if updated:
                print(f"Product {pname:s} is now priced {nprice:3.2f}")
                return 1
    else:
        print(f"Product {pname:s} not in stock")
        return 0


def create_and_stock_shop():
    print("Loading shop with stock from file ...")
    s = Shop()
    with open('../data/stockcash.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        s.cash = float(first_row[1])
        for row in csv_reader:
            p = Product(row[0], float(row[1]))
            ps = Stock(p, float(row[2]))
            s.stock.append(ps)
            #print(ps)
    return s
    
def read_customer(s):
    global c
    csv_file_name = get_csv_file_name()
    if csv_file_name != "":
        file_path = "../data/" + csv_file_name
        #print(file_path)
        #prtc()
        with open(file_path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            c = Customer(first_row[0], float(first_row[1]))
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                price = get_price(s, name)
                p = Product(name, price)
                #print("p",p)
                ps = Stock(p, quantity)
                c.shopping_list.append(ps)
            return c 
                
def add_customer(s):
    #print("Add Customer Order")
    global c
    cost_of_order = 0.0
    counter = 0
    finished = 0
    cbudget = 0.0
    while (finished != -1):
        counter += 1
        if (counter == 1):
            #add name & budget
            cname = input("Enter customer name: ").strip()
            cbudget = float(input("Enter customer budget: ").strip())
            c = Customer(cname, cbudget)
            print(f"Customer {cname:s} with a budget of {cbudget:3.2f} created")
        else:
            #add order lines        
            pname = input("Enter a product or -1 to finish: ").strip()
            #print("pname: ",pname)
            if (pname == "-1"):
                finished = -1
                break
            #check to see if product in stock
            qty_oh = get_product_qty_oh(s, pname)

            if (qty_oh != -1):
                order_quantity = int(input("Enter the quantity to order: "))
                #check if enough stock to fulfil this line
                if (order_quantity <= qty_oh):
                    pprice = get_price(s, pname)
                    cost_of_order += (order_quantity * pprice)
                    #check to see if over budget by adding this line to order
                    if (cost_of_order <= cbudget):
                        p = Product(pname, pprice)
                        ps = Stock(p, order_quantity)
                        c.shopping_list.append(ps)
                        print(f"Product {pname:s} Price {pprice:3.2f} Quantity {order_quantity:d} added to Customer Order")
                    else:
                        print(f"The cost {cost_of_order:3.2f} of the order exceeds the budget {cbudget:3.2f}")
                        print("Line not added to the order")
                        #remove this line from the cost of the order
                        cost_of_order -= (order_quantity * pprice)
                else:
                    print(f"There is insufficient stock of %s to fulfil this line", pname)
    
    print("Finished Loading Order - ")
    prtc()
    #print("Customer name:",c.name)
    return c

def check_orders(ob):
    if  ob.order:
        #print("orders")
        return 1
    else:
        print("No orders have been added yet - option 1 will allow order entry, option 2 allows upload from a csv file")
        prtc()
        return 0    

def check_order_not_empty(c):
    if  c.shopping_list:
        print("order has lines")
        prtc()
        return 1
    else:
        print("order has no lines")
        prtc()
        return 0   

def validate_input(choice,min,max):
    #printf("Input:%d Min:%d Max:%d\n",choice,min,max);
    validated = 0
    if((choice >= min) and (choice <= max)):
        
        validated = 1
    else:

        validated = 0
    return validated

def calculate_order_cost(c):
    total_cost = 0
    for item in c.shopping_list:
        cost = item.quantity * item.product.price 
        total_cost += cost
    return total_cost

def get_order_to_process(ob):
    if ob.order:
        print("The order book contains the following orders:")
        print("-----------------------------------------")
        print("|OrderNo| Customer   | Items   | Value  |")
        print("-----------------------------------------")
        for i,order in enumerate(ob.order):
            print(f"| {i+1:3d}   ",end="")
            print(f"| {ob.order[i].name:10s} ",end="")
            print(f"|   {len(ob.order[i].shopping_list):3d}   ",end="")
            order_value = calculate_order_cost(ob.order[i])
            print(f"| {order_value:6.2f} |")
        print("-----------------------------------------")
        print("Please choose an order to process by inputting its number or enter -1 to exit")
        choice = 0
        while (choice != "-1"):
            choice = int(input())
            if (choice == "-1"):
                return -1;
            validated = validate_input(choice,1,len(ob.order))
            if (validated == 1):
                idx = choice -1
                print(f"You have chosen to process order no: {choice:d}")
                return idx
            else:
                print("Please enter a valid order number")
    else:
        print("No orders have been added yet - option 1 will allow order entry, option 2 allows upload from a csv file")
        return 0; 

def process_order(s,c):
    for i,item in enumerate(c.shopping_list):
            print(f"Processing order line {i+1:d}")
            cost_of_line = item.product.price * item.quantity
            print_product(item.product)
            print(f" Order Qty: {item.quantity:3.0f} Cost:{cost_of_line:3.2f}")

            #find the product in the shop and change the quantity on hand
            qty_on_hand = get_product_qty_oh(s,item.product.name)
            print(f"The shop has {qty_on_hand:3.0f} of these in stock")
            update_qty_on_hand = update_product_qty_oh(s,item.product.name,item.quantity)
            print(f"The shop now has {update_qty_on_hand:3.0f} of these in stock")

            #update shop cash and customer budget
            print(f"Reducing the customers budget by {cost_of_line:3.2f} and adding it to shop's cash")
            c.budget -= cost_of_line
            s.cash += cost_of_line

def print_product(p):
    print(f'| {p.name} \t {p.price:3.2f} ', end ='')

def print_customer(c):
    print(f"Customer Name: {c.name}  Budget: {c.budget:3.2f}")
    print("Order Details:")
    print("-----------------------------------------")
    print("|Product Name | Price | OrderQty | Cost |")
    print("-----------------------------------------")
    total_cost = 0
    
    for item in c.shopping_list:
        print_product(item.product)
        print(f'\t {item.quantity:3.0f}',end='')
        cost = item.quantity * item.product.price
        total_cost += cost
        #print("\t Cost:{}".format(cost))
        print(f"\t {cost:6.2f} |")
        #print(f'The cost to {c.name} will be €{cost}')
    print("-----------------------------------------")
    print(f"| Total Cost of Order:          €{total_cost:3.2f} |")
    print("-----------------------------------------")
    if total_cost > c.budget:
        #overbudget = total_cost - c.budget
        print(f"Warning - Order exceeds Customer Budget by €{(total_cost - c.budget):5.2f}")
       
def print_shop(s):
    print(f"Shop has {s.cash:3.2f} in cash and the following products in stock:")
    print("-------------------------------")
    print("|Product Name | Price | Qty OH|")
    print("-------------------------------")
    #print(f'Shop has {s.cash} in cash')
    for item in s.stock:
        print_product(item.product)
        print(f'\t {item.quantity:4.0f} |')
    print("-------------------------------")
        
def get_files():
        data_folder = os.listdir("../data/")
        order_files = []
        for orderfile in data_folder:
                if "cust" in orderfile:
                        order_files.append(orderfile)
        return order_files
                        

def get_csv_file_name():
    csv_files = get_files()
    if len(csv_files)  > 0:
        print("The data folder contains the following files:")
        print("-----------------------------------------")
        print("|File Number | File Name                |")
        print("-----------------------------------------")

        for i,order_file in enumerate(csv_files):
            print("| %3d        | %-24s |" % (i+1,order_file))

        print("-----------------------------------------")
       
        choice =  0
        choices = np.arange(1,len(csv_files)+1,1)
        print(choices)

        while (choice != -1):
            choice = int(input("Please choose a file to upload by inputting its number or enter -1 to exit"))
            if (choice == -1):
                csv_file_name = ""
                return csv_file_name
            if choice in choices:
                idx = choice -1;
                csv_file_name = csv_files[idx]
                return csv_file_name
            else:
                print("Please enter a valid file number")
        else:
            print("The data folder is empty - please add an order file in csv format to the folder");   

    


                        
def option_1():
    print("Option 1 - Add Customer Order")
    c = add_customer(s)
    order_not_empty = check_order_not_empty(c)
    #print("Order not empty value: ",order_not_empty)
    #prtc()
    if order_not_empty:
        ob.order.append(c)
    #print(ob)
    #prtc()
def option_2():
    print("Option 2 - Load Customer Order from csv")
    c = read_customer(s)
    order_not_empty = check_order_not_empty(c)
    if order_not_empty:
        ob.order.append(c)
    prtc()
def option_3():
    print("Option 3 - Process Customer Order")
    have_orders = check_orders(ob)
    if have_orders:
        idx = get_order_to_process(ob)
        if idx != -1:
            process_order(s,ob.order[idx])
    #prtc()
def option_4():
    print("Option 4 - Add Stock")
    add_stock(s)
    prtc()
def option_5():
    print("Option 5 - Change Price")
    change_price(s)
    prtc()
def option_6():
    print("Option 6 - Modify Order")
    have_orders = check_orders(ob)
    if have_orders:
        otm = get_order_to_process(ob)
        if otm != -1:
            modify_order(s,ob.order[otm])
    prtc()
def option_7():
    print("Option 7 - View Shop")
    print_shop(s)
    prtc()
def option_8():
    print("Option 8 - View Customer Order")
    have_orders = check_orders(ob)
    if have_orders:
        ctp = get_order_to_process(ob)
        if ctp != -1:
            print_customer(ob.order[ctp])
    prtc()



#set up the array for the available options on the menu
options = [option_1,option_2,option_3,option_4,option_5,option_6,option_7,option_8]



                        
def main():
    global s
    
    s = create_and_stock_shop()
    print_shop(s)
    prtc()
    global ob
    ob = OrderBook()
    #print(ob)
    #prtc()
    while True:
        os.system('clear') #clear the screen
        menu()
        choice = get_choice()
        if choice == "9":
            print("Option 9 - Now exiting program")
            exit()
        else:
            option = options[int(choice) -1]
            option() 

if __name__ == "__main__":
        main()
                        

