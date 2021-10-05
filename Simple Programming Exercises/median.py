def get_median_value(list):
    """ 
        Given a list of numbers as input this function will return the median  value in that list.
        It calls the bubble_sort function to sort the list

        Note - this function is incorrect
    
        :param list: the list of numbers given as input
        :return: the median value of the list
    """
    #list1 = list.copy()
    #bubble_sort(list1
    pos = int(len(list)/2)

    if pos%2 == 0:
        median = list[pos]
    else:
        median = (list[pos] + list[pos +1])/2
    return median

median = get_median_value([3,5,7,9,11])
print(median)