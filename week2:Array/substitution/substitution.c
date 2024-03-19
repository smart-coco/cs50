#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool checks(string s);
int main(int argc, string argv[])
{
    if (argc!=2){
        printf("Usage: ./substitution key\n");
        return 1;
    }else{
        if (strlen(argv[1])!=26){
            printf("Key must contain 26 characters.\n");
            return 1;
        }else{
            if (checks(argv[1])){
                printf("Islegal.\n");
                return 1;
            }
        }
    }
    string s=get_string("plaintext: \n");
    int l=strlen(s);
    for (int i=0;i<l;i++){
        if (isupper(s[i])) s[i]=toupper(argv[1][s[i]-'A']);
        else if (islower(s[i])) s[i]=tolower(argv[1][s[i]-'a']);
    }
    printf("ciphertext: %s\n",s);
    return 0;
}
bool checks(string s){
    bool isf[26];
    for (int i=0;i<26;i++){
        isf[i]=true;
    }
    for (int i=0;i<26;i++){
        int temp=tolower(s[i])-'a';
        //printf("temp: %d\n",temp);
        if (isalpha(s[i]) && isf[temp]) isf[temp]=false;
        else return true;
    }
    return false;
}