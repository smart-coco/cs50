# TODO

import cs50

# count_letters
def count_letters(text):
    ret=0
    for i in range(len(text)):
        if ((text[i]<='z') and (text[i]>='a')) or (((text[i]<='Z') and (text[i]>='A'))):
            ret+=1
    return ret

# count_words
def count_words(text):
    ret=0
    flag=1
    for i in range(len(text)):
        if ((text[i]<='z') and (text[i]>='a')) or (((text[i]<='Z') and (text[i]>='A'))) or text[i]=='-' or text[i]=='\'':
            flag=1
        else:
            if flag==1:
                ret+=1
            flag=0
    return ret

# count_sentences
def count_sentences(text):
    ret=0
    for i in range(len(text)):
        if text[i]=='.' or text[i]=='?' or text[i]=='!':
            ret+=1
    return ret

# main
str=cs50.get_string("Text: ")
l=count_letters(str)
w=count_words(str)
s=count_sentences(str)
score=round(0.0588 * l*100.0/w - 0.296 * s*100.0/w - 15.8)
if score<1:
    print("Before Grade 1")
else:
    if score>16:
        print("Grade 16+")
    else:
        print(f"Grade {score}")
#print(f"letters: {l}")
#print(f"words: {w}")
#print(f"sentences: {s}")
#print(f"socre: {score}")