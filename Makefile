all: run.exe

run.exe: run.o common_header.o
	g++ -Wall -Wextra -Werror -o run.exe run.o common_header.o

run.o: ${IN_FILE} 
	g++ -Wall -Wextra -Werror -c ${IN_FILE} -o run.o

common_header.o: common_header.cpp
	g++ -Wall -Wextra -Werror -c common_header.cpp -o common_header.o

clean:
	rm run.exe run.o common_header.o
