PROG_NAME = libh.a
FILES := $(wildcard *.c)
OBJECTS = stack.o ternary_tree.o

# build libh as static lib
$(PROG_NAME): $(OBJECTS)
	ar rcs $@ $^

all: $(FILES)
	$(CC) -O -c $?

clean: $(OBJECTS) $(PROG_NAME)
	rm $^
