#!/bin/bash

BIN_DIR := bin
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/object
DEP_DIR := $(BUILD_DIR)/dependency
TEST_DIR := test

TARGET := $(BIN_DIR)/interpreter

SRC_EXT := cpp

SRCS := $(shell find $(SRC_DIR) -type f -name '*.$(SRC_EXT)')
OBJS := $(SRCS:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)
INCLUDES := $(shell find $(INC_DIR) -type d)
TEST := test1.c

CC := g++
LD := g++

CFLAGS := -g -Wall -Wextra -std=c++23
CPPFLAGS := $(foreach dir,$(INCLUDES),-I$(dir))
DEPFLAGS = -MMD -MT $@ -MF $(@:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)
LDFLAGS :=

all: $(TARGET)

#Linking
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

#Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) | $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(@D) $(@D:$(OBJ_DIR)%=$(DEP_DIR)%)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(DEPFLAGS)


$(OBJ_DIR) $(DEP_DIR) $(BIN_DIR):
	@mkdir -p $@

-include $(DEPS)

run: $(TARGET)
	@$< $(TEST_DIR)/$(TEST)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean run valrun