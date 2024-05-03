EXECUTABLE_FILE = ziplib_test

.PHONY: all clean run

all: clean build
	@cd build && cmake .. && cmake --build .

build:
	@mkdir -p build

run:
	@./build/Debug/$(EXECUTABLE_FILE)

clean:
	@rm -rf build out 