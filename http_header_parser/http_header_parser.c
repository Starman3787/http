#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./http_header_structures.h"

struct Header **http_header_parser(char *rawHttp, uint8_t *headerIndex)
{
    struct Header **allHeaders = malloc(1 * sizeof(struct Header *));
    while (!(*rawHttp == '\r' && *(rawHttp + 1) == '\n'))
        rawHttp++;
    rawHttp += 2;
    (*headerIndex) = 0;
    while (1)
    {
        if (*rawHttp == '\r' && *(rawHttp + 1) == '\n')
            break;
        allHeaders = realloc(allHeaders, ((*headerIndex) + 1) * sizeof(struct Header *));
        char *key = malloc(1);
        *key = '\0';
        uint8_t keyLength;
        rawHttp++;
        for (keyLength = 1; *(rawHttp - 1) != ':'; keyLength++)
        {
            key = realloc(key, keyLength + 1);
            *(key + keyLength - 1) = *(rawHttp - 1);
            *(key + keyLength) = '\0';
            rawHttp++;
        }
        char *value = malloc(1);
        *value = '\0';
        uint8_t valueLength;
        rawHttp++;
        for (valueLength = 1; !(*(rawHttp - 1) == '\r' && *rawHttp == '\n'); valueLength++)
        {
            value = realloc(value, valueLength + 1);
            *(value + valueLength - 1) = *rawHttp;
            *(value + valueLength) = '\0';
            rawHttp++;
        }
        allHeaders[*headerIndex] = malloc(sizeof(struct Header));
        allHeaders[*headerIndex]->key = key;
        allHeaders[*headerIndex]->value = value;
        rawHttp++;
        (*headerIndex)++;
    }
    return allHeaders;
}