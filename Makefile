all: build

build:
	@echo "Building chronometer..."
	gcc -o out/chronometer chronometer.c lib/*.c lib/alg/*.c -I. -Wall
	@echo "Build finished."

clean:
	@rm out/*