#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(int argc, char *argv[])
{
    printf("hello world\n");

    if(argc!=2){
        printf("Usage: ./recover [file]\n");
        return 1;
    }

    char *fileName = argv[1];

    printf("%s\n", fileName);

    FILE *inptr = fopen(fileName, "r");
    FILE *outptr = NULL;


    if(inptr == NULL){
        printf("Could not open %s\n", fileName);
        return 1;
    }

    const int block = 512;
    unsigned char buffer[block];
    int i=0;
    char name[9];

    while(fread(buffer, block, 1, inptr)==1){
        /*
        printf("buffer[0] -> 0x%04x\n", buffer[0]);
        printf("buffer[1] -> 0x%04x\n", buffer[1]);
        printf("buffer[2] -> 0x%04x\n", buffer[2]);
        printf("buffer[3] -> 0x%04x\n\n", buffer[3]);
        */

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef){



            sprintf(name, "%03i.jpg",i);
            outptr = fopen(name, "w");


            //fwrite(buffer, block, 1, outptr);

            i++;
        }
        if(outptr != NULL){
            fwrite(buffer, block, 1, outptr);
        }

    }
    printf("%03i",i);
    fclose(inptr);
    fclose(outptr);

    return 0;
}