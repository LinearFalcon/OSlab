//
//  NRU.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_NRU_h
#define MMU_NRU_h
#include "PageReplace.h"

class NRU : public PageReplace {
    vector<int> class0;
    vector<int> class1;
    vector<int> class2;
    vector<int> class3;
    int pageReplaceCount;
    
public:
    NRU();
    
    int choosePageToReplace();
    
    void createClass();
    
    void resetReferenceBit();  // reset all REFERENCE bit of valid page table entries every 10th page replacement
};

NRU::NRU() {
    pageReplaceCount = 0;
}

int NRU::choosePageToReplace() {
    createClass();
    
    pageReplaceCount++;
    if (pageReplaceCount % 10 == 0) {
        resetReferenceBit();
    }
    
    if (!class0.empty()) {
        int index = myRandom(class0.size());
        return class0[index];
    } else if (!class1.empty()) {
        int index = myRandom(class1.size());
        return class1[index];
    } else if (!class2.empty()) {
        int index = myRandom(class2.size());
        return class2[index];
    } else {                     // !class3.empty()), since it's not possible that all classX is empty
        int index = myRandom(class3.size());
        return class3[index];
    }
    
}

void NRU::createClass() {
    // first clear all class vector
    class0.clear();
    class1.clear();
    class2.clear();
    class3.clear();
    
    for (int i = 0; i < 64; i++) {
        if (page_table[i].PRESENT) {
            bool R = page_table[i].REFERENCE;
            bool M = page_table[i].MODIFIED;
            if (!R && !M) {
                class0.push_back(i);
            } else if (!R && M) {
                class1.push_back(i);
            } else if (R && !M) {
                class2.push_back(i);
            } else {
                class3.push_back(i);
            }
        }
    }
}

void NRU::resetReferenceBit() {
    for (int i = 0; i < 64; i++) {
        if (page_table[i].PRESENT) {
            page_table[i].REFERENCE = 0;
        }
    }
}

#endif
