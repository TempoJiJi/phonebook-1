#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "phonebook_opt.h"

int hash(char *str)
{
    unsigned int hash_value = 0;
    while(*str)
        hash_value = (hash_value << 5) - hash_value + (*str++);
    return (hash_value % SIZE);
}

void create_hash_table()
{
    int i;

    /* Allocate memory for hashtable*/
    my_hash_table = malloc(sizeof(hash_table));
    my_hash_table->table = malloc(sizeof(entry *) * SIZE);

    /* Initialize the elements of the table */
    for(i=0; i<SIZE; i++)
        my_hash_table->table[i] = NULL;
}

entry *findName(char *lastName)
{
    entry *list;
    int hash_value = hash(lastName);

    /*   Searching from hash_table   */
    for(list = my_hash_table->table[hash_value] ; list!=NULL ; list = list->pNext) {
        if(strcmp(lastName,list->lastName)==0) {
            return list;
        }
    }
    /* FAIL */
    return NULL;
}

void append(char *lastName)
{
    entry *new_entry;
    int hash_value = hash(lastName);

    new_entry = (entry *) malloc(sizeof(entry));

    /* Creating entry list by hash table */
    strcpy(new_entry->lastName , lastName);
    new_entry->pNext = my_hash_table->table[hash_value];
    my_hash_table->table[hash_value] = new_entry;
}
