#include <cs50.h>
#include <stdio.h>
#include <math.h>


float quarters = 25;
float dimes = 10;
float nickels = 5;
float pennies = 1;

bool valid = false;
bool valid2 = false;

int total = 0;

float data = -1;
int newData = 0;


int main(){
    while(valid == false){
        while(data < 0){
            data = get_float("Change owed: ");
        }
        valid = true;
        newData = round(data * 100);
    }

    while(valid2 == false){
        while(newData>=quarters){
            total++;
            newData = newData - quarters;
        }

        while(newData>=dimes){
            total++;
            newData = newData - dimes;
        }

        while(newData>=nickels){
            total++;
            newData = newData - nickels;
        }

        while(newData>=pennies){
            total++;
            newData = newData - pennies;
        }

        printf("%d\n", total);
        valid2 = true;
    }
    return 0;
}
