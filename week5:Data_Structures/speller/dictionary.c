// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *p=table[hash(word)];
    while(p!=NULL) {
        if (strcasecmp(word,p->word)==0) {
            return true;
        }
        p=p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open the file and load
    FILE *fp=fopen(dictionary,"r");
    if (fp==NULL) {
        printf("Failed to open dictionary.\n");
        return false;
    }

    char get_word[LENGTH+3];
    while (fgets(get_word,LENGTH+3,fp)!=NULL) {
    //while (fscanf(fp,"%s",get_word)!=EOF) {
        int hash_n=hash(get_word);
        node *n=malloc(sizeof(node));
        if (n==NULL)
        {
            return false;
        }
        int l=strlen(get_word);
        get_word[l-1]='\0';
        for (int i=0;i<(l-1);i++)
        {
            get_word[i]=tolower(get_word[i]);
        }
        strncpy(n->word,get_word,l);
        n->next=table[hash_n];
        table[hash_n]=n;
    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int ret=0;
    for (int i=0;i<N;i++)
    {
        node *p=table[i];
        while(p!=NULL)
        {
            ret++;
            p=p->next;
        }
    }
    return ret;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i=0;i<N;i++)
    {
        node *p=table[i];
        node *t;
        while(p!=NULL)
        {
            t=p;
            p=p->next;
            free(t);
        }
        if (i == N - 1 && p == NULL)
        {
            return true;
        }
    }
    return false;
}
