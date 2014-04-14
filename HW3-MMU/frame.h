//
//  frame.h
//  MMU
//
//  Created by Liang Fang on 4/5/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_frame_h
#define MMU_frame_h

class frame {
    int indexOfPageTable;

public:
    frame();
    int getIndexOfPageTable();
    void setIndex(int index);
    
};

frame::frame() {
    indexOfPageTable = -1;          // -1 indicate not currently mapped by any virtual page
}

int frame::getIndexOfPageTable() {
    return indexOfPageTable;
}

void frame::setIndex(int index) {
    indexOfPageTable = index;
}

#endif
