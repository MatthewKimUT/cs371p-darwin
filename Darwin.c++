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

using namespace std;

enum direction{UP, DOWN, LEFT, RIGHT};
enum command{HOP, INFECT, WALL, EMPTY, ENEMY};


class Darwin{
	private:
		vector<vector<Creature*>> grid;
		vector<Creature*> creatures;
	public:
		Darwin(){
			grid = new vector(10, vector<Creature>(10));
			for(size_t i = 0; i < 10; i++){
				for(size_t j = 0; j < 10; j++){
					grid[i][j] = NULL;
				}
			}
		}
		Darwin(int x, int y){
			grid = new vector(x, vector<Creature>(y));
			for(size_t i = 0; i < x; i++){
				for(size_t j = 0; j < y; j++){
					grid[i][j] = NULL;
				}
			}
		}
		iterator begin(){
			return creatures.begin();
		}
		iterator end(){
			return creatures.end();
		}
		void addCreature(Creature *c, int x, int y){
			grid[x][y] = c;
			creatures.push_back(c);
		}
		Creature& at(int x, int y){
			return *grid[x][y];
		}
		void take_turn(){
			for(int i = 0; i < creatures.size(); i++){
				*creatures[i].do_stuff(*this);
			}
		}
		//in counterclockwise order: up, left, down, right
		vector<Creature*> return_adjacent(Creature* c){
			vector<Creature*> return_values;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid[0].size(); j++){
					if(grid[i][j] == c){
						if(j != 0)
							return_values.push_back(grid[i][j - 1]);
						else
							return_values.push_back(wall);

						if(i != 0)
							return_values.push_back(grid[i - 1][j ]);
						else
							return_values.push_back(wall);

						if(j != grid[0].size() - 1)
							return_values.push_back(grid[i][j + 1]);
						else
							return_values.push_back(wall);

						if(j != grid.size() - 1)
							return_values.push_back(grid[i + 1][j]);
						else
							return_values.push_back(wall);
						break;
					}
				}
			}
			return return_values;
		}

		void hop(Creature *c, int com){
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid[0].size(); j++){
					if(grid[i][j] == c){
						if(com == 0){
							grid[i][j - 1] = grid[i][j];
							grid[i][j] = NULL;
						}
						else if(com == 1){
							grid[i - 1][j] = grid[i][j];
							grid[i][j] = NULL;
						}
						else if(com == 2){
							grid[i][j + 1] = grid[i][j];
							grid[i][j] = NULL;
						}
						else{
							grid[i + 1][j] = grid[i][j];
							grid[i][j] = NULL;
						}
					}
				}
			}
		}
};

class Creature{
	private:
		Species species;
		direction dir;
		int pc;
	public:
		Creature(){
			species = new Species();
			dir = UP;
			pc = -1;
		}
		Creature(const Species &s, direction d, int n = 0){
			species = s;
			dir = d;
			pc = n;
		}
		void do_stuff(Darwin* d){
			int num = species.do_stuff(*this, d, pc);
			if(num == -1)
				pc++;
			else
				pc = num;
		}
		void try_hop(Darwin* d){
			vector<Creature*> vals = *d.return_values;
			if(dir == UP){
				if(vals[0] == NULL)
					d->hop(*this, 0);
			}
			else if(dir == LEFT){
				if(vals[1] == NULL)
					d->hop(*this, 1);
			}
			else if(dir == DOWN){
				if(vals[2] == NULL)
					d->hop(*this, 2);
			}
			else{
				if(vals[3] == NULL)
					d->hop(*this, 3);
			}
		}
		void try_infect(Darwin* d){
			vector<Creature*> vals = *d.return_values;
			if(dir == UP){
				if(vals[0] != NULL){
					Creature inf = *vals[0];
					if(inf.species != this.species){
						inf.species = this.species;
						inf.pc = 0;
					}
				}
			}
			else if(dir == LEFT){
				if(vals[1] != NULL){
					Creature inf = *vals[1];
					if(inf.species != this.species){
						inf.species = this.species;
						inf.pc = 0;
					}
				}
			}
			else if(dir == DOWN){
				if(vals[2] != NULL){
					Creature inf = *vals[2];
					if(inf.species != this.species){
						inf.species = this.species;
						inf.pc = 0;
					}
				}
			}
			else{
				if(vals[3] != NULL){
					Creature inf = *vals[3];
					if(inf.species != this.species){
						inf.species = this.species;
						inf.pc = 0;
					}
				}
			}
		}
		void do_left(){
			if(dir == UP){
				dir = LEFT;
			}
			else if(dir == DOWN){
				dir = RIGHT;
			}
			else if(dir == LEFT){
				dir = DOWN;
			}
			else{
				dir = UP;
			}
		}
		void do_right(){
			if(dir == UP){
				dir = RIGHT;
			}
			else if(dir == DOWN){
				dir = LEFT;
			}
			else if(dir == LEFT){
				dir = UP;
			}
			else{
				dir = DOWN;
			}
		}
		bool if_empty(Darwin *d){
			vector<Creature*> vals = *d.return_values(*this);
			if(dir == UP)
				return vals.at(0) == NULL;
			else if(dir == LEFT)
				return vals.at(1) == NULL;
			else if(dir == DOWN)
				return vals.at(2) == NULL;
			else
				return vals.at(3) == NULL;
		}
		bool if_wall(Darwin *d){
			vector<Creature*> vals = *d.return_values(*this);
			if(dir == UP)
				return vals.at(0) == wall;
			else if(dir == LEFT)
				return vals.at(1) == wall;
			else if(dir == DOWN)
				return vals.at(2) == wall;
			else
				return vals.at(3) == wall;
		}
		bool if_enemy(Darwin *d){
			vector<Creature*> vals = *d.return_values(*this);
			if(dir == UP)
				return (vals.at(0) != wall && vals.at(0) != NULL && *vals.at(0).species != species);
			else if(dir == LEFT)
				return (vals.at(1) != wall && vals.at(1) != NULL && *vals.at(1).species != species);
			else if(dir == DOWN)
				return (vals.at(2) != wall && vals.at(2) != NULL && *vals.at(2).species != species);
			else
				return (vals.at(3) != wall && vals.at(3) != NULL && *vals.at(3).species != species);
		}
};

class Species{
	private:
		vector<string> program;
		string name_char;
	public:
		Species(string s){
			name_char = s;
			program = new vector<string>(0);
		}
		void addInstruction(string instr){
			program.push_back(instr);
		}
		int do_stuff(Creature* c, Darwin* d, int pc){
			string instr = program[pc];
			if(instr.find("hop") != string::npos){
				c->try_hop(d);
				return -1;
			}
			if(instr.find("left") != string::npos){
				c->do_left();
				return -1;
			}
			if(instr.find("right") != string::npos){
				c->do_right();
				return -1;
			}
			if(instr.find("infect") != string::npos){
				c->try_infect(d);
				return -1;
			}
			if(instr.find("if_empty") != string::npos){
				bool val = c->if_empty(d);
				int num = atoi(instr.c_str());
				if(val)
					return num;
				else
					return -1;
			}
			if(instr.find("if_wall") != string::npos){
				bool val = c->if_wall(d);
				int num = atoi(instr.c_str());
				if(val)
					return num;
				else
					return -1;
			}
			if(instr.find("if_random") != string::npos){
				int r = rand();
				int num = atoi(instr.c_str());
				if(r % 2 != 0)
					return num;
				else
					return -1;
			}
			if(instr.find("if_enemy") != string::npos){
				bool val = c->if_enemy(d);
				int num = atoi(instr.c_str());
				if(val)
					return num;
				else
					return -1;
			}
			if(instr.find("go") != string::npos){
				int num = atoi(instr.c_str());
				return num;
			}
		}
};