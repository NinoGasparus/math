import sys

if(len(sys.argv) < 3):
    print("not enough arguments")
    sys.exit(0)

x = int(sys.argv[1])
y = int(sys.argv[2])

print(x+y)
