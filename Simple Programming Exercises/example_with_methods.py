import csv
from sorting_algorithms import bubble_sort, sq_root
import math
import pandas as pd

def calc_std_dev(list):
    """ 
        Given a list of numbers as input this function will return the standard deviation for that list.
        derived from https://www.mathsisfun.com/data/standard-deviation-formulas.html
    
        :param list: the list of numbers given as input
        :return: the standard deviation for that list

    """
    #1. get the mean
    mu = get_average(list)

    #2. Then for each number: subtract the Mean and square the result
    new_list = []
    for item in list:
        new_list.append((item - mu)**2)

    #3. Then work out the mean of those squared differences
    mu2 = get_average(new_list)

    #4. Take the square root of the above and we are done

    std_dev = sq_root(mu2)

    return std_dev



def get_maximum_value(list):
    """ 
        Given a list of numbers as input this function will return the maximum value in that list.
    
        :param list: the list of numbers given as input
        :return: the maximum value of the list
    """
    maximum = list[0]
    for l in list:
        if maximum < l:
            maximum = l
    return maximum

def get_minimum_value(list): 
    """ 
        Given a list of numbers as input this function will return the minimum value in that list.
    
        :param list: the list of numbers given as input
        :return: the minimum value of the list
    """

    minimum = list[0]
    for l in list:
        if minimum > l:
            minimum = l
    return minimum
            
def get_average(list):
    """ 
        Given a list of numbers as input this function will return the numerical average.
    
        :param list: the list of numbers given as input
        :return: the numerical average of the list
    """
    total = 0
    for l in list:
        total += l
        
    average = total / len(list)
    return average

def get_median_value(list):
    """ 
        Given a list of numbers as input this function will return the median  value in that list.
        It calls the bubble_sort function to sort the list
    
        :param list: the list of numbers given as input
        :return: the median value of the list
    """
    list1 = list.copy()
    bubble_sort(list1)
    median = list1[int(len(list1)/2)]
    return median

def get_median_value_and_index(list):
    """ 
        Given a list of numbers as input this function will return the median  value in that list.
        It calls the bubble_sort function to sort the list

        Note - the original function is incorrect
    
        :param list: the list of numbers given as input
        :return: the median value of the list and its position
    """
    list1 = list.copy()
    bubble_sort(list1)

    #find the index for the middle value
    no_elements = int(len(list1))
    
    idx = math.ceil(no_elements/2) -1

    #print(idx)
    

    #check if number of elements in the list is odd or even
    #if odd then the array was odd length
    #so the median would be the middle value in positon(idx +1) python index starts at zero whereas position starts at 1
    #if even then the array was even length
    #so need to take the average of the two middle values

    if no_elements%2 == 1:
        median = list1[idx]
    else:
        median = (list1[idx] + list1[idx+1])/2
    return median, idx

def get_quartiles(list,idx):
    list1 = list.copy()
    bubble_sort(list1)
    q1_list=list1[:idx]
    q3_list=list1[idx+1:]

    q1= get_median_value_and_index(q1_list)
    q3= get_median_value_and_index(q3_list)
    return q1, q3

#def bubble_sort(list1):
    """ moving this to sorting-algorithms.py as a separate module"""    

    """ 
        Given a list of numbers as input this function will sort the  list in-place.
    
        :param list: a copy of the list of numbers given as input
        :return: nothing explicity returned however inputted list is sorted
    """

    """
    for i in range(0,len(list1)-1):  
        for j in range(len(list1)-1):  
            if(list1[j]>list1[j+1]):  
                temp = list1[j]  
                list1[j] = list1[j+1]  
                list1[j+1] = temp  
    """
def get_mode(list):
    """ 
        Given a list of numbers as input this function will return the mode value for that list.
        It calculates the mode by counting the occurences of items in the list and returning the one with the highest number of occurences

    
        :param list: the list of numbers given as input
        :return: the mode value of the list
    """
    highest_freq = 0
    mode = scores[0]
    for score in scores:
        frequency = 0
        for score2 in scores:
            if score == score2:
                frequency += 1
        if frequency > highest_freq:
            mode = score
            highest_freq = frequency
    return mode

def read_scores_from_csv(filename):
    """ 
        Given a filename as input this function will return the values in that csv file.
    
        :param list: filename of the csv file to be read
        :return: a list of the values in the csv file for the 'score' column
    """
    scores = []
    with open(filename, mode ='r') as file:   
        csvFile = csv.DictReader(file)
    
        for lines in csvFile:
            score = int(lines["Score"])
            scores.append(score)    
    return scores
    
if __name__ == "__main__":

    scores = read_scores_from_csv('example.csv')
    ds = pd.Series(scores)
    print(ds)
    print(ds.describe())
    
    average = get_average(scores)
    minimum = get_minimum_value(scores)   
    maximum = get_maximum_value(scores)
    median,idx = get_median_value_and_index(scores)
    mode = get_mode(scores)
    range = get_maximum_value(scores) - get_minimum_value(scores)
    std_dev = calc_std_dev(scores)
    q1, q3 = get_quartiles(scores,idx)

    print(f'Average: {average} Smallest: {minimum} Q1: {q1[0]} Median: {median} Q3: {q3[0]}Largest: {maximum} Mode: {mode} Range: {range} Std_dev: {std_dev}')
    