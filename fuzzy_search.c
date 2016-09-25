#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#include "fuzzy_search.h"

int dist(char *a,char *b)
{
    int count = 0;
    int max = MAX(strlen(a),strlen(b));
    int min = MIN(strlen(a),strlen(b));
    for(int i=0; i<max; i++) {
        if(a[i] != b[i] || i >= min)
            count ++;
    }
    return count;
}

void findName(char lastname[], entry *pHead)
{
    int distance;
    while (pHead != NULL) {
        distance = dist(lastname , pHead->lastName);
        if(distance <= 2) {
            printf("intput=%s , %s , dist=%d\n",lastname,pHead->lastName,distance);
        }
        pHead = pHead -> pNext;
    }
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}
