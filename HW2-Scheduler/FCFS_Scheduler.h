//
//  FCFS_Scheduler.h
//  Scheduler
//
//  Created by Liang Fang on 3/9/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef Scheduler_FCFS_Scheduler_h
#define Scheduler_FCFS_Scheduler_h

#include "Scheduler.h"
#include "Process.h"
#include "Variable.h"
#include <deque>
#include <vector>

class FCFS_Scheduler : public Scheduler {
    deque<Process> processQueue;    // stores process in Ready state
    
    
public:
    /* schedule funtion **/
    void beginSchedule() {
        while (!processQueue.empty() || !runningBuffer.empty() || !IOBuffer.empty() || !allProcess.empty()) {   //anything not empty, then continue
     
            /* check if new process arrive **/
            if (!allProcess.empty()) {
                
                while (true) {                          // it is possible there is more than one process arrive at the same time
                    Process front = allProcess.front();
                    if (TIME == front.getAT()) {
                        processQueue.push_back(front);
                        allProcess.pop();
                    } else {
                        break;
                    }
                }
                
            }
            
            
            /* process on IO block state **/
            if (!IOBuffer.empty()) {
                for (int i = 0; i < IOBuffer.size(); i++) {
                    if (TIME == IOBuffer[i].getStateEnterTime() + IOBuffer[i].getIOBurst()) {             // run out of burst
                        Process p = IOBuffer[i];
                        processQueue.push_back(p);
                        IOBuffer.erase(IOBuffer.begin() + i);
                        i--;
                        
                    }
                }
                
                IO_ActiveTime++;
            }
            
            if (!runningBuffer.empty()) {
                Process& p = runningBuffer[0];
                p.setRemainingTime(p.getRemainingTime() - 1);
                
                if (TIME == p.getStateEnterTime() + p.getCPUBurst()) {    // process run out of burst
                    runningBuffer.clear();
                    
                    if (p.getRemainingTime() == 0) {                // process finish executing, add to results
                        p.setFT(TIME);
                        p.setTT(p.getFT() - p.getAT());
                        results.push_back(p);
                    } else {
                        p.setStateEnterTime(TIME);
                        int burst = myrandom(p.getIO());
                        p.setIOBurst(burst);
                        
                        IOBuffer.push_back(p);                                     
                    }
                    
                } else {                                // not run out of burst, nothing happens
                }
 
            }
                
            // check again if runningBuffer empty and processQueue has process waiting, then scheduler pick process since context swtich cost is 0
            if (runningBuffer.empty()) {
                if (!processQueue.empty()) {
                    Process p = processQueue.front();
                    processQueue.pop_front();
                    p.setStateEnterTime(TIME);
                    
                    int burst = myrandom(p.getCB());
                    if (p.getRemainingTime() < burst) {
                        burst = p.getRemainingTime();
                    }
                    p.setCPUBurst(burst);
                    runningBuffer.push_back(p);
                }
            }

            for (deque<Process>::iterator i = processQueue.begin(); i != processQueue.end(); i++) {     // update CW of process in Ready queue
                i->setCW(i->getCW() + 1);
            }
            for (vector<Process>::iterator i = IOBuffer.begin(); i != IOBuffer.end(); i++) {
                i->setIT(i->getIT() + 1);
            }
            
            TIME++;
            
        }
    }
    
    
    deque<Process> getProcessQueue() {
        return processQueue;
    }
};

#endif
