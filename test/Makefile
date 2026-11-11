.SUFFIXES:
MAKEFLAGS += --no-builtin-rules


#NO DEBS IN THIS MAKEFILE, IM LAZY, REMEMBER .h ARE NOT UPDATED AUTOMATICALY

CFLAGS := -Wall -Wextra -g #-D DEBUG_ON

#output file names
TEST_INPUT_TERM			:= test_input
TEST_RENDER_TERM_NATIVE	:= test_render_native
TEST_RENDER_API			:= test_render_api
TEST_GENERIC			:= test_generic

OUTPUT_FILES_TO_CLEAN := $(TEST_INPUT_TERM) $(TEST_RENDER_TERM_NATIVE)\
						 $(TEST_RENDER_API) $(TEST_GENERIC)

#input main files names
MAIN_INPUT_TERM			:= input_test.c
MAIN_RENDER_TERM_NATIVE	:= render_native_test.c
MAIN_RENDER_API			:= render_api_test.c
MAIN_GENERIC			:= generic_test.c

.PHONY: all

all: $(TEST_INPUT_TERM) $(TEST_RENDER_TERM_NATIVE) $(TEST_RENDER_API) $(TEST_GENERIC)




INPUT_TERM_FILES	:= $(MAIN_INPUT_TERM) ../src/input_term_native.c ../src/debug.c
RENDER_NATIVE_FILES	:= ../src/render_term_native.c ../src/debug.c
RENDER_API_FILES	:= $(RENDER_NATIVE_FILES) 	\
						../src/render_factory.c \
						../src/render_term_binding_to_api.c \
						../src/debug.c



$(TEST_INPUT_TERM): $(INPUT_TERM_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
$(TEST_RENDER_TERM_NATIVE): $(MAIN_RENDER_TERM_NATIVE) $(RENDER_NATIVE_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
$(TEST_RENDER_API): $(MAIN_RENDER_API) $(RENDER_API_FILES)
	gcc $(CFLAGS) -I../include $^ -o $@
	
	
$(TEST_GENERIC): $(MAIN_GENERIC) ../src/debug.c
	gcc $(CFLAGS) -I../include $^ -o $@
	
.PHONY: clean

clean:
	rm $(OUTPUT_FILES_TO_CLEAN)
