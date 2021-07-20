#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>



int key[] = {};
char param;

void encrypt(string w, string y, bool help);

int main(int argc, char **argv){

    if(argc<2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for(int c = 0, n = strlen(argv[1]); c<n;c++){
        //printf("%c", toupper(argv[1][c]));
        if(toupper(argv[1][c]) >= 65 && toupper(argv[1][c]) <= 90){
            argv[1][c] = toupper(argv[1][c]);
        }else{
            printf("use correct format of key\n");
            return 1;
        }
    }

    for(int a = 65, n = strlen(argv[1])+65; a<n;a++){
        if(argv[1][a-65] == a){
            printf("duplicate characters in key\n");
            return 1;
        }
    }

    if(strlen(argv[1]) == 26){
        //printf("argv -> %s\n", argv[1]);
        string plaintext = get_string("plaintext: ");
        encrypt(argv[1], plaintext, false);
    }else if(strlen(argv[1]) > 26 || strlen(argv[1]) < 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}

void encrypt(string w, string y, bool help){

    if(help){
        printf("w -> %s\n",w);
        printf("y -> %s\n",y);

        printf("w[0] to int -> %i\n", (int) w[0]);
        printf("y[0] to int -> %i\n\n", (int) y[0]);

        for(int o = 65, n=strlen(w)+65; o<n; o++){
            printf("%c -> %c\n", o, w[o-65]);
        }
    }

    for(int z = 0, n=strlen(w); z<n; z++){
        key[z] += (int) w[z];
    }
    printf("ciphertext: ");
    for(int i = 0, n=strlen(y); i<n; i++){
        //printf("%c -> %i -> %i -> %c\n", y[i], (int) y[i], (int) y[i]-96, (int) key[y[i]-97]);
        if(y[i]>=97 && y[i]<=122){
            printf("%c",(int) key[y[i]-97]+32);
        }else if(y[i]>=65 && y[i]<=90){
            printf("%c",(int) key[y[i]-65]);
        }else{
            printf("%c",(int) y[i]);
        }
    }
    printf("\n");
}