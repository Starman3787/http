#ifndef FUNCTION_DECLARATIONS_H
#define FUNCTION_DECLARATIONS_H

#include <stdint.h>
#include <time.h>
#include "../http_body_parser/http_body_structures.h"
#include "../http_header_parser/http_header_structures.h"

char *response_parser(void);
uint16_t http_response_status(char *rawHttp);
Header **http_header_parser(char *rawHttp, uint8_t *headerIndex, char **headersEnd);
void display_headers(Header **headers, uint8_t headersLength);
Body *http_body_parser(char *rawBody, Header **headers, uint8_t headersLength);
void display_body(Body *parsedBody);
void free_body(Body **parsedBody);
Header *find_header(Header **headers, uint8_t headersLength, char *key);
time_t parse_date(char *date);
void free_headers(Header ***headers, uint8_t headersLength);
void to_lower_case(char *characters);
bool read_next_and_expect(char *pattern, uint16_t startPositionOffset);
int64_t convertMonth(char *month);
time_t parse_date(char *date);
uint8_t hex_char_to_int(char hex);
uint32_t hex_to_int(char *hex);
void free_json(Json ***jsonBody, size_t child_size);
uint16_t find_pattern(const char *pattern, const size_t patternLength);
void display_json(Json **jsonBody, const size_t child_size);
char **split_header_values(char *headerValue, uint8_t *values, const char splitBy);
void skip_whitespace(char **cursor);
char *get_property_name(char **cursor);
char *get_string(char **cursor, size_t *size);
bool get_boolean(char **cursor, size_t *size);
Json **get_array(char **cursor, size_t *size);
Json **get_object(char **cursor, size_t *size);
Json *parse_element(char **cursor);
Json **parse_json(char *body, size_t *size);
char *chunked(char *httpNoHeaders, size_t *outputLength);

#endif