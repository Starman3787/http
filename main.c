#include <stdio.h>
#include "./response_parser/response_parser.c"
#include "./data/esp001s_response.h"

void main(void)
{
    char *response = response_parser();
    printf("%s\n", response);
}