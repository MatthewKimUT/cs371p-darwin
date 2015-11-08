

// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
// ----
// main
// ----
int main () {
    using namespace std;
    // ----
    // food
    // ----

    Species food = Species("f");
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    Species hopper = Species("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    // -----
    // rover
    // -----

    Species rover = Species("r");
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

    // ----
    // trap
    // ----

    Species trap = Species("t");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    // ----
    // best
    // ----

    Species best = Species("b");
    best.addInstruction("if_enemy 21");
    best.addInstruction("if_empty 19");
    best.addInstruction("if_wall 8");
    best.addInstruction("if_random 6");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("right");
    best.addInstruction("go 0");
    best.addInstruction("left");
    best.addInstruction("if_enemy 21");
    best.addInstruction("left");
    best.addInstruction("if_enemy 21");
    best.addInstruction("left");
    best.addInstruction("if_enemy 21");
    best.addInstruction("right");
    best.addInstruction("if_enemy 21");
    best.addInstruction("right");
    best.addInstruction("if_enemy 21");
    best.addInstruction("go 10");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 0");


    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin d1 = Darwin(8, 8);
    Creature c0 = Creature(food, EAST);
    d1.addCreature(c0, 0, 0);
    Creature c1 = Creature(hopper, NORTH);
    d1.addCreature(c1, 3, 3);
    Creature c2 = Creature(hopper, EAST);
    d1.addCreature(c2, 3, 4);
    Creature c3 = Creature(hopper, SOUTH);
    d1.addCreature(c3, 4, 4);
    Creature c4 = Creature(hopper, WEST);
    d1.addCreature(c4, 4, 3);
    Creature c5 = Creature(food, NORTH);
    d1.addCreature(c5, 7, 7);

    cout << "Turn = 0." << endl;
    cout << d1 << endl;
    for(int i = 1; i < 6; i++){
        d1.do_turn();
        cout << "Turn = " << i << "." << endl;
        cout << d1 << endl;
    }
    

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin d2 = Darwin(7, 9);
    Creature c6 = Creature(trap, SOUTH);
    d2.addCreature(c6, 0, 0);
    Creature c7 = Creature(hopper, EAST);
    d2.addCreature(c7, 3, 2);
    Creature c8 = Creature(rover, NORTH);
    d2.addCreature(c8, 5, 4);
    Creature c9 = Creature(trap, WEST);
    d2.addCreature(c9, 6, 8);
    cout << "Turn = 0." << endl;
    cout << d2 << endl;
    for(int i = 1; i < 6; i++){
        d2.do_turn();
        cout << "Turn = " << i << "." << endl;
        cout << d2 << endl;
    }
    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    vector<Creature> foods;
    Darwin d3 = Darwin(72, 72);
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(food, d);
        foods.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d3.addCreature(foods[i], x1, y1);
    }

    vector<Creature> hoppers;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(hopper, d);
        hoppers.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d3.addCreature(hoppers[i], x1, y1);
    }

    vector<Creature> rovers;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(rover, d);
        rovers.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d3.addCreature(rovers[i], x1, y1);
    }

    vector<Creature> traps;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(trap, d);
        traps.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d3.addCreature(traps[i], x1, y1);
    }

    cout << "Turn = 0." << endl;
    cout << d3 << endl;
    
    for(int i = 1; i < 1001; i++){
        d3.do_turn();
        if(i <= 10 || (i % 100) == 0){
            cout << "Turn = " << i << "." << endl;
            cout << d3 << endl;
        }
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    vector<Creature> foods1;
    Darwin d4 = Darwin(72, 72);
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(food, d);
        foods1.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d4.addCreature(foods1[i], x1, y1);
    }

    vector<Creature> hoppers1;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(hopper, d);
        hoppers1.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d4.addCreature(hoppers1[i], x1, y1);
    }

    vector<Creature> rovers1;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(rover, d);
        rovers1.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d4.addCreature(rovers1[i], x1, y1);
    }

    vector<Creature> traps1;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(trap, d);
        traps1.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d4.addCreature(traps1[i], x1, y1);
    }

    vector<Creature> best1;
    for(int i = 0; i < 10; i++){
        int dir1 = rand() % 4;
        direction d;
        switch(dir1){
            case 0 :
                d = NORTH;
                break;
            case 1 :
                d = EAST;
                break;
            case 2 :
                d = SOUTH;
                break;
            case 3 :
                d = WEST;
                break;
        }
        Creature tmp = Creature(best, d);
        best1.push_back(tmp);
    }
    for(int i = 0; i < 10; i++){
        int num1 = rand() % 5184;
        int x1 = num1 / 72;
        int y1 = num1 % 72;
        while(d3.at(x1, y1) != NULL){
            num1 = rand() % 5184;
            x1 = num1 / 72;
            y1 = num1 % 72;
        }
        d4.addCreature(best1[i], x1, y1);
    }
    cout << "Turn = 0." << endl;
    cout << d4 << endl;
    for(int i = 1; i < 1001; i++){
        d4.do_turn();
        if(i <= 10 || (i % 100) == 0){
            cout << "Turn = " << i << "." << endl;
            cout << d4 << endl;
        }
    }
    return 0;}

    // Status API Training Shop Blog About Pricing 

    // © 2015 GitHub, Inc. Terms Privacy Security Contact Help 

