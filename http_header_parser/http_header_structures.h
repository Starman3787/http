#ifndef HTTP_HEADER_STRUCTURES_H
#define HTTP_HEADER_STRUCTURES_H

typedef struct header {
    char *key;
    char *value;
} Header;

#endif