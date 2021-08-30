# Simple HTTP Parser

This is supposed to provide a simple way of parsing basic HTTP and relevant HTTP content types.

This has been made specifically for use with a limited set of controlled responses, so is definitely something that should be thoroughly tested for your own use case first, or an alternative HTTP parser should be used.

Only HTTP/1.1 is supported for now.

## Using the HTTP Parser

There are a variety of functions which allow different pieces of information to be extracted from the HTTP response.

- `uint16_t http_response_status(char *rawHttp)`: Extracts the HTTP response status code and returns it as an unsigned 16 bit integer, and a response of `0` if invalid HTTP or HTTP version is provided.

- `Header **http_header_parser(char *rawHttp, uint8_t *headerLength, const char **headersEnd)`: Extracts all the HTTP headers on this response. Returns a pointer to an array of `Header` structs. A pointer to an unsigned 8 bit integer should also be passed as the second parameter. This will be set to the number of headers that are in the array, and that were attached to the HTTP response. The final parameter should be a pointer to a `char`. This pointer will be set to where the headers end. This just simplifies further function calls, saves time, and many of the other function calls rely on being able to read the parsed headers.

- `Body *http_body_parser(char *rawBody, const Header **headers, uint8_t *headersLength)`: Parses the HTTP body. The headers are required so the content type can be determined and it can be parsed correctly.

## Structures

- `Header`:

```c
typedef struct header {
    char *key;
    char *value;
} Header;
```

Simply contains the key and value of the header.

- `Body`:

```c
typedef struct body {
    ContentType content_type;
    union {
        Json **data_json;
        char *data_text;
    } data;
    size_t data_size;
} Body;
```

Contains information about the type of content that the body contains, the actual data in the body, as well as the size of the first level of the data.

- `ContentType`:

```c
typedef enum contenttype {
    HEADER_CONTENT_TYPE_TEXT_PLAIN,
    HEADER_CONTENT_TYPE_APPLICATION_JSON
} ContentType;
```

Indicates the type of content that the body data holds. Based on the headers of the response.

- `Json`:

```c
typedef struct json Json;

struct json {
    char *key;
    JsonType type;
    union {
        int64_t json_number;
        char *json_string;
        bool json_boolean;
        Json **json_array;
        Json **json_object;
    } data;
    size_t child_size;
};
```

Contains information about the JSON data within the body. An array and an object are represented in essentially the same way; the data is a pointer to an array of more `Json` structures. The `child_size` field is simply the count of top-level child structures.

- `JsonType`:

```c
typedef enum jsontype {
    JSON_NUMBER,
    JSON_STRING,
    JSON_BOOLEAN,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;
```

Indicates the type of data that the JSON snippet contains.
