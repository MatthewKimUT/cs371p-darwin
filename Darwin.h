/** @file Darwin.h
 *	@brief Contains function definitions
 */

#ifndef Darwin_h
#define Darwin_h

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <iterator>
#include <vector>
#include <cstdlib>
#include <map>
#include <iterator>

using namespace std;

class Darwin;
class Species;
class Creature;
enum direction{NORTH, SOUTH, EAST, WEST};


class Species{
	private:
		vector<string> program;
		string name_char;
	public:
		Species();
		Species(string s);
		void addInstruction(string s);
		int do_stuff(int pc, Creature& c, Darwin& d);

		bool operator == (const Species& s) const {
		    return name_char == s.name_char;
		}
		friend ostream& operator<<(ostream& os, const Species& s);
};

class Creature{
	private:
		Species s;
		direction dir;
		int pc;
	public:
		Creature(Species& spec, direction direct);
		void do_stuff(Darwin& d);
		void do_left();
		void do_right();
		void try_hop(Darwin& d);
		void try_infect(Darwin& d);
		bool if_empty(Darwin& d);
		bool if_enemy(Darwin& d);
		bool if_wall(Darwin& d);
		friend ostream& operator<<(ostream& os, const Creature& c);
};

class Darwin{
	private:
		vector<vector<Creature*> > grid;
		map<Creature*, bool> creatures;
		int _x;
		int _y;
	public:
		class iterator : public std::iterator<forward_iterator_tag, Creature*> {
			private:
				int pos_x;
				int pos_y;
				Darwin * d;

			public:
				 iterator(Darwin * dar, int x, int y){
	                pos_x = x;
	                pos_y = y;
	                d = dar;
	            }

				bool operator == (const iterator& rhs) const {
                    return ((pos_x == rhs.pos_x) && (pos_y == rhs.pos_y));
                }
                bool operator != (const iterator& rhs) const {
                    return ((pos_x != rhs.pos_x) || (pos_y != rhs.pos_y));
                }
                Creature* operator * (){
                    return (*d).at(pos_x, pos_y);
                }
                iterator& operator ++ () {
                	iterator end = (*d).end();
                	int max_x = end.pos_x;
                	int max_y = end.pos_y;
                    if (pos_x < max_x){
                    	pos_x++;
                    	return *this;
                    }
                    else{
                    	if(pos_y < max_y){
	                    	pos_x = 0;
	                    	pos_y++;
	                    }
	                    else
                    		return *this;
                    }
                }
		};
		iterator begin(){
			return iterator(this, 0, 0);
		}
		iterator end(){
			return iterator(this, _x, _y);
		}
		Creature* at(int x, int y){
			return grid[x][y];
		}
		const Creature* at(int x, int y) const{
			return grid[x][y];
		}
		Darwin(int x, int y);
		void addCreature(Creature& c, int x, int y);
		void do_turn();
		void try_hop(Creature* c, direction d);
		Creature* return_neighbor(Creature* c, direction d);
		bool check_empty(Creature*c, direction d);
		bool check_wall(Creature*c, direction d);
		friend ostream& operator<<(ostream& os, const Darwin& d);
};


// // ------------
// // Darwin_answer
// // ------------

// /**
//  * read string vector
//  * @param input a string vector
//  * @return a string answer, one that answers who wins the ballot
//  */
// string Darwin_answer(std::vector<string> &input);

// // -----
// // split
// // -----

// *
//  * @param s string to split into array
//  * @param delim char: the delimiter
//  * @return vector of strings from s split by the delimiter
 
// std::vector<std::string> split(const std::string &s, char delim);

// std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

// // -------------
// // Darwin_solve
// // -------------

// /**
//  * @param r an istream
//  * @param w an ostream
//  */
// void Darwin_solve(istream& r, ostream& w);

#endif // Darwin_h
