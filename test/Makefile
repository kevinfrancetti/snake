.SUFFIXES:
MAKEFLAGS += --no-builtin-rules

CFLAGS := -Wall -g -D DEBUG_ON

#output file names
TEST_INPUT_TERM			:= test_input
TEST_RENDER_TERM_NATIVE	:= test_render_native
TEST_RENDER_API			:= test_render_api

OUTPUT_FILES_TO_CLEAN := $(TEST_INPUT_TERM) $(TEST_RENDER_TERM_NATIVE) $(TEST_RENDER_API)

#input main file names
MAIN_INPUT_TERM			:= input_test.c
MAIN_RENDER_TERM_NATIVE	:= render_native_test.c
MAIN_RENDER_API			:= render_api_test.c

.PHONY: all

all: $(TEST_INPUT_TERM) $(TEST_RENDER_TERM_NATIVE) $(TEST_RENDER_API)




INPUT_TERM_FILES	:= $(MAIN_INPUT_TERM) ../src/input_term_native.c
RENDER_NATIVE_FILES	:= ../src/render_term_native.c
RENDER_API_FILES	:= $(RENDER_NATIVE_FILES) 	\
						../src/render_factory.c \
						../src/render_term_binding_to_api.c 



$(TEST_INPUT_TERM): $(INPUT_TERM_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
$(TEST_RENDER_TERM_NATIVE): $(MAIN_RENDER_TERM_NATIVE) $(RENDER_NATIVE_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
$(TEST_RENDER_API): $(MAIN_RENDER_API) $(RENDER_API_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
	
.PHONY: clean

clean:
	rm $(OUTPUT_FILES_TO_CLEAN)
