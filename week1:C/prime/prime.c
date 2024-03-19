#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}
h
bool prime(int number)
{
    // TODO
    bool flag=true;
    if (number==1) return false;
    for (int i=2;i<=sqrt(number);i++){
        if (number % i==0) flag=false;
    }
    return flag;
}
