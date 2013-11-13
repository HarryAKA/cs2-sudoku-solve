/*
 * Sudoku.cpp
 * Name: Harry Kran-Annexstein
 *
 * Implementation for the Sudoku class.
 *
 * Oct 23, 2013
 */
 
#include <iostream>
#include <string>

#include "Sudoku.h"

using namespace std;

const int BOARD_SIZE = 9;

Sudoku::Sudoku(const string& state){
  startstate = state;
  currentstate = startstate;

}

Sudoku::Sudoku(){
  // A default constructor doesn't make any sense in this case, but having this defined
  // here without any code allows a unit test to create a dummy object (with 
  // non-initialized private variables), so that it can test the private functions
  // Takeaway: leave this as is and SudokuTest.h will work as written.
}

void Sudoku::printCurrentBoard(){
	for (unsigned i = 0; i < currentstate.size(); i++) {
		if (i % BOARD_SIZE == 0) {
			cout << endl;
		}
		cout.width(2);
		cout << currentstate[i];
	}
	cout << endl << endl;
}

string Sudoku::getCurrentBoard(){
  return currentstate;
}

string Sudoku::getStartBoard() {
	return startstate;
}

void Sudoku::reset(vector<int> &t) {
	for (unsigned i = 0; i < t.size(); i++) {
		t[i] = 0;
	}
}

bool Sudoku::checkTest(vector<int> t) {
	for (unsigned i = 0; i < t.size(); i++) {
		if (t[i] > 1) {
			return false;
		}
	}
	return true;
}

vector<int> Sudoku::getRegion(int y, int x, const board_t &state) {
	vector<int> region(9);
	board_t board = state;
	for (int row = y; row < y+3; row++) {
		for (int col = x; col < x+3; col++) {
			unsigned index = row*BOARD_SIZE+col;
			int num = board[index] - '0';
			if (num >= 1 && num <= 9) {
				region[num-1]++;
			}
		}
	}
	return region;
}

bool Sudoku::isValid(){
	vector<int> test(9);
	reset(test);
	// Test rows for validity
	for (int i = 0; i < BOARD_SIZE; i++) {
		int row = i*BOARD_SIZE;
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j++) {
			int num = currentstate[row+j] - '0';
			if (num >= 1 && num <= 9) {
				test[num-1]++;
			}
		}if (!checkTest(test)) {
			return false;
		}
	}
	// Test columns for validity
	for (int i = 0; i < BOARD_SIZE; i++) {
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j++) {
			int num = currentstate[j*BOARD_SIZE+i] - '0';
			if (num >= 1 && num <= 9) {
				test[num-1]++;
			}
		}if (!checkTest(test)) {
			return false;
		}
	}
	// Test regions for validity
	for (int i = 0; i < BOARD_SIZE; i+=3) {
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j+=3) {
			test = getRegion(i,j,currentstate);
			if (!checkTest(test)) {
				return false;
			}
		}
	}
  return true;
}

bool Sudoku::isComplete(){
  // FILL ME IN
	for (unsigned i = 0; i < currentstate.size(); i++) {
		if (currentstate[i] == '.') {
			return false;
		}
	}
	if (!isValid()) {
		return false;
	}
	return true;
}

bool Sudoku::solve(){
	if (solve(startstate)) {
		return true;
	}
  return false;
}

void Sudoku::printBoard(const board_t& state){
	board_t board = state;
	for (unsigned i = 0; i < board.size(); i++) {
		if (i % BOARD_SIZE == 0) {
			cout << endl;
		}
		cout.width(2);
		cout << board[i];
	}
	cout << endl << endl;
}

bool Sudoku::isValid(const board_t& state){
	board_t board = state;
	vector<int> test(9);
	reset(test);
	// Test rows for validity
	for (int i = 0; i < BOARD_SIZE; i++) {
		int row = i*BOARD_SIZE;
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j++) {
			int num = board[row+j] - '0';
			if (num >= 1 && num <= 9) {
				test[num-1]++;
			}
		}if (!checkTest(test)) {
			return false;
		}
	}
	// Test columns for validity
	for (int i = 0; i < BOARD_SIZE; i++) {
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j++) {
			int num = board[j*BOARD_SIZE+i] - '0';
			if (num >= 1 && num <= 9) {
				test[num-1]++;
			}
		}if (!checkTest(test)) {
			return false;
		}
	}
	// Test regions for validity
	for (int i = 0; i < BOARD_SIZE; i+=3) {
		reset(test);
		for (int j = 0; j < BOARD_SIZE; j+=3) {
			test = getRegion(i,j,board);
			if (!checkTest(test)) {
				return false;
			}
		}
	}
  return true;
}

bool Sudoku::isComplete(const board_t& state){
	board_t board = state;
	for (unsigned i = 0; i < board.size(); i++) {
		if (board[i] == '.') {
			return false;
		}
	}
	if (!isValid(board)) {
		return false;
	}
  return true;
}

vector<board_t> Sudoku::getSuccessors(const board_t& state){
  vector<board_t> ret;
  board_t board(state);
  unsigned i = 0;
  while (board[i] != '.') {
  	i++;
  }
  if (i < board.size()) {
  	for (int j = 1; j <= BOARD_SIZE; j++) {
  		char num = j + '0';
  		board[i] = num;
  		if (isValid(board)) {
 			  //cout << board << endl;
  		  string temp(board);
  			ret.push_back(temp);
 			}
 		}
  }
  return ret;
 }
 
bool Sudoku::solve(board_t state){
	if (isComplete(state)) {
		//printBoard(state);
		currentstate = state;
		return true;
	}
	vector<board_t> successors = getSuccessors(state);
	for (unsigned i = 0; i < successors.size(); i++) {
		//cout << successors[i] << endl;
		if (solve(successors[i])) {
			return true;
		}
	}
  return false;
}
