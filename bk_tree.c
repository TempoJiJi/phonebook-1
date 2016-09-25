#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#include "bk_tree.h"

int dist(char *a,char *b)
{
    int count = 0;
    int max = MAX(strlen(a),strlen(b));
    int min = MIN(strlen(a),strlen(b));
    for(int i=0; i<max; i++) {
        if(a[i] != b[i] || i >= min)
            count ++;
    }
    return count % MAX_SIZE;
}

entry *findName(char lastname[], entry *pHead)
{
    int distance;
    while (pHead != NULL) {
        distance = dist(lastname , pHead->lastName);
        if (strcasecmp(lastname, pHead->lastName) == 0) {
            return pHead;
        }
        pHead = pHead -> pNext[distance];
    }
    return NULL;
}

void append(char lastName[],entry *e)
{
    while(e!=NULL) {
        int distance = dist(lastName , e->lastName);
        if(e->pNext[distance] != NULL)
            e = e->pNext[distance];
        else {
            e->pNext[distance] = (entry *) malloc(sizeof(entry));
            e = e->pNext[distance];
            strcpy(e->lastName, lastName);
            for(int i=0; i<MAX_SIZE; i++)
                e->pNext[i] = NULL;
            return;
        }
    }
}
