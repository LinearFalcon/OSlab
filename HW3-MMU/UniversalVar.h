//
//  UniversalVar.h
//  MMU
//
//  Created by Liang Fang on 4/5/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_UniversalVar_h
#define MMU_UniversalVar_h

#include <iostream>
using namespace std;

#include "Stats.h"
#include "pte.h"
#include "frame.h"
#include <stdio.h>
#include <string.h>


// enum type for different paging algorithm
enum Type {type_NRU, type_LRU, type_Random, type_FIFO, type_SecondChance, type_PhysicalClock, type_VirtualClock, type_PhysicalAging, type_VirtualAging};

char* inputPath;   // path of input file
char* randPath;     // path of random number file

string str;     // temporary variable
int numOfRandom;  // store number of random in random file
int* randvals;  // store random num read from rfile

int num_frames = 32;    // number of frames, specified by option parameter, default value is 32
int algoType = type_LRU;  // paging algorithm type, specified by option parameter, default type is LRU
Stats stats;

// option parameters, initialize to false
bool option_O = false;
bool option_F = false;
bool option_P = false;
bool option_S = false;
bool option_p = false;
bool option_f = false;

pte page_table[64]; // gloabal virtual page table
frame* frame_table; // global physical frame table, implemented by frame pointer    ???????


int operationVal;  // read = 0 or write = 1
int whichPage;  // which page to operate specified in instruction

#endif
