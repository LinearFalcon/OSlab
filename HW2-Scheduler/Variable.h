//
//  Variable.h
//  Scheduler
//
//  Created by Liang Fang on 3/8/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef Scheduler_Variable_h
#define Scheduler_Variable_h

#include <iostream>
#include <queue>
#include "Process.h"
using namespace std;

enum Type {FCFS, LCFS, SJF, RR};    // enum type representing different scheduler algorithm

int TIME = 0;   // time count

char* inputPath;   // path of input file
char* randPath;     // path of random number file
string str;     // temporary variable

int schedulerType;  // store schedular algorithm type for this process
int quantum = 0;    // store quantum for RoundRobin, initialize as 0
int* randvals;  // store random num read from rfile
int numOfRandom;  // store number of random in random file

queue<Process> allProcess;

#endif
