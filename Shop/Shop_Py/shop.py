from dataclasses import dataclass, field
from typing import List
import csv

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

def get_price(shop, pname):
    for item in shop.stock:
      if item.product.name  == pname:
         #print("found product")
        return item.product.price
    return 0

def create_and_stock_shop():
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
    
def read_customer(file_path,s):
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
    print("-------------------------------\n")

s = create_and_stock_shop()
print_shop(s)

#pname = "Bread"
#get_price(s, pname)

c = read_customer("../data/custorderDom.csv",s)
print_customer(c)