#include <cs50.h>
#include <stdio.h>

int n = -1;
int i;
int z;

void right_pyramid(int w){
    for(i=1;i<w+1;i++){

        //for(z = 0; z < 10; z++) putchar(' ');
        for(z = 0; z < i; z++) putchar('#');
        printf("\n");

    }
}

void left_pyramid(int w){

    for(i=1;i<w+1;i++){
        for(z = 0; z < w-i; z++) putchar(' ');
        for(z = 0; z < i; z++) putchar('#');
        printf("  \n");
    }

}


void total_pyramid(int w){
    for(i=1;i<w+1;i++){



        for(z = 0; z < w-i; z++) putchar(' ');
        for(z = 0; z < i; z++) putchar('#');

        printf("  ");

        for(z = 0; z < i; z++) putchar('#');

        printf("\n");
    }
}

int main(){
    while(n<1 || n>8){
        n = get_int("Height: ");
    }

    //left_pyramid(n);
    //right_pyramid(n);
    total_pyramid(n);
}

