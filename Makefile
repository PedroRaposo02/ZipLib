.PHONY: all clean run

all: clean build
	@cd build && cmake .. && cmake --build .

build:
	@mkdir -p build

clean:
	@rm -rf build out 