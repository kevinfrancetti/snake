.SUFFIXES:
MAKEFLAGS += --no-builtin-rules


TEST_INPUT_TERM := test_input
TEST_RENDER_TERM := test_render
TEST_RENDER_TERM_NATIVE := test_render_native


.PHONY: all

all: $(TEST_INPUT_TERM) $(TEST_RENDER_TERM_NATIVE)

$(TEST_INPUT_TERM):
	gcc -Wall -g -I../include input_test.c ../src/input_term.c -o $@
	
	
	
RENDER_FILES := render_test.c ../src/render_term.c ../src/render_factory.c

	
$(TEST_RENDER_TERM): $(RENDER_FILES)
	gcc -Wall -g -I../include $^ -o $@
	
	
	
RENDER_NATIVE_FILES := render_native_test.c ../src/render_term_native.c


$(TEST_RENDER_TERM_NATIVE): $(RENDER_NATIVE_FILES)
	gcc -Wall -g -I../include $^ -o $@
	
	
.PHONY: clean

clean:
	rm $(TEST_INPUT_TERM)
