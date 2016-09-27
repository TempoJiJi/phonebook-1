#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>


#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
#if defined(BK)
    /* Initialize head node */
    strcpy(pHead -> lastName,"aaaaaa");
    for(i=0; i<MAX_SIZE; i++)
        e->pNext[i] = NULL;
#else
    e->pNext = NULL;
#endif

#if defined(OPT)
    hash_table *my_hash_table;
    my_hash_table = create_hash_table();
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
#if defined(OPT)
    unsigned int size;
    struct stat buf;
    /* O_RDONLY = read only */
    int fd = open (DICT_FILE,O_RDONLY);

    /* Get the size of the file */
    int status = fstat(fd, &buf);
    size = buf.st_size;

    clock_gettime(CLOCK_REALTIME, &start);
    char *s = mmap(0,size,PROT_READ,MAP_PRIVATE,fd,0);
    int k = 0;
    for(i = 0; i < size; i++) {
        line[k] = s[i];
        if(s[i] == 10) {
            line[k] = '\0';
            k = 0;
            append(line,my_hash_table);
            continue;
        }
        k++;
    }

#elif defined(BK)
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        e = pHead;
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        append(line,e);	//for OPT
    }
#else
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);	//for ORI
    }
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";

    e = pHead;

#if defined (OPT)
    assert(findName(input,my_hash_table) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, my_hash_table)->lastName, "zyxel"));
#elif !defined(FUZ)
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
#if defined(OPT)
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input,my_hash_table);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#else
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#endif

    FILE *output;
#if defined(OPT)
    output = fopen("opt.txt", "a");
#else
    output = fopen("orig.txt", "a");
#endif
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    return 0;
}
