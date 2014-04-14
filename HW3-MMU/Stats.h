//
//  Stats.h
//  MMU
//
//  Created by Liang Fang on 4/5/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_Stats_h
#define MMU_Stats_h
#include <stdio.h>

class Stats {
    
public:
    long long totalcost; // overall execution time in cycles
    long long inst_count;  // count number of instructions
    long long maps; // number of map operations
    long long unmaps; // number of unmap operations
    long long ins; // number of pagein operations
    long long outs; // number of pageout operations
    long long zeros; // number of zero operations
    
    Stats();
    
    void print();
};

Stats::Stats() {
    totalcost = 0;
    inst_count = 0;
    maps = 0;
    unmaps = 0;
    ins = 0;
    outs = 0;
    zeros = 0;
}

void Stats::print() {
    totalcost = (long)400 * (maps + unmaps) + (long)3000 * (ins + outs) + (long)150 * zeros + (long)1 * inst_count;
    printf("SUM %d U=%d M=%d I=%d O=%d Z=%d ===> %llu\n",
           inst_count, unmaps, maps, ins, outs, zeros, totalcost);
}

#endif
