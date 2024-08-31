import sys

file_path = 'Checks/small9'

with open(file_path, 'r') as file:
    number = int(file.read().strip())
    x = number 
    y = number
    print(x + y)

