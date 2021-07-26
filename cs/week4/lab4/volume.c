// Modifies the volume of an audio file
#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    /*
    uint8_t header[HEADER_SIZE];

    uint8_t *ptr = (uint8_t*) malloc(sizeof(header)*44);

    *ptr = 42;
    printf("ptr -> %p -> %u\n", ptr, *ptr);

    printf("input -> %p\n", (input));
    printf("input -> %p\n", (input+2));

    fread(ptr, sizeof(header)*1, 1, input);
    printf("%s\n", ptr);

    free(ptr);
    */



    //easy -> working

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];


    fread(&header, sizeof(header), 1, input);
    fwrite(&header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }


    /*
    // TODO: Copy header from input file to output file
    uint8_t str[44];

    fread(&str, sizeof(str),1,input);
    fwrite(&str, sizeof(str),1,output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t data;

    while(fread(&data, sizeof(str),1,input)){
        data*=factor;
        fwrite(&data, sizeof(str),1,output);
    }
    */

    //unsigned char c;

    //printf("%p\n", &input);
    //fread(&input, 1, 1, input);

    /*
    int n = fread(&header, sizeof(4), 1, input);
    int z = fread(&header+9, sizeof(3), 1, input);


    printf("n -> %i\nz -> %i\n", n, z);

    printf("%s\n", (header));
    printf("%s\n", (header));

    int total = fread(&header, sizeof(44), 1, input);
    //printf("%i\n", (int)header);

    */




    /*
    for (int i=13; i<17; i++){
        printf("str -> %p -> %c\n", str+i, *str+i);
    }

    printf("%s\n", str);


    */



    /*
    while(fread(&header, sizeof(header), 1, input)){
        printf("%x  ",(int) header);

    }
    */
    /*
    char c;
    while(fread(&c, sizeof(char), 1, input)){
        printf("%c",c);
    }
    */

    /*
    while(fread(&input, sizeof(unsigned char), 1, input)){
        printf("%i",*input);
    }*/






    // Close files
    fclose(input);
    fclose(output);
}
