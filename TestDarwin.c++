/** @file TestDarwin.c++
 *  @brief Contains unit tests for each method in Darwin.c++
 */

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// -----------
// TestCollatz
// -----------

//ostream& operator << (ostream& os, const Darwin& d){
//also tests Darwin::Darwin(int x, int y)

TEST(DarwinFixture, printDarwin1){
    Darwin d = Darwin(10, 10);
    stringstream ss;
    ss << d;

    ASSERT_EQ(ss.str(), "  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
}

// ostream& operator << (ostream& os, const Creature& c){
// also tests Creature::Creature(Species& s, direction d)

TEST(DarwinFixture, printCreature1){
    Species s = Species("b");
    Creature c = Creature(s, NORTH);
    stringstream ss;
    ss << c;

    ASSERT_EQ(ss.str(), "b");
}

//ostream& operator << (ostream& os, const Species& s){
//also tests Species::Species() and Species::Species(string s)

TEST(DarwinFixture, printSpecies1){
    Species s = Species();
    stringstream ss;
    ss << s;

    ASSERT_EQ(ss.str(), ".");
}
TEST(DarwinFixture, printSpecies2){
    Species s = Species("b");
    stringstream ss;
    ss << s;

    ASSERT_EQ(ss.str(), "b");
}

//void Darwin::addCreature(Creature &c, int x, int y)
TEST(DarwinFixture, addCreature1){
    Darwin d1 = Darwin(10, 10);
    Darwin d2 = Darwin(10, 10);
    Species s = Species();
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 4, 4);
    stringstream ss1;
    ss1 << d1;
    stringstream ss2;
    ss2 << d2;
    ASSERT_EQ(ss1.str(), ss2.str());
}
TEST(DarwinFixture, addCreature2){
    Darwin d = Darwin(10, 10);
    Species s = Species("a");
    Creature c = Creature(s, NORTH);
    d.addCreature(c, 4, 4);
    stringstream ss;
    ss << d;

    ASSERT_EQ(ss.str(), "  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ..........\n4 ....a.....\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
}
TEST(DarwinFixture, addCreature3){
    Darwin d = Darwin(10, 10);
    Species s1 = Species("a");
    Species s2 = Species("b");
    Creature c1 = Creature(s1, NORTH);
    Creature c2 = Creature(s2, NORTH);
    d.addCreature(c1, 4, 4);
    d.addCreature(c2, 4, 5);
    stringstream ss;
    ss << d;

    ASSERT_EQ(ss.str(), "  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ..........\n4 ....ab....\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
}

//void Darwin::do_turn()
//also tests void Species::addInstruction(), void Creature::do_stuff() and int Species::do_stuff(int pc, Creature*c, Darwin& d)
TEST(DarwinFixture, doTurn1){
    Darwin d1 = Darwin(10, 10);
    Species s = Species();
    s.addInstruction("hop");
    s.addInstruction("go 0");
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 4, 4);
    d1.do_turn();
    stringstream ss;
    ss << d1;
    ASSERT_EQ(ss.str(), "  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
}
TEST(DarwinFixture, doTurn2){
    Darwin d1 = Darwin(10, 10);
    Species s = Species();
    s.addInstruction("hop");
    s.addInstruction("left");
    s.addInstruction("go 0");
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 4, 4);
    d1.do_turn();
    d1.do_turn();
    d1.do_turn();
    stringstream ss;
    ss << d1;
    ASSERT_EQ(ss.str(), "  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
}

//void Creature::try_hop(Darwin * d)
//also tests Creature& Darwin::at(int x, int y)
TEST(DarwinFixture, tryHop1){
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_hop(d1);
    stringstream ss;
    ss << d1;
    ASSERT_EQ(ss.str(), "  01\n0 .b\n1 ..\n");
}

TEST(DarwinFixture, tryHop2){
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_hop(d1);
    cp->try_hop(d1);
    stringstream ss;
    ss << d1;
    ASSERT_EQ(ss.str(), "  01\n0 .b\n1 ..\n");
}

TEST(DarwinFixture, tryHop3){
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    Creature * cp2 = d1.at(0, 1);
    cp->try_hop(d1);
    cp2->try_hop(d1);
    cp->try_hop(d1);
    stringstream ss;
    ss << d1;
    ASSERT_EQ(ss.str(), "  01\n0 cb\n1 ..\n");
}

//Creature* Darwin::return_neighbor(Creature*c, direction)
TEST(DarwinFixture, tryNeighbor1){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    Creature * a = d1.return_neighbor(cp, WEST);
    Creature * n = NULL;
    ASSERT_EQ(a, n);
}
TEST(DarwinFixture, tryNeighbor2){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    Creature * a = d1.return_neighbor(cp, EAST);
    Creature * n = NULL;
    ASSERT_EQ(a, n);
}
TEST(DarwinFixture, tryNeighbor3){//test neighbor
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    Creature * cp2 = d1.at(0, 1);
    Creature * a = d1.return_neighbor(cp, NORTH);
    ASSERT_EQ(a, cp2);
}

//bool Darwin::check_empty(Creature*c, direction)
TEST(DarwinFixture, tryEmpty1){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_empty(cp, WEST);
    ASSERT_EQ(a, true);
}
TEST(DarwinFixture, tryEmpty2){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_empty(cp, EAST);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryEmpty3){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_empty(cp, NORTH);
    ASSERT_EQ(a, false);
}

//bool Darwin::check_wall(Creature*c, direction)
TEST(DarwinFixture, tryWall1){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_wall(cp, WEST);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryWall2){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_wall(cp, EAST);
    ASSERT_EQ(a, true);
}
TEST(DarwinFixture, tryWall3){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = d1.check_wall(cp, NORTH);
    ASSERT_EQ(a, false);
}

//void Creature::do_left() and void Creature::do_right()
TEST(DarwinFixture, do_direction1){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    cp->do_left();
    bool an = cp->if_empty(d1);
    ASSERT_EQ(an, true);
    cp->do_right();
    an = cp->if_enemy(d1);
    ASSERT_EQ(an, true);
}

//void Creature::try_hop(Darwin &d)
TEST(DarwinFixture, tryHop4){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_hop(d1);
    ASSERT_EQ(cp, d1.at(0, 1));
}
TEST(DarwinFixture, tryHop5){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, EAST);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_hop(d1);
    ASSERT_EQ(cp, d1.at(1, 1));
}
TEST(DarwinFixture, tryHop6){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_hop(d1);
    ASSERT_EQ(cp, d1.at(1, 1));
}

//void Creature::try_infect(Darwin &d)
TEST(DarwinFixture, tryInfect1){//test 2 different species
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_infect(d1);
    stringstream ss;
    ss << c2;
    ASSERT_EQ(ss.str(), "b");
}
TEST(DarwinFixture, tryInfect2){//test 2 same species
    Darwin d1 = Darwin(2, 2);
    Species s = Species("c");   
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    cp->try_infect(d1);
    stringstream ss;
    ss << c2;
    ASSERT_EQ(ss.str(), "c");
}
TEST(DarwinFixture, tryInfect3){//test failed infection
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(0, 1);
    cp->try_infect(d1);
    stringstream ss;
    ss << c2;
    stringstream ss1;
    ss1 << c;
    ASSERT_EQ(ss.str(), "c");
    ASSERT_EQ(ss1.str(), "b");
}

//bool Creature::if_empty(Darwin & d)
TEST(DarwinFixture, tryEmpty4){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, EAST);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_empty(d1);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryEmpty5){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_empty(d1);
    ASSERT_EQ(a, true);
}
TEST(DarwinFixture, tryEmpty6){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_empty(d1);
    ASSERT_EQ(a, false);
}

//bool Creature::if_enemy(Darwin & d)
TEST(DarwinFixture, tryEnemy4){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_enemy(d1);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryEnemy5){//test same species
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s, EAST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_enemy(d1);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryEnemy6){//test enemy
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_enemy(d1);
    ASSERT_EQ(a, true);
}

//bool Creature:: if_wall(Darwin &d)
TEST(DarwinFixture, tryWall4){//test empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, NORTH);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_wall(d1);
    ASSERT_EQ(a, false);
}
TEST(DarwinFixture, tryWall5){//test wall
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Creature c = Creature(s, EAST);
    d1.addCreature(c, 1, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_wall(d1);
    ASSERT_EQ(a, true);
}
TEST(DarwinFixture, tryWall6){//test not empty
    Darwin d1 = Darwin(2, 2);
    Species s = Species("b");   
    Species s2 = Species("c"); 
    Creature c = Creature(s, NORTH);
    Creature c2 = Creature(s2, WEST);
    d1.addCreature(c, 1, 1);
    d1.addCreature(c2, 0, 1);
    Creature * cp = d1.at(1, 1);
    bool a = cp->if_wall(d1);
    ASSERT_EQ(a, false);
}