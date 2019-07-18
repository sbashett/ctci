#include <iostream>
#include <cassert>

using namespace std;

enum BoxState{
	EMPTY = 0,
	STATE1 = 1,
	STATE2 = 2
};

class TicTacBoard{
	const int n;

public:
	BoxState *board;

	TicTacBoard();
	TicTacBoard(int);
	int getBoardSize();
	void createBoard();
	void checkInputValid(int, int);
	BoxState getState(int, int);
	BoxState modifyState(int, int, BoxState);

	~TicTacBoard();
};

TicTacBoard::TicTacBoard() : n(3), board(new BoxState[n*n]) {}
// TicTacBoard::TicTacBoard(int n) : n(n), board{new BoxState[n][n]} {}
TicTacBoard::TicTacBoard(int n) : n(n), board(new BoxState[n*n]) {}
TicTacBoard::~TicTacBoard(){
	delete[] board;
}

int TicTacBoard::getBoardSize(){ return n;}

void checkInputValid(int row, int col){
	assert((row >= n, "row exceeded the range of n", col >=n, "col exceeded range of n"));
	return;	
}

BoxState TicTacBoard::getState(int row, int col){
	checkInputValid(row, col);
	return board[row*n + col];
}

BoxState modifyState(int row, int col, BoxState newState){
	checkInputValid(row, col);
	int index = row*n + col; 
	BoxState ret_val = board[index];
	board[index] = newState;

	return ret_val;
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){

	TicTacBoard board; //array indexing from zero

	cout << board.getBoardSize() << '\n';
	cout << board.board[0] << '\n';

	return 0;

}