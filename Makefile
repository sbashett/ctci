all: run.exe

run.exe: run.o
	g++ -Wall -Wextra -Werror -o run.exe run.o

run.o: ${IN_FILE}
	g++ -Wall -Wextra -Werror -c ${IN_FILE} -o run.o

clean:
	rm run.exe run.o
