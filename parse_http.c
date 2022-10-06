#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "http_parser.h"


#define MAXCHAR 9000

void parse_http()
{
    char str[MAXCHAR];
    FILE* ptr = fopen("index.html", "r");
    char ch[1];

    do {
        ch[0] = fgetc(ptr);
        strncat(str, ch, 1);
    } while (ch[0] != EOF);

    printf("%s", str);




    /* if (NULL == ptr) { */
    /*     printf("file can't be opened \n"); */
    /* } */
    /* fgets(str, MAXCHAR, ptr); */
    /* printf("%s", str); */
    /* printf("hola"); */
    fclose(ptr);

    /* /\* Find out where everything is *\/ */
    /* const char *start_of_path = strchr(request, ' ') + 1; */
    /* const char *start_of_query = strchr(start_of_path, '?'); */
    /* const char *end_of_query = strchr(start_of_query, ' '); */

    /* /\* Get the right amount of memory *\/ */
    /* char path[start_of_query - start_of_path]; */
    /* char query[end_of_query - start_of_query]; */

    /* /\* Copy the strings into our memory *\/ */
    /* strncpy(path, start_of_path,  start_of_query - start_of_path); */
    /* strncpy(query, start_of_query, end_of_query - start_of_query); */

    /* /\* Null terminators (because strncpy does not provide them) *\/ */
    /* path[sizeof(path)] = 0; */
    /* query[sizeof(query)] = 0; */

    /* /\*Print *\/ */
    /* printf("%s\n", query); */
    /* printf("%s\n", path); */

};
