all: run.exe

run.exe: run.o common_header.o common_graphs_trees.o
	g++ -Wall -Wextra -Werror -o run.exe run.o common_header.o common_graphs_trees.o

run.o: ${IN_FILE} 
	g++ -Wall -Wextra -Werror -c ${IN_FILE} -o run.o

common_header.o: common_header.cpp
	g++ -Wall -Wextra -Werror -c common_header.cpp -o common_header.o

common_graphs_trees.o: common_graphs_trees.cpp
	g++ -Wall -Wextra -Werror -c common_graphs_trees.cpp -o common_graphs_trees.o

clean:
	rm run.exe run.o common_header.o common_graphs_trees.o
