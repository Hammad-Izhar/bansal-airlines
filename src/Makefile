all:
	mkdir -p bin
	g++ column-major.cpp -o bin/column-major -g -Wall -Wextra -pedantic -std=c++11
	g++ row-major.cpp -o bin/row-major -g -Wall -Wextra -pedantic -std=c++11
	g++ strassen.cpp -o bin/strassen -g -Wall -Wextra -pedantic -std=c++11

all-c:
	mkdir -p bin
	gcc column-major.c -o bin/column-major -g -Wall -Wextra -pedantic
	gcc row-major.c -o bin/row-major -g -Wall -Wextra -pedantic
	gcc strassen.c -o bin/strassen -g -Wall -Wextra -pedantic