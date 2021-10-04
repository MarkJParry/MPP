n = input("Enter a number: ")

sum = 0

for i in range(1,n+1):
    if ((i % 3)==0) or ((1 % 5)==0):
        print i
        sum = sum + i

print("The sum of 1 to %d, was %d" % (n, sum))