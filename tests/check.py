import sys
sys.set_int_max_str_digits(999999)
file_path = 'Checks/number1'

with open(file_path, 'r') as file:
    number = int(file.read().strip())
    x = number 
    y = number
    print(x + y)

