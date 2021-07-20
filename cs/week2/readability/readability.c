#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
MATH :

w = 100 / number of words in the sentence
{value} letters per 100 words  = w * letters in sentences
{value} sentences per 100 words = w * numbers of sentences

Coleman-liau formula :

index = 0.0588 * L - 0.296 * S - 15.8

L = average number of letters per 100 words
S = average number of sentences per 100 words

*/


void count(string text);

int main()
{
    printf("hello world\n");



    string s = get_string("Text: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = tolower(s[i]);
    }

    count(s);
}

void count(string text)
{

    float letters = 0;
    float words = 1;
    float sentences = 0;

    float index;
    float l;
    float s;
    float w;
    int final;


    for (int i = 0, n = strlen(text); i < n ; i++)
    {
        //printf("%c\n",text[i]);

        if ((int)text[i] == 32)
        {
            words++;
        }
        else if ((int)text[i] == 46 || (int)text[i] == 33 || (int)text[i] == 63)
        {
            sentences++;
        }
        else if ((int)text[i] >= 96 && (int)text[i] <= 123)
        {
            letters++;
        }

    }
    //printf("letters -> %f\nwords -> %f\nsentences -> %f\n",letters,words,sentences);

    w = 100 / words;
    l = w * letters;
    s = w * sentences;
    index = 0.0588 * l - 0.296 * s - 15.8;
    final = (int)(index < 0 ? (index - 0.5) : (index + 0.5));

    //printf("w -> %f\nL -> %f\nS -> %f\n",w,l,s);



    if (final < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", final);
    }


}

