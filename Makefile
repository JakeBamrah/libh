LIB_NAME = libh.a
FILES := $(wildcard *.c)
OBJECTS = $(patsubst %.c, build/%.o, $(FILES))

# build libh as static lib
build/$(LIB_NAME): $(OBJECTS)
	ar rcs $@ $^

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $< -c

clean:
	rm -r build
