//
//  Scheduler.h
//  Scheduler
//
//  Created by Liang Fang on 3/8/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef Scheduler_Scheduler_h
#define Scheduler_Scheduler_h

#include "Variable.h"
#include <algorithm>

class Scheduler {
protected:
    int ofs;
    float IO_ActiveTime;          // count time for at least one process is performing IO
    vector<Process> results;
    vector<Process> IOBuffer;         // IOBuffer stores <index, process> pair in IO blocked state       Not sure if map's element is in order?????
    vector<Process> runningBuffer; // runningBuffer can only have at most one process!!!!!!!!!
    
public:
    Scheduler() {
        ofs = 0;
        IO_ActiveTime = 0;
    }
    
    virtual void beginSchedule() = 0;   // virtual funtion for process schedule
    
    void output() {          // virtual function for output schedule info
        int lastFT = results[results.size() - 1].getFT();       // get FT of last event before sort
        sort(results.begin(), results.end(), sortByIndex);      // first sort process by index
        
        if (schedulerType == FCFS) {
            cout << "FCFS" << endl;
        } else if (schedulerType == LCFS) {
            cout << "LCFS" << endl;
        } else if (schedulerType == SJF) {
            cout << "SJF" << endl;
        } else {
            cout << "RR " << quantum << endl;
        }
        
        
        float sumOfCPUTime = 0;
        float sumOfTurnaroudTime = 0;
        float sumOfCPUWaitingTime = 0;
        for (int i  = 0; i < results.size(); i++) {
            Process p = results[i];
            printf("%04d: %4d %4d %4d %4d | %4d %4d %4d %4d\n", p.index, p.getAT(), p.getTC(), p.getCB(), p.getIO(),
                   p.getFT(), p.getTT(), p.getIT(), p.getCW());
            sumOfCPUTime += p.getTC();
            sumOfTurnaroudTime += p.getTT();
            sumOfCPUWaitingTime += p.getCW();
        }
        
        float num = results.size();
        printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", lastFT, sumOfCPUTime / lastFT * 100, IO_ActiveTime / lastFT * 100,
               sumOfTurnaroudTime / num, sumOfCPUWaitingTime / num, num / lastFT * 100);

    }
    
    /* sort helper function for algorthm.sort **/
    static bool sortByIndex(const Process &p1, const Process &p2) {
        return p1.index < p2.index;
    }
    
    int myrandom(int burst) {
        if (ofs + 1 >= numOfRandom) {
            ofs = 0;
        }
        int c = ofs;
        ofs++;
        return 1 + (randvals[c] % burst);
    }
    
    int getOfs() {
        return ofs;
    }
    
    int getIOActiveTime() {
        return IO_ActiveTime;
    }
    
    vector<Process> getResults() {
        return results;
    }
};

#endif
