#include <stdio.h>
#include "../../http_body_parser/http_body_structures.h"
#include "http_function_declarations.h"

void display_json(Json **jsonBody, const size_t child_size)
{
    uint16_t child_elements = child_size / sizeof(Json *);
    printf("%d\n", child_elements);
    for (uint16_t i = 0; i < child_elements; i++)
    {
        switch ((*(jsonBody + i))->type)
        {
        case JSON_NUMBER:
            printf("%s: %ld\n", (*(jsonBody + i))->key, (*(jsonBody + i))->data.json_number);
            break;
        case JSON_STRING:
            printf("%s: \"%s\"\n", (*(jsonBody + i))->key, (*(jsonBody + i))->data.json_string);
            break;
        case JSON_BOOLEAN:
            printf("%s: %s\n", (*(jsonBody + i))->key, (*(jsonBody + i))->data.json_boolean ? "true" : "false");
            break;
        case JSON_ARRAY:
            if ((*(jsonBody + i))->key)
                printf("%s:", (*(jsonBody + i))->key);
            puts("[");
            display_json((*(jsonBody + i))->data.json_array, (*(jsonBody + i))->child_size);
            puts("]");
            break;
        case JSON_OBJECT:
            if ((*(jsonBody + i))->key)
                printf("%s:", (*(jsonBody + i))->key);
            puts("{");
            display_json((*(jsonBody + i))->data.json_object, (*(jsonBody + i))->child_size);
            puts("}");
            break;
        }
    }
}