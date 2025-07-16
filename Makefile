
build_chronometer: chronometer.c
	mkdir -p out
	gcc chronometer.c -Wall -O0 -L./lib -l:./lib.so -o ./out/chronometer
	cp ./lib/lib.so out/lib.so

run:
	LD_LIBRARY_PATH=./lib ./out/chronometer

pdf:
	pandoc relation.md -o relation.pdf

zip:
	zip project.zip chronometer.c Makefile dataparser.py lib/* lib/alg/quickSort.c lib/alg/quickSort3w.c lib/alg/quickSortSelect.c lib/alg/quicksortUtils.c lib/alg/countingSort.c lib/alg/mergeSort.c

clean:
	rm -f ./out/*
