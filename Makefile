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
          -Wconversion

LIBS = -lm

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
