
import csv
scores = []
with open('example.csv', mode ='r') as file:   
    csvFile = csv.DictReader(file, delimiter = ',')
   
    for lines in csvFile:
        #print(lines.keys())
        print(lines['Student_Number'])
        score = int(lines["Score"])
        scores.append(score)    
print(scores)
