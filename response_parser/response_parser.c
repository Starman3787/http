#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../data/esp001s_response.h"
#include "../util/find_pattern.c"
#include "../util/read_next_and_expect.c"

char *response_parser(void)
{
    char *fullRawResponse = malloc(1);
    *fullRawResponse = '\0';
    size_t currentResponseSize = 1;
    uint16_t responseStart = find_pattern("+IPD,", 5);
    while (1)
    {
        uint16_t currentChunkLength;
        char currentCharacter = *(rawResponse + responseStart);
        char *rawChunkLength = malloc(2);
        uint8_t counter;
        for (counter = 0; currentCharacter != ':'; counter++)
        {
            rawChunkLength = realloc(rawChunkLength, counter + 2);
            *(rawChunkLength + counter) = currentCharacter;
            *(rawChunkLength + counter + 1) = '\0';
            currentCharacter = *(rawResponse + responseStart + counter + 1);
        }
        char *endOfRawChunkLengthString = rawChunkLength + counter + 1;
        currentChunkLength = strtoul(rawChunkLength, &endOfRawChunkLengthString, 10) + 1;
        free(rawChunkLength);
        char *chunk = malloc(currentChunkLength);
        uint16_t bodyCounter;
        for (bodyCounter = 0; bodyCounter < currentChunkLength - 1; bodyCounter++)
            *(chunk + bodyCounter) = *(rawResponse + responseStart + counter + 1 + bodyCounter);
        *(chunk + currentChunkLength - 1) = '\0';
        currentResponseSize += currentChunkLength - 1;
        fullRawResponse = realloc(fullRawResponse, currentResponseSize);
        strcat(fullRawResponse, chunk);
        free(chunk);
        *(fullRawResponse + currentResponseSize + currentChunkLength - 1) = '\0';
        printf("%s\n", fullRawResponse);
        if (!read_next_and_expect("\r\n+IPD,", responseStart + counter + 1 + bodyCounter))
            break;
        responseStart = responseStart + counter + 1 + bodyCounter + 7;
    }
    return fullRawResponse;
}