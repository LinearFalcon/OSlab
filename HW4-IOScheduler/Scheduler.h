//
//  Scheduler.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_Scheduler_h
#define IOSched_Scheduler_h
#include "Time.h"
#include "UniversalVar.h"
#include <cmath>


class Scheduler {
protected:
    Time timeInfo;
    int headPos;        // current head position, initialize 0
    
public:
    Scheduler();
    virtual void schedule() = 0;    // virtual schedule function
    void output();
};

Scheduler::Scheduler() {
    headPos = 0;
}

void Scheduler::output() {
    timeInfo.printResult();
}

#endif
