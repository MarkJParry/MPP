#Filename:  squareroot.py
#Author:    Mark Parry
#Created:   28/02/2021
#Purpose:  finds the square root of a number using the newton square root method
#accept a number and a tolerance , finishes when the tolerance is minimal compared to assumed root
#iterative formula for square root = .5(x+n/x)
#tried this on paper very cool 
#References:
#https://www.geeksforgeeks.org/find-root-of-a-number-using-newtons-method/
#https://en.wikipedia.org/wiki/Newton%27s_method
#https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
#rabbit hole on connections to other things whilst researching(bones babylonian maths prizes etc) but very interesting
#http://www.math.com/school/subject1/lessons/S1U1L9DP.html - simple lesson for manual calc.

#n is the number to find the square root of and t is the toleranace level(number of decimal places) to enable us to stop calculating "(x-root) < t"
def newton(n,t):
    x = n               #let the approx square root equal the input number to start
    while True:         #This will loop indefinitely until the break statement occurs
                                  # First time through                                               # 2nd Time  
        root = .5 * (x + (n/x))   # i.e n = 25   ==> root .5 (25 + 1) ~ 13                           # x is now 13 ==> root is .5(13 +25/13) ~ 7
        if (x - root) < t:        # (25 - 13) is not less than .000001                               # (13 - 7) !< .000001
            break                 # doesn't happen because above condition not met 
        x = root                  # swap x with the calculed root  x becomes 13  and reiterate       #x now 7
    return root                   # break occurs when within .000001 close to the true root so stop calc and return answer
#the above will loop until the difference between the calculated root and assumed root x is less than the tolerance entered in this case .000001

#Obtain the number to find the square root of
numIn = float(input("Please enter a postive number: "))

#call the above function passing in the inputted number and a tolerance
result = newton(numIn,.001)

#output the answer to the screen rounding the answer to 4 decimal places
print("The square root of {} is approx {}".format(numIn, round(result,4)))