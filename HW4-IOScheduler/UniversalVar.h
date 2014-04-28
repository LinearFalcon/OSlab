//
//  UniversalVar.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_UniversalVar_h
#define IOSched_UniversalVar_h

#include <iostream>
using namespace std;
#include "IORequest.h"
#include <deque>
#include <queue>
#include <vector>


enum Type {type_FIFO, type_SSTF, type_SCAN, type_CSCAN, TYPE_FSCAN};

int scheduleType;

int numOfRequest = 0;   // number of IO requests, initialize 0


string str;     // temporary variable

deque<IORequest> IO_queue;  // IO request queue

//int TIME = 0;   // time count

#endif
