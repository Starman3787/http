#ifndef HTTP_BODY_STRUCTURES_H
#define HTTP_BODY_STRUCTURES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum contenttype {
    HEADER_CONTENT_TYPE_TEXT_PLAIN,
    HEADER_CONTENT_TYPE_APPLICATION_JSON
} ContentType;

typedef enum jsontype {
    JSON_NUMBER,
    JSON_STRING,
    JSON_BOOLEAN,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct json Json;

struct json {
    char *key;
    JsonType type;
    union {
        int64_t json_number;
        char *json_string;
        bool json_boolean;
        struct Json **json_array;
        struct Json **json_object;
    } data;
    size_t child_size;
};

typedef struct body {
    ContentType content_type;
    union {
        Json **data_json;
        char *data_text;
    } data;
    size_t data_size;
} Body;

void skip_whitespace(const char **cursor);
char *get_property_name(const char **cursor);
char *get_string(const char **cursor, size_t *size);
bool get_boolean(const char **cursor, size_t *size);
Json **get_array(const char **cursor, size_t *size);
Json **get_object(const char **cursor, size_t *size);
Json *parse_element(const char **cursor);

void display_json(Json **jsonBody, const size_t child_size);
void free_json(Json ***jsonBody, size_t child_size);

#endif