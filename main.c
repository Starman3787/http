#include <stdio.h>
#include <stdint.h>
#include "./response_parser/response_parser.c"
#include "./http_response_status/http_response_status.c"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);
    uint16_t status = http_response_status(response);
    printf("%lu\n", status);
}