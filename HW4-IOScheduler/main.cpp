//
//  main.cpp
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#include <iostream>
using namespace std;
#include "HelperFunc.h"
#include "Scheduler.h"
#include "FIFO.h"
#include "SSTF.h"
#include "SCAN.h"
#include "CSCAN.h"
#include "FSCAN.h"

int main(int argc, char ** argv)
{
    read(argc, argv);   // read command and input file
    Scheduler* sche;
    if (scheduleType == type_FIFO) {
        sche = new FIFO();
    } else if (scheduleType == type_SSTF) {
        sche = new SSTF();
    } else if (scheduleType == type_SCAN) {
        sche = new SCAN();
    } else if (scheduleType == type_CSCAN) {
        sche = new CSCAN();
    } else if (scheduleType == TYPE_FSCAN) {
        sche = new FSCAN();
    }
    
    sche->schedule();
    sche->output();
    
    return 0;
}

