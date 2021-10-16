from cs50 import *
import sys
import csv
import re

seq = {}

if len(sys.argv) != 3:
    print("[!] bad usage of command line arguments")
    exit(1)

with open(sys.argv[2]) as x:
    data = csv.reader(x)
    for row in data:
        dnaLst = row

dna = dnaLst[0]

with open(sys.argv[1]) as x:
    for row in csv.reader(x):
        dnaS = row
        dnaS.pop(0)
        break

for y in dnaS:
    seq[y] = 1




"""

def findSTR(Type, List):
    print(Type)
    print(List)

    follow=0
    unfollow=0
    Max= [None]*200
    i=0


    for x in List:
        if x == List[0]:
            last = x
        else:
            if x-last == len(Type):
                follow+=1

            else:

                unfollow+=1
            last = x


#            if last + len(Type) == x:
#                follow+=1
#                last = x
    return follow, unfollow




for x in dnaS:
    a,b=findSTR(x, [m.start() for m in re.finditer(x, dna)])
    print(a,b)
"""





for x in seq:
    l = len(x)
    tempM = 0
    temp = 0
    for i in range(len(dna)):
        while temp > 0:
            temp -= 1
            continue
        if dna[i: i + l] == x:
            while dna[i - l: i] == dna[i: i + l]:
                temp += 1
                i += l
            if temp > tempM:
                tempM = temp
    seq[x] += tempM

with open(sys.argv[1], newline='') as peoplefile:
    people = csv.DictReader(peoplefile)
    for x in people:
        y = 0
        for dna in seq:
            if seq[dna] == int(x[dna]):
                y += 1
        if y == len(seq):
            print(x['name'])
            exit()
    print("No match")






