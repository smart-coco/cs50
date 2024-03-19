#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    string str;
    str=get_string("Text: ");
    int l=count_letters(str),w=count_words(str),s=count_sentences(str);
    int score=0.0588 * l*100.0/w - 0.296 * s*100.0/w - 15.8+0.5;
    if (score<1) printf("Before Grade 1\n");
    else{
        if (score>16) printf("Grade 16+\n");
        else printf("Grade %d\n",score);
    }
    printf("letters: %d\n",l);
    printf("words: %d\n",w);
    printf("sentences: %d\n",s);
    printf("socre: %d\n",score);
}
int count_letters(string text)
{
    int ret=0;
    for (int i=0;i<strlen(text);i++){
        if (((text[i]<='z')&&(text[i]>='a')) || (((text[i]<='Z')&&(text[i]>='A')))){
            ret++;
        }
    }
    return ret;
}
int count_words(string text)
{
    int ret=0,flag=1;
    for (int i=0;i<strlen(text);i++){
        if (((text[i]<='z')&&(text[i]>='a')) || (((text[i]<='Z')&&(text[i]>='A'))) || text[i]=='-' || text[i]=='\''){
            flag=1;
        }else{
            if (flag==1) {
                ret++;
            }
            flag=0;
        }
    }
    return ret;
}
int count_sentences(string text)
{
    int ret=0,flag=1;
    for (int i=0;i<strlen(text);i++){
        if (text[i]=='.' || text[i]=='?' || text[i]=='!'){
            ret++;
        }
    }
    return ret;
}