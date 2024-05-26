import csv

with open('test.csv', newline='') as f:
    reader = csv.reader(f)
    for row in reader:
        print(row)