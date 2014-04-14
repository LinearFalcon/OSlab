//
//  Aging.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_Aging_h
#define MMU_Aging_h

#include "PageReplace.h"
#include <limits>

class Aging : public PageReplace {
    int type;       // 0 for physical, 1 for virtual
    vector<unsigned int> counters;   // 64 counter for 64 pages, unsigned int is 32 bit
    
public:
    Aging(int type);
    
    void updateCounters();
    
    int choosePageToReplace();

};

Aging::Aging(int type) {
    this->type = type;
    for (int i = 0; i < 64; i++) {      // initially, all counters of pages are zero
        counters.push_back(0);
    }
}

void Aging::updateCounters() {
    for (int i = 0; i < 64; i++) {
        if (page_table[i].PRESENT) {            // only update present pages' age info
            counters[i] = counters[i] >> 1;     // right shift 1 bit
            unsigned int rBit = page_table[i].REFERENCE;
            rBit <<= 31;
            counters[i] = counters[i] | rBit;
        }
    }
}

int Aging::choosePageToReplace() {
    
    updateCounters();

    int index = -1;
    unsigned int min = numeric_limits<unsigned int>::max();     // initialize min as maximum value
    
    if (type == 1) {                                            // based on virtual page
        for (int i = 0; i < 64; i++) {
            if (page_table[i].PRESENT) {
                if (counters[i] < min) {
                    index = i;
                    min = counters[i];
                }
                page_table[i].REFERENCE = 0;            // reset REFERENCE bit of all pages in memory
            }
        }
        
    } else {                                                    // based on physical page
        for (int i = 0; i < num_frames; i++) {
            int pageIndex = frame_table[i].getIndexOfPageTable();
            if (counters[pageIndex] < min) {
                index = pageIndex;
                min = counters[pageIndex];
            }
            
            page_table[pageIndex].REFERENCE = 0;            // reset REFERENCE bit of all pages in memory
        }
        
    }
    counters[index] = 0;
    return index;
}

#endif
