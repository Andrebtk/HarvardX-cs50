#include <cs50.h>
#include <stdio.h>

int new_n;
int pass_n;
int years;

int main(void){
    // Prompt for start size
    int n = get_int("Start size: ");

    while(n < 9){
        n = get_int("Start size must be bigger than 9: ");
    }

    int n_final = get_int("End size: ");
    while(n_final < n){
        n_final = get_int("End size must be bigger than the start population : ");
    }
    printf("Start size : %i\n", n);
    printf("End size : %i\n", n_final);


    while(n<n_final){
        new_n = n/3;
        pass_n = n/4;

        n = n + new_n - pass_n;

        years++;

    }



    printf("Years: %i\n",years);



    // TODO: Calculate number of years until we reach threshold

    // TODO: Print number of years
}