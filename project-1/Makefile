build:
	docker build --platform linux/amd64 -t c-dev .

run:
	docker run --platform linux/amd64 --rm -it -v "$(shell pwd)":/workspace c-dev

all:
	make build
	make run

valgrind:
	gcc -g -O0 -Wall -Wextra -Wpedantic -pthread *.c -o main && \
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		./main

compile:
	gcc -g *.c -o main && ./main
