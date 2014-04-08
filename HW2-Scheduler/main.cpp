//
//  main.cpp
//  Scheduler
//
//  Created by Liang Fang on 3/8/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include "IO.h"
#include "FCFS_Scheduler.h"
#include "LCFS_Scheduler.h"
#include "SJF_Scheduler.h"
#include "RoundRobin_Scheduler.h"
using namespace std;

int main(int argc, char** argv)
{
    processInput(argc, argv);
    
    if (schedulerType == FCFS) { 
        FCFS_Scheduler scheduler;
        scheduler.beginSchedule();
        scheduler.output();
    } else if (schedulerType == LCFS) {
        LCFS_Scheduler scheduler;
        scheduler.beginSchedule();
        scheduler.output();
    } else if (schedulerType == SJF) {
        SJF_Scheduler scheduler;
        scheduler.beginSchedule();
        scheduler.output();
    } else {
        RoundRobin_Scheduler scheduler;
        scheduler.beginSchedule();
        scheduler.output();
    }

    return 0;
}

