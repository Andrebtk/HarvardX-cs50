from cs50 import *

def count(text):

    word=1
    letters=0
    sentences=0

    for i in text:
        if i == " ": word+=1
        elif i == "." or i == "!" or i == "?": sentences+=1
        elif i.isalpha(): letters+=1

    w = 100 / word
    l = w * letters
    s = w * sentences
    index = 0.0588 * l - 0.296 * s - 15.8
    final = round(index)

    if final < 1: print("Before Grade 1")
    elif final > 16: print("Grade 16+")
    else: print("Grade " + str(final))


a = get_string("Text: ").lower()
count(a)