#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do{
        n = get_int("Height: ");
    }
    while (n>8 || n<1);
    for (int i=0;i<n;i++){
        for (int j=n-i-1;j>0;j--){
            printf(" ");
        }
        for (int z=0;z<i+1;z++){
            printf("#");
        }
        printf("\n");
    }
}