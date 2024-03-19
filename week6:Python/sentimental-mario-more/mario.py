# TODO

from cs50 import get_int

while True:
    n=get_int("Height:")
    if n<=8 and n>=1:
        break

for i in range(n):
    for j in range(n-i-1):
        print(" ",end="")
    for z in range(i+1):
        print("#",end="")
    print("  ",end="")
    for z in range(i+1):
        print("#",end="")
    print("")