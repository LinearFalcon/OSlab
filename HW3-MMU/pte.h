//
//  pte.h
//  MMU
//
//  Created by Liang Fang on 4/5/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_pte_h
#define MMU_pte_h

// Bit fields for page table entry
struct pte {
    unsigned int PRESENT:1;
    unsigned int MODIFIED:1;
    unsigned int REFERENCE:1;
    unsigned int PAGEDOUT:1;
    unsigned int INDEX:28;
};

#endif
