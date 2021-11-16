CC := gcc
CFLAGS := -O3 -W -Wall -Wextra -std=c99

.PHONY: all
all: main

BUILD_DIR := build
SRC_DIR := src

C_FILES := $(wildcard $(SRC_DIR)/*.c)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
#DEP_FILES = $(OBJ_FILES:%.o=%.d)
#-include $(DEP_FILES)

main: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lm -Iinclude

clean:
	rm -rf main build

all: main
