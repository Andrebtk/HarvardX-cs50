from cs50 import *

data = -1
valid = False
total = 0

quarters = 25;
dimes = 10;
nickels = 5;
pennies = 1;



while data < 0:
    data = get_float("Change owed: ")

newData = data*100

while valid == False:
    while newData>=quarters:
        total += 1
        newData = newData - quarters


    while newData>=dimes:
        total += 1
        newData = newData - dimes


    while newData>=nickels:
        total += 1
        newData = newData - nickels

    while newData>=pennies:
        total+=1
        newData = newData - pennies

    valid = True

    print(total)