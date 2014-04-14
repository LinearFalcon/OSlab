//
//  SecondChance.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_SecondChance_h
#define MMU_SecondChance_h

#include "PageReplace.h"

class SecondChance : public PageReplace {
    
public:
    int choosePageToReplace() {
        int count = 0;
        while (count < validPageIndexQueue.size()) {        // Recursively inspect the R bit of the oldest page
            
            int index = validPageIndexQueue.front();
            
            if (!page_table[index].REFERENCE) {             // If R=0 page is old and unused -> replace
                validPageIndexQueue.pop();
                return index;
            } else {
                page_table[index].REFERENCE = 0;                        // bit is cleared
                validPageIndexQueue.pop();                  // page is put at the end of the list
                validPageIndexQueue.push(index);
            }
            count++;
        }
        
        // all pages have R=1, the algorithm degenerates to FIFO
        int res = validPageIndexQueue.front();
        validPageIndexQueue.pop();
        return res;
    }
};

#endif
