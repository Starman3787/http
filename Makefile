TARGET = main

CC = /usr/bin/gcc

# C compilation directives
CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -g3
CFLAGS += -O2
CFLAGS += -std=c17
CLFAGS += -D_FORTIFY_SOURCE=2
CFLAGS += -Wno-sequence-point
CFLAGS += -lm
# CFLAGS += -DDMALLOC
# CFLAGS += -DDMALLOC_FUNC_CHECK
CFLAGS += -DMALLOC_DISABLE

C_SRC = ./main.c
C_SRC += ./response_parser/response_parser.c
C_SRC += ./http_response_status/http_response_status.c
C_SRC += ./http_header_parser/http_header_parser.c
C_SRC += ./http_header_parser/split_header_values.c
C_SRC += ./http_body_parser/http_body_parser.c
C_SRC += ./http_body_parser/encoding/chunked.c
C_SRC += ./http_body_parser/types/json.c
C_SRC += ./util/free_body/free_body.c
C_SRC += ./util/free_headers/free_headers.c
C_SRC += ./util/free_json/free_json.c
C_SRC += ./util/display_headers/display_headers.c
C_SRC += ./util/display_body/display_body.c
C_SRC += ./util/display_json/display_json.c
C_SRC += ./util/find_header/find_header.c
C_SRC += ./util/parse_date/parse_date.c
C_SRC += ./util/find_pattern/find_pattern.c
C_SRC += ./util/hex_to_int/hex_to_int.c
C_SRC += ./util/read_next_and_expect/read_next_and_expect.c

LFLAGS = -Wall
LFLAGS += -Wextra
LFLAGS += -lm
# LFLAGS += -ldmallocth

OBJS = $(C_SRC:.c=.o)

.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) -Iheaders/ -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)