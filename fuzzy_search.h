#ifndef _FUZZY_SEARCH_H
#define _FUZZY_SEARCH_H

#define FUZ 1
#define MAX_LAST_NAME_SIZE 16
#define MAX_SIZE 2

/* fuzzy_search version */

typedef struct __DETAILS {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} Details;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    Details *details;
} entry;

void findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
