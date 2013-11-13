/*
 * SudokuTest.h
 * Name: Harry Kran-Annexstein
 *
 * Unit tests for Sudoku class.
 *
 * Oct 23, 2013
 */

#ifndef SUDOKU_TEST_H
#define SUDOKU_TEST_H

#include <Sudoku.h>

#include <iostream>
#include <cxxtest/TestSuite.h>

using namespace std;

class SudokuTest : public CxxTest::TestSuite {
public:
	void testConstructor() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    TS_ASSERT_EQUALS(s,g.getStartBoard());
    TS_ASSERT_EQUALS(s,g.getCurrentBoard());
	}

	void testGetStartBoard() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    g.solve();
    TS_ASSERT_DIFFERS(g.getStartBoard(),g.getCurrentBoard());
	}

	void testResetTest() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
		vector<int> test(9);
		g.reset(test);
		TS_ASSERT_EQUALS(test.size(),9);
	}

	void testCheckTestTRUE() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
		vector<int> test (4,1);
		TS_ASSERT(g.checkTest(test));
	}

	void testCheckTestFALSE() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
		vector<int> test (4,2);
		TS_ASSERT(!g.checkTest(test));
	}

	void testGetRegion() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
		vector<int> test = g.getRegion(0,0,s);
		TS_ASSERT_EQUALS(test.size(),9);
	}

  void testisCompleteTRUE(){
    board_t s = "123456789456789123789123456234567891567891234891234567345678912678912345912345678";
  	Sudoku g(s);
    TS_ASSERT(g.isComplete(s));
  }
  
  void testiCompleteFALSE() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    TS_ASSERT(!g.isComplete());
  }

  void testisValidTRUE() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    TS_ASSERT(g.isValid());
  }

  void testisValidFALSE() {
    board_t s = "75994....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    TS_ASSERT(!g.isValid());
  }

  void testGetSuccessors() {
    board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
    Sudoku g(s);
    vector<board_t> rets = g.getSuccessors(s);
    TS_ASSERT_LESS_THAN(0,rets.size());
  }

  void testSolve(){
            // This is BLACK-BOX-TESTING since we only use public methods.
    board_t s = ".........456789123789123456234567891567891234891234567345678912678912345912345678";
    Sudoku g(s);
    TS_ASSERT(g.solve());
    s = g.getCurrentBoard();
    string sol = "123456789456789123789123456234567891567891234891234567345678912678912345912345678";
    TS_ASSERT(s.compare(sol) == 0);
  }

  void testSolve2() {
  	board_t s = "759.4....68.5...4..3.2.95..56.1..9....3...1....1..6.37..53.7.9..7...8.53....6.721";
  	Sudoku g(s);
  	TS_ASSERT(g.solve());
  }

  void testSolve4Sol() {
  	board_t s = "1.657..9.84..2.1...5.9.4...6.....2.3.82.9.74.4.7.....1...4.2.....5.8.....7..59...";
  	Sudoku g(s);
  	TS_ASSERT(g.solve());
  }

  void testSolve0Sol() {
  	board_t s = "1.657..9.84..2.1...5.9.4...6.....2.3.82.9.74.4.7.....1...4.2.1...5.8..39.7..598.4";
  	Sudoku g(s);
  	TS_ASSERT(!g.solve());
  }

};
  
#endif
