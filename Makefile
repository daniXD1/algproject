
build_chronometer: chronometer.c
	gcc chronometer.c -Wall -O0 -L./lib -l:./lib.so -o ./out/chronometer
	cp ./lib/lib.so out/lib.so

run:
	LD_LIBRARY_PATH=./lib ./out/chronometer

clean:
	rm -f ./out/*