#ifndef HTTP_HEADER_STRUCTURES
#define HTTP_HEADER_STRUCTURES

typedef struct header {
    char *key;
    char *value;
} Header;

#endif