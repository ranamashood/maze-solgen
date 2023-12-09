CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR) -lSDL2 -lm

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
TARGET = $(BUILD_DIR)/$(LINK)
LINK= maze-solgen

all: $(TARGET) $(LINK)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(LINK):
	ln -sf $(TARGET) $(LINK)

clean:
	rm -rf $(BUILD_DIR) $(LINK)
