#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "phonebook_opt.h"

unsigned int hash(char *str)
{
    unsigned int hash_value = 0;
    while(*str)
        hash_value = (hash_value << 5) - hash_value + (*str++);
    return (hash_value % SIZE);
}

hash_table *create_hash_table()
{
    hash_table *my_table;

    /* Allocate memory for hashtable*/
    my_table = malloc(sizeof(hash_table));
    my_table->table = malloc(sizeof(entry *) * SIZE);

    /* Initialize the elements of the table */
    for(int i=0; i<SIZE; i++)
        my_table->table[i] = NULL;

    return my_table;
}

entry *findName(char *lastName, hash_table *hashtable)
{
    entry *list;
    unsigned int hash_value = hash(lastName);

    /*	 Searching from hash_table   */
    for(list = hashtable->table[hash_value] ; list!=NULL ; list = list->pNext) {
        if(strcmp(lastName,list->lastName)==0)
            return list;
    }

    /* FAIL */
    return NULL;
}

void append(char *lastName,hash_table *hashtable)
{
    entry *new_entry;
    unsigned int hash_value = hash(lastName);

    new_entry = (entry *) malloc(sizeof(entry));

    /* Creating entry list by hash table */
    strcpy(new_entry->lastName , lastName);
    new_entry->pNext = hashtable->table[hash_value];
    hashtable->table[hash_value] = new_entry;
}
