def powers(n,p):
    if p == 0:
        return n
    return n * powers(n,p -1)

#print( powers(2,7))

def palindrome(string):
    #print(string)
    if len(string)==0:
        return True
    if string[0] == string[len(string)-1]:
        #print( string[1:len(string)-1])
        return palindrome(string[1:len(string)-1])
    return False

#print(palindrome("able i was ere saw i elba"))

def reverse(string,rstring):
    if len(string)==0:
        return rstring
    rstring += string[len(string)-1]
    return reverse(string[:len(string)-1],rstring)

print(reverse("markparry",""))

