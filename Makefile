CC := gcc

CFLAGS := -O2 \
          -Wall \
          -Wextra \
          -Wformat=2 \
          -Wformat-overflow \
          -Wformat-truncation \
          -Wshadow \
          -Wdouble-promotion \
          -Wundef \
          -fno-common \
          -z noexecstack \
          -Wconversion \
          -g

SRC := main.c
TARGET := bin/main
INSTALL_DIR := ~/.local/bin

.PHONY: build deploy

build: create_dir $(TARGET)

create_dir:
	mkdir -p bin

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

deploy: $(INSTALL_DIR)/tagger

$(INSTALL_DIR)/tagger: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: build
	$(TARGET)

cppcheck:
	cppcheck --enable=all --inconclusive --force --suppress=unusedFunction .

valgrind:
	 valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 -s --track-fds=yes  --track-origins=yes ./bin/main
