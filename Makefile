.SUFFIXES:
MAKEFLAGS += --no-builtin-rules
#Last modification 17.11.2025

#config
GCC := gcc
AR := ar


#Directory structure
SRC_DIR := src
BUILD_DIR := build
BUILD_OBJ_DIR := $(BUILD_DIR)/obj
INCLUDE_DIR := include


#Compiler flags
INCLUDES := -I$(INCLUDE_DIR) 
CFLAGS := -Wall -MMD $(INCLUDES) -g -c

#Linker flags
LDLIBS := 
LDFLAGS := 

PROGRAM_NAME := $(BUILD_DIR)/main

srcs := $(wildcard $(SRC_DIR)/*.c)
objs := $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o, $(srcs))
deps := $(patsubst $(BUILD_OBJ_DIR)/%.o,$(BUILD_OBJ_DIR)/%.d, $(objs))



$(PROGRAM_NAME): $(objs)
	$(GCC) $^ $(LDLIBS) $(LDFLAGS) -o $@



.PHONY: object_files
object_files: $(objs)

.PHONY: debug
debug: CFLAGS += -g
debug: $(PROGRAM_NAME)

.PHONY: create_directory
create_directory: | $(BUILD_OBJ_DIR) $(SRC_DIR) $(INCLUDE_DIR)


$(BUILD_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_OBJ_DIR)
	$(GCC) $(CFLAGS)  $< -o $@


$(BUILD_OBJ_DIR) $(SRC_DIR) $(INCLUDE_DIR):
	mkdir -p $@


.PHONY: clean
clean:
	rm  $(objs) $(STATIC_LIB_NAME) $(deps) $(PROGRAM_NAME) test/maintest maintest.o
	
	
print:
	@echo "srcs:$(srcs)"
	@echo "objs:$(objs)"
	@echo "deps:$(deps)"
	@echo $(STATIC_DIR)
	@echo $(SRC_DIR)
	@echo $(BUILD_DIR)
	@echo $(BUILD_OBJ_DIR)


-include $(deps)
