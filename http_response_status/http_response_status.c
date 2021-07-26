#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./http_supported.h"

/**
 * @brief Extracts the HTTP status from the raw response.
 * 
 * @param rawHttp A raw HTTP response.
 * @return uint16_t The 3 digit HTTP code.
 */
uint16_t http_response_status(char *rawHttp)
{
    uint8_t index;
    for (index = 0; index < strlen(httpSupported); index++)
        if (*(rawHttp + index) != *(httpSupported + index))
            return 0;
    if (*(rawHttp + index) != ' ')
        return 0;
    index++;
    char *rawHttpStatus = "\0\0\0";
    strncpy(rawHttpStatus, rawHttp + index, 3);
    char *rawHttpStatusEnd = rawHttpStatus + index + 3;
    return strtoul(rawHttpStatus, &rawHttpStatusEnd, 10);
}