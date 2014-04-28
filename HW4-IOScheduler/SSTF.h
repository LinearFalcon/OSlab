//
//  SSTF.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_SSTF_h
#define IOSched_SSTF_h

#include "Scheduler.h"
#include <limits>

class SSTF : public Scheduler {
    
public:
    /* schedule funtion **/
    void schedule() {
        for (int i = 0; i < numOfRequest; i++) {                    // update all IO requests' arrival time
            timeInfo.arrival_time[i] = IO_queue[i].arrivalTime;     // The order is not scheduling order !!!!!!
        }
        
        while (!IO_queue.empty()) {
            int minDist = numeric_limits<int>::max();
            int minIndex = -1;
            // choose an IO request to disk
            for (int i = 0; i < IO_queue.size(); i++) {
                if (IO_queue[i].arrivalTime <= timeInfo.TIME) {     // if this IO request has been submited/arrived
                    if (minDist > abs(IO_queue[i].track - headPos)) {   // find closest IO request
                        minDist = abs(IO_queue[i].track - headPos);
                        minIndex = i;
                    }
                }
            }
            
            
            if (minIndex != -1) {                                       // one IO request is chosen, names io
                IORequest io = IO_queue[minIndex];
                IO_queue.erase(IO_queue.begin() + minIndex);            // erase chosen IO request from IO_queue
                
                timeInfo.diskStart_time[io.index] = timeInfo.TIME;
                
                int headMoveTime = abs(io.track - headPos);     // time from head begin to move to IO completion
                timeInfo.total_movement += headMoveTime;        // update total head move number
                timeInfo.TIME += headMoveTime;                  // set current time to head moving finish time
                timeInfo.complete_time[io.index] = timeInfo.TIME;      // update complete time
                headPos = io.track;
            } else {                                            // no IO request arrive yet, so set time to arrival time of head of IO_queue
                if (!IO_queue.empty()) {
                    timeInfo.TIME = IO_queue.front().arrivalTime;
                }
            }
        }
    }
};

#endif
