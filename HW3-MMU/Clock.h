//
//  Clock.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_Clock_h
#define MMU_Clock_h

#include "PageReplace.h"

class Clock : public PageReplace {
    int type;           // 0 for physical, 1 for virtual
    int hand;           // for Clock based on virtual pages
    
public:
    Clock(int type);
    
    int choosePageToReplace();
    
};

Clock::Clock(int type) {
    this->type = type;
    hand = 0;
}

int Clock::choosePageToReplace() {
    
    if (type == 1) {                                            // based on virtual page
        int index;
        while (true) {
            if (hand == 64) {                                   // wrap clock hand
                hand = 0;
            }
            
            if (page_table[hand].PRESENT) {
                if (page_table[hand].REFERENCE) {
                    page_table[hand].REFERENCE = 0;
                    hand++;
                    
                } else {                                        // If R=0 page is evicted
                    index = hand;
                    hand++;
                    return index;
                }
                
            } else {
                hand++;
            }
        }
        
    } else {                                                    // based on physical page
        int count = 0;
        while (true) {        // Recursively inspect the R bit of the oldest page
            
            int index = validPageIndexQueue.front();
            
            if (!page_table[index].REFERENCE) {             // If R=0 page is evicted, new page will be added to tail in executeInstr()
                validPageIndexQueue.pop();
                return index;
            } else {
                page_table[index].REFERENCE = 0;                        // bit is cleared
                validPageIndexQueue.pop();                  // page is put at the end of the list
                validPageIndexQueue.push(index);
            }
            
            count++;
            if (count == validPageIndexQueue.size()) {      // wrap clock hand
                count = 0;
            }
        }
        
    }
}

#endif
