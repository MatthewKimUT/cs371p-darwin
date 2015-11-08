/** @file Darwin.c++
 *  @brief Contains function implementations for Collatz project
 */

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include "Darwin.h"
#include <iterator>
#include <vector>
#include <cstdlib>
#include <map>
#include <iterator>

using namespace std;

//------
//Darwin
//------

//Darwin board constructor, takes int 2 ints for height and width parameters
Darwin::Darwin(int x, int y){
	_x = x;
	_y = y;
	grid = vector<vector<Creature*>>(x, vector<Creature*>(y));
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			grid[i][j] = NULL;
		}
	}
}

//Adds creature by reference to the specified board position
void Darwin::addCreature(Creature& c, int x, int y){
	Creature *cp = &c;
	grid[x][y] = cp;
	creatures[cp] = false;
}

//Iterates through grid and performs creature's actions, if they have any
//map is needed so creatures that hop the same direction as the iteration counter 
//do not perform their action multiple times
void Darwin::do_turn(){
	for(int i = 0; i < _x; i++){
		for(int j = 0; j < _y; j++){
			if(grid[i][j] != NULL){
				Creature* cp = grid[i][j];
				if(creatures[cp] == false){
					cp->do_stuff(*this);
					creatures[cp] = true;
				}
			}
		}
	}
	map<Creature*, bool>::iterator it;
	for(it = creatures.begin(); it != creatures.end(); it++){
		it->second = false;
	}
}

//Given a creature and a direction, tries to hop in the given direction
//if there is a wall or another creature, does nothing
void Darwin::try_hop(Creature * c, direction d){
	bool done = false;
	for(int i = 0; i < _x; i++){
		for(int j = 0; j < _y; j++){
			if(grid[i][j] == c){
				if(d == NORTH){
					if(i != 0){
						if(grid[i - 1][j] == NULL){
							grid[i - 1][j] = grid[i][j];
							grid[i][j] = NULL;
							done = true;
						}
					}
				}
				else if(d == EAST){
					if(j != _y - 1){
						if(grid[i][j + 1] == NULL){
							grid[i][j + 1] = grid[i][j];
							grid[i][j] = NULL;
							done = true;
						}
					}
				}
				else if (d == SOUTH){
					if(i != _x - 1){
						if(grid[i + 1][j] == NULL){
							grid[i + 1][j] = grid[i][j];
							grid[i][j] = NULL;
							done = true;
						}
					}
				}
				else{
					if(j != 0){
						if(grid[i][j - 1] == NULL){
							grid[i][j - 1] = grid[i][j];
							grid[i][j] = NULL;
							done = true;
						}
					}
				}
			}
			//breaks so that the same creature is not moved multiple times
			if(done)
				break;
		}
		if(done)
			break;
	}
}

//Returns the gridspace next to a creature in a given direction
Creature* Darwin::return_neighbor(Creature* c, direction d){
	for(int i = 0; i < _x; i++){
		for(int j = 0; j < _y; j++){
			if(grid[i][j] == c){
				if(d == NORTH){
					if(i != 0)
						return grid[i - 1][j];
				}
				else if(d == EAST){
					if(j != _y - 1)
						return grid[i][j + 1];
				}
				else if (d == SOUTH){
					if(i != _x - 1)
						return grid[i + 1][j];
				}
				else{
					if(j != 0)
						return grid[i][j - 1];
				}
			}
		}
	}
	return NULL;
}

//checks if the gridspace a creature is facing is empty
//only returns true if there is no wall and no creature present
bool Darwin::check_empty(Creature*c, direction d){
	for(int i = 0; i < _x; i++){
		for(int j = 0; j < _y; j++){
			if(grid[i][j] == c){
				if(d == NORTH){
					if(i != 0)
						return grid[i - 1][j] == NULL;
				}
				else if(d == EAST){
					if(j != _y - 1)
						return grid[i][j - 1] == NULL;
				}
				else if (d == SOUTH){
					if(i != _x - 1)
						return grid[i + 1][j] == NULL;
				}
				else{
					if(j != 0)
						return grid[i][j - 1] == NULL;
				}
			}
		}
	}
	return false;
}

//checks if the gridspace a creature is facing is a wall
//returns true if the creature is on the border and facing the correct direction
bool Darwin::check_wall(Creature*c, direction d){
	for(int i = 0; i < _x; i++){
		for(int j = 0; j < _y; j++){
			if(grid[i][j] == c){
				if(d == NORTH){
					if(i == 0)
						return true;
				}
				else if(d == EAST){
					if(j == _y - 1)
						return true;
				}
				else if (d == SOUTH){
					if(i == _x - 1)
						return true;
				}
				else{
					if(j == 0)
						return true;
				}
			}
		}
	}
	return false;
}
//--------
//Creature 
//--------

//constructs a creature object using a species object (by reference) and a direction
Creature::Creature(Species& spec, direction direct){
	s = spec;
	dir = direct;
	pc = 0;
}

//pushes relevant information to species to perform its action during a darwin do_turn() call
void Creature::do_stuff(Darwin& d){
	pc = s.do_stuff(pc, *this, d);
}

//rotates the creature to the left
void Creature::do_left(){
	if(dir == NORTH){
		dir = WEST;
	}
	else if(dir == SOUTH){
		dir = EAST;
	}
	else if(dir == WEST){
		dir = SOUTH;
	}
	else{
		dir = NORTH;
	}
}

//rotates the creature to the right
void Creature::do_right(){
	if(dir == NORTH){
		dir = EAST;
	}
	else if(dir == SOUTH){
		dir = WEST;
	}
	else if(dir == WEST){
		dir = NORTH;
	}
	else{
		dir = SOUTH;
	}
}

//signal to the creature that it should attempt a hop
//pushes relevant information to darwin object, which will vet the request
void Creature::try_hop(Darwin& d){
	d.try_hop(this, dir);
}

//signal to the creature that it should attempt an infection
//pushes relevant information to darwin object, which returns the gridspace the creature is facing
//if the gridspace contains another creature, infects it
void Creature::try_infect(Darwin& d){
	Creature* inf = d.return_neighbor(this, dir);
	if(inf != NULL){
		if (!(inf->s == s))
			inf->s = s;
	}
}

//signal to creature that it should ask if the space in front contains anything
//pushes relevant information to darwin object, returns true if the space in front is empty
bool Creature::if_empty(Darwin& d){
	return d.check_empty(this, dir);
}

//signal to creature that it should ask if the space in front contains an enemy
//pushes relevant information to darwin object, which returns the gridspace the creature is facing
//if the gridspace contains another creature, returns true
bool Creature::if_enemy(Darwin& d){
	Creature* c = d.return_neighbor(this, dir);
	if(c != NULL){
		if (!(c->s == s))
			return true;
	}
	return false;
}

//signal to creature that it should ask if the space in front is a wall
//pushes relevant information to darwin object, returns true if the space in front is a wall
bool Creature::if_wall(Darwin& d){
	return d.check_wall(this, dir);
}

//-------
//Species
//-------

//Default constructor for a species, makes the gridspace name the same as an empty space
Species::Species(){
	name_char = ".";
}
//Constructs a species with gridspace name equal to the given parameter
Species::Species(string s){
	name_char = s;
}
//adds the instruction to the specie's program
void Species::addInstruction(string s){
	program.push_back(s);
}
//processes execution request from Creature during a Darwin::do_turn() call
//returns the program counter that Creature should set to after execution of one turn
int Species::do_stuff(int pc, Creature& c, Darwin& d){
	string instr = program[pc];

	//action instructions consume the entire turn
	if(instr.find("hop") != string::npos){
		c.try_hop(d);
		return pc + 1;
	}
	if(instr.find("left") != string::npos){
		c.do_left();
		return pc + 1;
	}
	if(instr.find("right") != string::npos){
		c.do_right();
		return pc + 1;
	}
	if(instr.find("infect") != string::npos){
		c.try_infect(d);
		return pc + 1;
	}

	//control instructions do not count as a turn and continue until an action instruction is called
	if(instr.find("if_empty") != string::npos){
		bool val = c.if_empty(d);
		string tmp;
	    int num;
	    stringstream ss(instr);
	    ss >> tmp >> num;
		if(val)
			return do_stuff(num, c, d);
		else
			return do_stuff(pc + 1, c, d);
	}
	if(instr.find("if_wall") != string::npos){
		bool val = c.if_wall(d);
		string tmp;
	    int num;
	    stringstream ss(instr);
	    ss >> tmp >> num;
		if(val)
			return do_stuff(num, c, d);
		else
			return do_stuff(pc + 1, c, d);
	}
	if(instr.find("if_random") != string::npos){
		int r = rand();
		string tmp;
	    int num;
	    stringstream ss(instr);
	    ss >> tmp >> num;
		if(r % 2 != 0)
			return do_stuff(num, c, d);
		else
			return do_stuff(pc + 1, c, d);
	}
	if(instr.find("if_enemy") != string::npos){
		bool val = c.if_enemy(d);
		string tmp;
	    int num;
	    stringstream ss(instr);
	    ss >> tmp >> num;
		if(val)
			return do_stuff(num, c, d);
		else
			return do_stuff(pc + 1, c, d);
	}
	if(instr.find("go") != string::npos){
		string tmp;
	    int num;
	    stringstream ss(instr);
	    ss >> tmp >> num;
		return do_stuff(num, c, d);
	}
	return pc + 1;
}

//--------
//Printing
//--------

ostream& operator << (ostream& os, const Darwin& d){
	os << "  ";
	for(int i = 0; i < d._y; i++){
		os << to_string(i % 10);
	}
	os << "\n";
	for(int i = 0; i < d._x; i++){
		os << (to_string(i % 10) + " ");
		for(int j = 0; j < d._y; j++){
		    if(d.grid[i][j] == NULL){
		    	os << ".";
		    }
		    else{
		    	os << *(d.at(i, j));
		    }
		}
		os << "\n";
	}
	return os;
}

ostream& operator << (ostream& os, const Creature& c){
	return os << c.s;
}

ostream& operator << (ostream& os, const Species& s){
	return os << s.name_char;
}