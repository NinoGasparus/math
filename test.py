with open("./Checks/number1", 'r') as f:
    number = int(f.read().strip())  

result = number * 2

print(result)

