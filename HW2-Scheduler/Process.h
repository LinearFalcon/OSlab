//
//  Process.h
//  Scheduler
//
//  Created by Liang Fang on 3/8/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef Scheduler_Process_h
#define Scheduler_Process_h

class Process {
    
    
    int AT;     // arrival time
    int TC;     // total CPU time
    int CB;     // fixed CB
    int IO;     // fixed IO
    
    int CPUBurst;       // CPU burst in running state
    int IOBurst;        // IO burst in blocked state
    int remainingExecutionTime;     
    
    int finishTime;     // FT
    int turnaroundTime; // TT
    int IOTime;         // IT
    int CPUWaitingTime; // CW
    
    int stateEnterTime;  // time for this process entering a state: running or blocked
    
public:
    int index;      // public index for comparison
    
    Process() {
        
    }
    
    Process(int index, int AT, int TC, int CB, int IO) {
        this->index = index;
        this->AT = AT;
        this->TC = TC;
        this->CB = CB;
        this->IO = IO;
        remainingExecutionTime = TC;    //remaining execution time is initialized to total CPU time
        
        CPUBurst = 0;
        IOBurst = 0;
        finishTime = 0;
        turnaroundTime = 0;
        IOTime = 0;
        CPUWaitingTime = 0;
        
        stateEnterTime = 0;
    }
    
//    bool operator < (const Process& another) {
//		return this->index < another.index;
//	}
    
    const int getIndex() {
        return index;
    }
    
    int getStateEnterTime() {
        return stateEnterTime;
    }
    
    void setStateEnterTime(int t) {
        stateEnterTime = t;
    }
    
    int getAT() {
        return AT;
    }
    
    int getTC() {
        return TC;
    }
    
    int getCB() {
        return CB;
    }
    
    int getIO() {
        return IO;
    }
    
    int getFT() {
        return finishTime;
    }
    
    int getTT() {
        return turnaroundTime;
    }
    
    int getIT() {
        return IOTime;
    }
    
    int getCW() {
        return CPUWaitingTime;
    }
    
    int getRemainingTime() {
        return remainingExecutionTime;
    }
    
    int getCPUBurst() {
        return CPUBurst;
    }
    
    int getIOBurst() {
        return IOBurst;
    }
    
    void setCPUBurst(int newCB) {
        CPUBurst = newCB;
    }
    
    void setIOBurst(int newIO) {
        IOBurst = newIO;
    }
    
    void setRemainingTime(int newTime) {
        remainingExecutionTime = newTime;
    }
    
    void setFT(int t) {
        finishTime = t;
    }
    
    void setTT(int t) {
        turnaroundTime = t;
    }
    
    void setIT(int t) {
        IOTime = t;
    }
    
    void setCW(int t) {
        CPUWaitingTime = t;
    }
};

#endif
