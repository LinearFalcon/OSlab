//
//  FIFO.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_FIFO_h
#define MMU_FIFO_h

#include "PageReplace.h"

class FIFO : public PageReplace {
    
public:
    int choosePageToReplace() {
        int res = validPageIndexQueue.front();
        validPageIndexQueue.pop();
        return res;
    }
};

#endif
