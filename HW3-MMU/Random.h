//
//  Random.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_Random_h
#define MMU_Random_h

#include "PageReplace.h"

class Random : public PageReplace {
    
public:
    int choosePageToReplace() {
        int index = myRandom(num_frames);
        return frame_table[index].getIndexOfPageTable();
    }
};

#endif
