# TODO

import cs50

number=0
while True:
    number=cs50.get_int("Number: ");
    if number!=0:
        break
if (number>=340000000000000 and number<=349999999999999) or (number>=370000000000000 and number<=379999999999999):
    answer="AMEX"
else:
    if (number>=5100000000000000 and number<=5599999999999999):
        answer="MASTERCARD"
    else:
        if (number>=4000000000000000 and number<=4999999999999999) or (number>=4000000000000 and number<=4999999999999):
            answer="VISA"
        else:
            answer="INVALID"

count1=0
count2=0
flag=1
while number!=0:
    if flag==1:
        count2=count2+number%10
    else:
        temp=number%10*2
        while temp>0:
            count1=count1+temp%10
            temp=temp//10
    flag=flag*-1
    number=number//10
count1=count1+count2
if count1%10!=0:
    answer="INVALID"
print(f"{answer}")