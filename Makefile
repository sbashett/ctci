all: run

run: run.o
	g++ -Wall -Wextra -Werror -o run run.o

run.o: ${IN_FILE}
	g++ -Wall -Wextra -Werror -c ${IN_FILE} -o run.o

clean:
	rm run run.o
