#include <stdlib.h>
#include <stdio.h>
#include "../../http_body_parser/http_body_structures.h"

void free_json(Json ***jsonBody, size_t child_size)
{
    uint16_t child_elements = child_size / sizeof(Json *);
    printf("%d\n", child_elements);
    for (uint16_t i = 0; i < child_elements; i++)
    {
        if ((*(*jsonBody + i))->key)
            printf("FREEING KEY: %s\n", (*(*jsonBody + i))->key);
        free((*(*jsonBody + i))->key);
        switch ((*(*jsonBody + i))->type)
        {
        case JSON_NUMBER:
            // number data is not a pointer, nothing to do here
            break;
        case JSON_STRING:
            printf("FREEING STRING: %s\n", (*(*jsonBody + i))->data.json_string);
            free((*(*jsonBody + i))->data.json_string);
            break;
        case JSON_BOOLEAN:
            // boolean data is not a pointer, nothing to do here
            break;
        case JSON_ARRAY:
            puts("FREEING ARRAY");
            free_json(&(*(*jsonBody + i))->data.json_array, (*(*jsonBody + i))->child_size);
            break;
        case JSON_OBJECT:
            puts("FREEING OBJECT");
            free_json(&(*(*jsonBody + i))->data.json_array, (*(*jsonBody + i))->child_size);
            break;
        }
        puts("FREEING JSON");
        free((*(*jsonBody + i)));
    }
    free(*jsonBody);
}