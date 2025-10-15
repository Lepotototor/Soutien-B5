CC=gcc
CFLAGS=-Wall -Wextra -Wvla -Werror -g -fsanitize=address
LDFLAGS=-fsanitize=address

SRC=main.c array_even.c merge_blocks.c get_childs.c str_to_upper.c resize_tab.c
OBJ=$(SRC:.c=.o)
BIN=dragons

all: CPPFLAGS = -DMERGE_BLOCKS -DARRAY_EVEN -DGET_CHILDS -DSTR_TO_UPPER -DRESIZE_TAB
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ): $(SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

merge_blocks: CPPFLAGS += -DMERGE_BLOCKS
merge_blocks: $(BIN)
	./$(BIN)

array_even: CPPFLAGS += -DARRAY_EVEN
array_even: $(BIN)
	./$(BIN)

get_childs: CPPFLAGS += -DGET_CHILDS
get_childs: $(BIN)
	./$(BIN)

str_to_upper: CPPFLAGS += -DSTR_TO_UPPER
str_to_upper: $(BIN)
	./$(BIN)

resize_tab: CPPFLAGS += -DRESIZE_TAB
resize_tab: $(BIN)
	./$(BIN)


clean:
	$(RM) $(OBJ) $(BIN)
