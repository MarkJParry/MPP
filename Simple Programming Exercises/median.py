import math

def get_median_value_and_index(list):
    """ 
        Given a list of numbers as input this function will return the median  value in that list.
        It calls the bubble_sort function to sort the list

        Note - this function is incorrect
    
        :param list: the list of numbers given as input
        :return: the median value of the list
    """
    #list1 = list.copy()
    #bubble_sort(list1)

    #find the index for the middle value
    no_elements = int(len(list))
    
    idx = math.ceil(no_elements/2) -1

    print(idx)
    

    #check if number of elements in the list is odd or even
    #if odd then the array was odd length
    #so the median would be the middle value in positon(idx +1) python index starts at zero whereas position starts at 1
    #if even then the array was even length
    #so need to take the average of the two middle values

    if no_elements%2 == 1:
        median = list[idx]
    else:
        median = (list[idx] + list[idx+1])/2
    return median, idx

def get_quartiles(list,idx):

    q1_list=list[:idx]
    q3_list=list[idx+1:]

    q1= get_median_value_and_index(q1_list)
    q3= get_median_value_and_index(q3_list)
    return q1, q3

#test for odd array
#median should be 7
list=[3,5,7,9,11]
median, idx = get_median_value_and_index(list)
print(median,idx)
q1,q3 = get_quartiles(list,idx)
print(q1[0],q3[0])
#test for even array
#median should be (7 +9 )/2 = 8
#median = get_median_value([3,5,7,9,11,13])
#print(median)
#median should be (9+11)/2=10
#median = get_median_value([3,5,7,9,11,13,15,17])
#print(median)