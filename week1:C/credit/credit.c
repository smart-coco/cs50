#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number=0;
    do {
        number=get_long("Number: ");
    }
    while (number==0);
    string answer;
    if ((number>=340000000000000 && number<=349999999999999) || (number>=370000000000000 && number<=379999999999999)){
        answer="AMEX";
    }else{
        if ((number>=5100000000000000 && number<=5599999999999999)){
            answer="MASTERCARD";
        }else{
            if ((number>=4000000000000000 && number<=4999999999999999) || (number>=4000000000000 && number<=4999999999999)){
                answer="VISA";
            }else answer="INVALID";
        }
    }
    int count1=0,count2=0,flag=1;
    while(number!=0){
        if (flag==1){
            count2=count2+number%10;
        }else{
            int temp=number%10*2;
            while(temp>0){
                count1=count1+temp%10;
                temp=temp/10;
            }
        }
        flag=flag*-1;
        number=number/10;
    }
    count1=count1+count2;
    if (count1%10!=0) answer="INVALID";
    printf("%s\n",answer);
}