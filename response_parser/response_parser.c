#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../data/esp001s_response.h"
#include "http_function_declarations.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

/**
 * @brief Function for parsing the response received from an ESP001S WiFi module. Communication with it is done over UART, so each character is treated as if it is received over UART.
 * 
 * @return char* A pointer to the parsed response.
 */
char *response_parser(void)
{
    char *fullRawResponse = malloc(sizeof(char) * 1);
    *fullRawResponse = '\0';
    size_t currentResponseSize = 1;
    uint16_t responseStart = find_pattern("+IPD,", 5);
    while (1)
    {
        uint16_t currentChunkLength;
        char currentCharacter = *(rawResponse + responseStart);
        char *rawChunkLength = malloc(sizeof(char) * 2);
        uint8_t counter;
        for (counter = 0; currentCharacter != ':'; counter++)
        {
            rawChunkLength = realloc(rawChunkLength, sizeof(char) * (counter + 2));
            *(rawChunkLength + counter) = currentCharacter;
            *(rawChunkLength + counter + 1) = '\0';
            currentCharacter = *(rawResponse + responseStart + counter + 1);
        }
        char *endOfRawChunkLengthString = rawChunkLength + counter + 1;
        currentChunkLength = strtoul(rawChunkLength, &endOfRawChunkLengthString, 10);
        free(rawChunkLength);
        char *chunk = malloc(sizeof(char) * (currentChunkLength + 1));
        uint16_t bodyCounter;
        for (bodyCounter = 0; bodyCounter < currentChunkLength; bodyCounter++)
            *(chunk + bodyCounter) = *(rawResponse + responseStart + counter + 1 + bodyCounter);
        *(chunk + currentChunkLength) = '\0';
        currentResponseSize += currentChunkLength;
        fullRawResponse = realloc(fullRawResponse, sizeof(char) * (currentResponseSize + 1));
        strncat(fullRawResponse, chunk, currentChunkLength);
        free(chunk);
        *(fullRawResponse + currentResponseSize) = '\0';
        if (!read_next_and_expect("\r\n+IPD,", responseStart + counter + 1 + bodyCounter))
            break;
        responseStart = responseStart + counter + 1 + bodyCounter + 7;
    }
    return fullRawResponse;
}