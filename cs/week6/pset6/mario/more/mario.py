def inputNumber(message):
  while True:
    try:
       userInput = int(input(message))
    except ValueError:
        continue
    else:
       return userInput
       break


def mario(height, i):

    if i == height :
        exit()

    print(" "*(height-i-1) + "#"*(i) + "  " + "#"*(i))
    mario(height, i+1)

while True:
    a = inputNumber("Height : ")

    if a > 0 and a < 9:
        mario(a+1,1)