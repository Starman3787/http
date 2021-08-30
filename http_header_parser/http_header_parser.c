#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include "./http_header_structures.h"
#include "http_function_declarations.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

/**
 * @brief Extracts the headers from a raw HTTP response, and returns a pointer to an array of pointers to Header structures.
 * 
 * @param *rawHttp A pointer to the zeroth index of the raw HTTP response.
 * @param *headerIndex A pointer which will contain the value of the number of headers extracted from this response.
 * @return struct Header** 
 */
Header **http_header_parser(char *rawHttp, uint8_t *headerIndex, char **headersEnd)
{
    Header **allHeaders;
    if ((allHeaders = malloc(sizeof(Header *) * 1)) == NULL)
        return NULL;
    while (!(*rawHttp == '\r' && *(rawHttp + 1) == '\n'))
        rawHttp++;
    rawHttp += 2;
    *headerIndex = 0;
    while (1)
    {
        if (*rawHttp == '\r' && *(rawHttp + 1) == '\n')
            break;
        if ((allHeaders = realloc(allHeaders, sizeof(Header *) * (*headerIndex + 1))) == NULL)
        {
            free_headers(&allHeaders, *headerIndex);
            return NULL;
        }
        char *key;
        if ((key = malloc(sizeof(char))) == NULL)
        {
            free_headers(&allHeaders, *headerIndex);
            return NULL;
        }
        *key = '\0';
        uint8_t keyLength;
        rawHttp++;
        for (keyLength = 1; *(rawHttp - 1) != ':'; keyLength++)
        {
            if ((key = realloc(key, sizeof(char) * (keyLength + 1))) == NULL)
            {
                free(key);
                free_headers(&allHeaders, *headerIndex);
                return NULL;
            }
            *(key + keyLength - 1) = (char)tolower(*(rawHttp - 1));
            *(key + keyLength) = '\0';
            rawHttp++;
        }
        char *value;
        if ((value = malloc(sizeof(char))) == NULL)
        {
            free(key);
            free_headers(&allHeaders, *headerIndex);
            return NULL;
        }
        *value = '\0';
        uint8_t valueLength;
        rawHttp += 2;
        for (valueLength = 1; !(*(rawHttp - 1) == '\r' && *rawHttp == '\n'); valueLength++)
        {
            if ((value = realloc(value, sizeof(char) * (valueLength + 1))) == NULL)
            {
                free(value);
                free(key);
                free_headers(&allHeaders, *headerIndex);
                return NULL;
            }
            *(value + valueLength - 1) = *(rawHttp - 1);
            *(value + valueLength) = '\0';
            rawHttp++;
        }
        if ((*(allHeaders + *headerIndex) = malloc(sizeof(Header))) == NULL)
        {
            free(value);
            free(key);
            free_headers(&allHeaders, *headerIndex);
            return NULL;
        }
        (*(allHeaders + *headerIndex))->key = key;
        (*(allHeaders + *headerIndex))->value = value;
        rawHttp++;
        (*headerIndex)++;
    }
    *headersEnd = ++rawHttp;
    return allHeaders;
}