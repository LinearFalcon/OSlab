//
//  LRU.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_LRU_h
#define MMU_LRU_h

#include "PageReplace.h"

class LRU : public PageReplace {
    
public:
    int choosePageToReplace() {
        int index = pageList_LRU.back();   // return the longest unused page index to replace
        pageList_LRU.pop_back();
        return index;
    }
};

#endif
