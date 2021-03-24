
#include "doctest.h"
#include "Board.hpp"
#include <string>
#include <sstream>

using namespace std;
using ariel::Direction;

// 1
TEST_CASE("Write horizontal out of current range") 
{
	ariel::Board board;
	board.post(1000, 2000, Direction::Horizontal, "abcd");
	CHECK(board.read(1000, 2000, Direction::Horizontal, 4) == "abcd"); 
}

// 2
TEST_CASE("Read horizontal out of current range")
{
	ariel::Board board;
    CHECK(board.read(1000, 2000, Direction::Horizontal, 5) == "_____"); 
}

// 3
TEST_CASE("Write vertical out of current range") 
{
	ariel::Board board;
	board.post(1000, 2000, Direction::Vertical, "abcd");
	CHECK(board.read(1000, 2000, Direction::Vertical, 4) == "abcd"); 
}

// 4
TEST_CASE("Read vertical out of current range")
{
	ariel::Board board;
    CHECK(board.read(1000, 2000, Direction::Vertical, 5) == "_____"); 
}

// 5
TEST_CASE("Read nothing horizontaly")
{
	ariel::Board board;
    CHECK(board.read(10, 2000, Direction::Vertical, 0) == ""); 
}

// 6
TEST_CASE("Read nothing verticaly")
{
	ariel::Board board;
    CHECK(board.read(0, 340, Direction::Vertical, 0) == ""); 
}

// 7
TEST_CASE("Show with empty board")
{
	ariel::Board board;

    // restore cout output from https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    board.show(); // call show

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == ""); 
}

// 8
TEST_CASE("Show with horizontal written message")
{
	ariel::Board board;
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

	board.post(100, 200, Direction::Horizontal, "abcd");
    board.show(); // call show

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == "00100: abcd\n"); 
}

// 9
TEST_CASE("Show with verticaly written message")
{
	ariel::Board board;
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

	board.post(100, 200, Direction::Vertical, "abcd");
    board.show(); // call show

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == "00100: a\n00101: b\n00102: c\n00103: d\n");  
}

// 10
TEST_CASE("Test demo show")
{
    ariel::Board board;

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

	board.post(100, 200, Direction::Horizontal, "abcd");
	board.post(99, 202, Direction::Vertical, "xyz");
	board.show();

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == "00099: __x_\n00100: abyd\n00101: __z_\n");  
    
}

// 11
TEST_CASE("Test demo post and read")
{
    ariel::Board board;
	board.post(100, 200, Direction::Horizontal, "abcd");
    CHECK(board.read(99, 201, Direction::Vertical, 3) == "_b_"); 
	board.post(99, 202, Direction::Vertical, "xyz");
    CHECK(board.read(100, 200, Direction::Horizontal, 6) == "abyd__"); 
}

// 12
TEST_CASE("Read run over text horizontaly")
{
	ariel::Board board;
    board.post(102, 198, Direction::Horizontal, "Horizontal");
    CHECK(board.read(102, 198, Direction::Horizontal, 10) == "Horizontal"); 
    board.post(100, 201, Direction::Vertical, "Vertical");
    CHECK(board.read(102, 198, Direction::Horizontal, 10) == "Horrzontal"); 
	board.post(101, 202, Direction::Vertical, "Vertical");
    CHECK(board.read(102, 198, Direction::Horizontal, 10) == "Horreontal"); 
}

// 13
TEST_CASE("Read run over text verticaly")
{
	ariel::Board board;
    board.post(98, 202, Direction::Vertical, "Vertical");
    CHECK(board.read(98, 202, Direction::Vertical, 8) == "Vertical"); 
    board.post(100, 201, Direction::Horizontal, "Horizontal");
    CHECK(board.read(98, 202, Direction::Vertical, 8) == "Veotical"); 
	board.post(101, 202, Direction::Horizontal, "Horizontal");
    CHECK(board.read(98, 202, Direction::Vertical, 8) == "VeoHical"); 
}

// 14
TEST_CASE("Write nothing horizontaly")
{
	ariel::Board board;
    board.post(0, 0, Direction::Horizontal, "");
    CHECK(board.read(0, 0, Direction::Horizontal, 3) == "___"); 
}

// 15
TEST_CASE("Write nothing verticaly")
{
	ariel::Board board;
    board.post(0, 0, Direction::Vertical, "");
    CHECK(board.read(0, 0, Direction::Vertical, 3) == "___"); 
}

// 16
TEST_CASE("Show after runing over text horizontaly")
{
	ariel::Board board;
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    board.post(102, 198, Direction::Horizontal, "Horizontal");
    board.post(100, 201, Direction::Vertical, "Vertical");
	board.post(101, 202, Direction::Vertical, "Vertical");
	board.show();

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == "00100: ___V______\n00101: ___eV_____\n00102: Horreontal\n00103: ___tr_____\n00104: ___it_____\n00105: ___ci_____\n00106: ___ac_____\n00107: ___la_____\n00108: ____l_____\n");  
}

// 17
TEST_CASE("Show after runing over text verticaly")
{
	ariel::Board board;
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    board.post(98, 202, Direction::Vertical, "Vertical");
    board.post(100, 201, Direction::Horizontal, "Horizontal");
	board.post(101, 202, Direction::Horizontal, "Horizontal");
    board.show();

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
    CHECK(oss.str() == "00098: _V_________\n00099: _e_________\n00100: Horizontal_\n00101: _Horizontal\n00102: _i_________\n00103: _c_________\n00104: _a_________\n00105: _l_________\n");  
    
}

// 18
TEST_CASE("Write string verticaly with '\n'")
{
	ariel::Board board;
    board.post(98, 202, Direction::Vertical, "some\nssdf");
    CHECK(board.read(98, 202, Direction::Vertical, 10) == "some_ssdf_"); 
}

// 19
TEST_CASE("Write string horizontaly with '\n'")
{
	ariel::Board board;
    board.post(98, 202, Direction::Horizontal, "some\nssdf");
    CHECK(board.read(98, 202, Direction::Horizontal, 10) == "some_ssdf_"); 
}

// 20
TEST_CASE("Write nothing and show")
{
	ariel::Board board;
    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());    
    CHECK(board.read(99, 201, Direction::Vertical, 3) == "___"); 
    board.show();

    cout.rdbuf(p_cout_streambuf); // restore cout output
    CHECK(oss);
     CHECK(oss.str() == ""); 
}