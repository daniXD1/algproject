
build_chronometer: chronometer.c
	gcc chronometer.c -Wall -O0 -L./lib -l:lib.so -o ./out/chronometer

run:
	LD_LIBRARY_PATH=./lib ./out/chronometer

clean:
	rm -f ./out/*