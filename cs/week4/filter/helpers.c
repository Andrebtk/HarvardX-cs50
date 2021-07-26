#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <string.h>


/*

sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

*/


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){


            //printf("[red] -> %i\n",image[i][j].rgbtRed);
            //printf("[green] -> %i\n",image[i][j].rgbtGreen);
            //printf("[blue] -> %i\n",image[i][j].rgbtBlue);

            //printf("[average] -> %i\n\n", (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);


            float faverage = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue + 0.0)/3;

            int average = (int)(faverage >= 0.0 ? (faverage + 0.5) : (faverage - 0.5));

            //printf("[average] -> %d\n\n", average);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    double sepiaRed;
    double sepiaGreen;
    double sepiaBlue;

    int sepiaRed2;
    int sepiaGreen2;
    int sepiaBlue2;

    //printf("\n[height] -> %i\n", height);
    //printf("[width] -> %i\n\n", width);



    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            //printf("[bytes from raw %i and height %i]\n", j,i);
            /*
            printf("[red] -> Ox%02X\n",image[i][j].rgbtRed);
            printf("[green] -> Ox%02X\n",image[i][j].rgbtGreen);
            printf("[blue] -> Ox%02X\n\n",image[i][j].rgbtBlue);
            */
            //printf("[red] -> %i\n",image[i][j].rgbtRed);
            //printf("[green] -> %i\n",image[i][j].rgbtGreen);
            //printf("[blue] -> %i\n\n",image[i][j].rgbtBlue);

            sepiaRed = (0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = (0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = (0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            sepiaRed2 = ((int)(sepiaRed >= 0.0 ? (sepiaRed + 0.5) : (sepiaRed - 0.5)));
            sepiaGreen2 = ((int)(sepiaGreen >= 0.0 ? (sepiaGreen + 0.5) : (sepiaGreen - 0.5)));
            sepiaBlue2 = ((int)(sepiaBlue >= 0.0 ? (sepiaBlue + 0.5) : (sepiaBlue - 0.5)));

            if(sepiaRed2 > 255){ sepiaRed2 = 255; }
            if(sepiaGreen2 > 255){ sepiaGreen2 = 255; }
            if(sepiaBlue2 > 255){ sepiaBlue2 = 255; }


            image[i][j].rgbtRed = sepiaRed2;
            image[i][j].rgbtGreen = sepiaGreen2;
            image[i][j].rgbtBlue = sepiaBlue2;



        }


    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i=0; i<height; i++){
        for(int j=0; j<width/2; j++){

            RGBTRIPLE temp = image[i][j];


            image[i][j] = image[i][width - j - 1];
            image[i][width -j -1] = temp;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    
    //[!] my own algorithm not the one for the course
    int average;
    RGBTRIPLE a;
    RGBTRIPLE b;
    RGBTRIPLE c;
    RGBTRIPLE z;
    RGBTRIPLE d;


    int rAverage;
    int bAverage;
    int gAverage;


    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){

            z = image[i][j-2];
            a = image[i][j-1];
            b = image[i][j];
            c = image[i][j+1];
            d = image[i][j+2];


            rAverage = (a.rgbtRed + b.rgbtRed + c.rgbtRed + z.rgbtRed + d.rgbtRed)/5;
            bAverage = (a.rgbtBlue + b.rgbtBlue + c.rgbtBlue + z.rgbtBlue + d.rgbtBlue)/5;
            gAverage = (a.rgbtGreen + b.rgbtGreen + c.rgbtGreen + z.rgbtGreen + d.rgbtGreen)/5;

            //printf("%i\n%i\n%i\n\n", rAverage, bAverage, gAverage);


            image[i][j].rgbtRed = rAverage;
            image[i][j].rgbtGreen = gAverage;
            image[i][j].rgbtBlue = bAverage;
            //print("average -> %i\n", average);


        }
    }
    return;
}
