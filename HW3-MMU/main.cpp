//
//  main.cpp
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#include <iostream>
#include "UniversalVar.h"
#include "IO.h"
#include "frame.h"


int main(int argc, char ** argv)
{
    // get info and store from command
    processCommand(argc, argv);
    
    // set algoPointer pointing to specific paging algorithm object
    PageReplace* algoPointer;
    if (algoType == type_NRU) {
        algoPointer = new NRU();
    } else if (algoType == type_LRU) {
        algoPointer = new LRU();
    } else if (algoType == type_Random) {
        algoPointer = new Random();
    } else if (algoType == type_FIFO) {
        algoPointer = new FIFO();
    } else if (algoType == type_SecondChance) {
        algoPointer = new SecondChance();
    } else if (algoType == type_PhysicalClock) {
        algoPointer = new Clock(0);
    } else if (algoType == type_VirtualClock) {
        algoPointer = new Clock(1);
    } else if (algoType == type_PhysicalAging) {
        algoPointer = new Aging(0);
    } else if (algoType == type_VirtualAging) {
        algoPointer = new Aging(1);
    }
    
    // initialize page table to all zero and frame table to all frame value equals to -1
    initializePageTableAndFrameTable();
    
    
    // Each time read a line from input path, then process and output
    ifstream infile;
    infile.open(inputPath);
    if (infile.is_open()) {
        while (getline(infile, str)) {
            vector<string> instrs = splitString(str);
            if ((instrs[0])[0] != '#') {                // ignore comment
                operationVal = atoi(instrs[0].c_str());
                whichPage = atoi(instrs[1].c_str());
                
                
                algoPointer->executeInstr();
                
                
                stats.inst_count++;                     // increment instruction count
            }
            
        }
    }
    infile.close();
    
    if (option_P) {
        algoPointer->printPageTable();
    }
    if (option_F) {
        algoPointer->printFrameTable();
    }
    if (option_S) {
        algoPointer->printSum();
    }

    
    return 0;
}

