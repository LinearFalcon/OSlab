//
//  Time.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_Time_h
#define IOSched_Time_h

#include "UniversalVar.h"

// Three kinds of time point: 1. submission to issue, 2. start of disk operation, 3. completion
class Time {
    
public:
    int TIME;                    // count time
    int total_movement;
    int arrival_time[1000];      // arrival time of each IO request, at most 1000 IO requests
    int diskStart_time[1000];    // disk start time of each IO request
    int complete_time[1000];      // disk end time(completion time) of each IO request
    int max_waittime;
    
    Time();
    void printResult();
};

// Initialization
Time::Time() {
    TIME = 0;
    total_movement = 0;
    for (int i = 0; i < 1000; i++) {
        arrival_time[i] = -1;
    }
    for (int i = 0; i < 1000; i++) {
        diskStart_time[i] = 0;
    }
    for (int i = 0; i < 1000; i++) {
        complete_time[i] = 0;
    }
    max_waittime = 0;
}

void Time::printResult() {
    int sum_TurnAroundTime = 0;
    for (int i = 0; i < numOfRequest; i++) {
        sum_TurnAroundTime += complete_time[i] - arrival_time[i];
    }
    int sum_WaitTime = 0;
    for (int i = 0; i < numOfRequest; i++) {
        int waitT = diskStart_time[i] - arrival_time[i];
        sum_WaitTime += waitT;

        if (waitT > max_waittime) {         // update max wait time
            max_waittime = waitT;
        }
    }
/*
    for (int i = 0; i < numOfRequest; i++) {
        cout << i << ": " << arrival_time[i] << "  " << diskStart_time[i] << "  " << complete_time[i] << endl;
    }
*/    
    printf("SUM: %d %d %.2lf %.2lf %d\n", TIME,
           total_movement, (double)sum_TurnAroundTime / numOfRequest, (double)sum_WaitTime / numOfRequest, max_waittime);
    
}

#endif
