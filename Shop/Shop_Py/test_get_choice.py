import numpy as np

def stringify_choices(arr,outstr):
    if len(arr) == 0:
        return outstr[:-1]
    outstr += str(arr[0]) + ","
    return stringify_choices(arr[1:],outstr)
    
def get_choice(arr):
    choices = stringify_choices(arr,"")

    while True:
        choice = input("Please choose an option: ")
        if choice in choices:
            break
        else:
            print("Valid options are: ",choices)
    return choice

def check_if_float(inputStr):
    try:
        val = float(inputStr)
        return 1
    except ValueError:
        print("Please enter a valid")
    return 0

#choices = np.arange(1,10,1)

#choice = get_choice(choices)

check = check_if_float("1.99")
print(check)

