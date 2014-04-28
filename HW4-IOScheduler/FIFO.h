//
//  FIFO.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_FIFO_h
#define IOSched_FIFO_h

#include "Scheduler.h"

class FIFO : public Scheduler {
    
public:
    /* schedule funtion **/
    void schedule() {
        
        for (int i = 0; i < numOfRequest; i++) {                    // update all IO requests' arrival time
            timeInfo.arrival_time[i] = IO_queue[i].arrivalTime;
        }
             
        for (int i = 0; i < numOfRequest; i++) {
            if (timeInfo.TIME < timeInfo.arrival_time[i]) {     // if last io request completes but next io request doesn't arrive yet,
                                                                // set TIME to arrival time
                timeInfo.TIME = timeInfo.arrival_time[i];           // IO request arrive
            }
            
            
            IORequest io = IO_queue[i];

            timeInfo.diskStart_time[i] = timeInfo.TIME;     // disk operation begins, set disk start time to current time
            
            int headMoveTime = abs(io.track - headPos);     // time from head begin to move to IO completion
            timeInfo.total_movement += headMoveTime;        // update total head move number
            timeInfo.TIME += headMoveTime;                  // set current time to head moving finish time
            timeInfo.complete_time[i] = timeInfo.TIME;      // update complete time
            headPos = io.track;
        }
    }
};

#endif
