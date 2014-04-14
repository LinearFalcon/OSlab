//
//  PageReplace.h
//  MMU
//
//  Created by Liang Fang on 4/4/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_PageReplace_h
#define MMU_PageReplace_h

#include "UniversalVar.h"
#include <vector>
#include <iomanip>
#include <queue>

/* Class Definition */
class PageReplace {
protected:
    int rofs;                           // random file reading counter
    vector<string> operations;          // store operations in order for current execution of instruction
    vector<vector<int> > parameters;     // store parameters of operations, ZERO has only one parameter, others have two
    
    queue<int> validPageIndexQueue;     // for FIFO, Second-Chance and Clock(physical) use, store page indexes currently in memory
    
    deque<int> pageList_LRU;            // for LRU use, store page indexes in memory
    
public:
    
    PageReplace();
    
    void executeInstr();
    
    void printOutput();
    void printPageTable();
    void printFrameTable();
    void printSum();
    
    int myRandom(int size);
    int getFreeFrameIndex();    // iterate over frame table to see if there is free frame, return -1 if no free frame
    void updateLRUList(int pageIndex);     // for LRU use, update list of page indexes when access, keep most recent accessed page in the head of list
    
    virtual int choosePageToReplace() = 0;  // choose a page when no free frame, return page index in page_table
};


/* Function Definition */

PageReplace::PageReplace() {
    rofs = 0;
}

void PageReplace::executeInstr() {
    
    if (page_table[whichPage].PRESENT) {            // if page present, just access
        if (operationVal == 1) {                    // if it is a write operation, set MODIFIED bit
            page_table[whichPage].MODIFIED = 1;
        }
        page_table[whichPage].REFERENCE = 1;    // set REFERENCE bit
        
    } else {                                        // if page not present in physical memory
        int freeFrameIndex = getFreeFrameIndex();   // check if there is free frame
        if (freeFrameIndex != -1) {                 // there is free frame
            page_table[whichPage].PRESENT = 1;      // set PRESENT bit
            if (operationVal == 1) {                // if it is a write operation, set MODIFIED bit
                page_table[whichPage].MODIFIED = 1;
            }
            page_table[whichPage].REFERENCE = 1;    // set REFERENCE bit
            page_table[whichPage].INDEX = freeFrameIndex;   // set INDEX bit of page
            
            frame_table[freeFrameIndex].setIndex(whichPage);    // set frame pointing back to page table
            
            
            // add operation strings to operations vector
            operations.push_back("ZERO");
            operations.push_back("MAP");
            vector<int> temp;
            temp.push_back(freeFrameIndex);
            parameters.push_back(temp);
            temp.clear();
            temp.push_back(whichPage);
            temp.push_back(freeFrameIndex);
            parameters.push_back(temp);
            temp.clear();

            // increment count
            stats.zeros++;
            stats.maps++;
            
        } else {                                            // there is no free frame
            int pageIndex = choosePageToReplace();          // use paging algorithm to choose a page present and frame related to replace
            int frameIndex = page_table[pageIndex].INDEX;
            
            // reset page table entry's bits of chosen page
            page_table[pageIndex].INDEX = 0;                // UNMAP chosen page and frame
            page_table[pageIndex].PRESENT = 0;
            page_table[pageIndex].REFERENCE = 0;
            
            // add UNMAP operation
            operations.push_back("UNMAP");
            vector<int> temp;
            temp.push_back(pageIndex);
            temp.push_back(frameIndex);
            parameters.push_back(temp);
            temp.clear();
            
            // increment count
            stats.unmaps++;
            
            bool modified = page_table[pageIndex].MODIFIED;             // determine if chosen page been modified
            bool pagedout = page_table[whichPage].PAGEDOUT;             // determine if operation page in instruction been previously pagedout
            if (modified) {           // if page has been modified
                page_table[pageIndex].PAGEDOUT = 1;                 // OUT chosen page
                page_table[pageIndex].MODIFIED = 0;         // OUT a modified page, so reset MODIFIED bit
                
                operations.push_back("OUT");
                vector<int> temp;
                temp.push_back(pageIndex);
                temp.push_back(frameIndex);
                parameters.push_back(temp);
                temp.clear();
                
                // increment count
                stats.outs++;
                
                
                // MAP related bits set, always do no mater modified
                page_table[whichPage].PRESENT = 1;
                page_table[whichPage].REFERENCE = 1;
                if (operationVal == 1) {
                    page_table[whichPage].MODIFIED = 1;
                }
                page_table[whichPage].INDEX = frameIndex;
                
                frame_table[frameIndex].setIndex(whichPage);
                
                
                
                // chech if new page has ever been swapped out
                if (pagedout) {       // if page has been swapped out
                    
                    // add operation strings to operations vector    IN MAP
                    operations.push_back("IN");
                    operations.push_back("MAP");
                    vector<int> temp;
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    
                    // increment count
                    stats.ins++;
                    stats.maps++;
                } else {               // if page never been swapped out
                    
                    // add operation strings to operations vector    ZERO  MAP
                    operations.push_back("ZERO");
                    operations.push_back("MAP");
                    vector<int> temp;
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    
                    // increment count
                    stats.zeros++;
                    stats.maps++;
                }
            } else {                // if page never be modifie
                
                // MAP related bits set, always do no mater modified
                page_table[whichPage].PRESENT = 1;
                page_table[whichPage].REFERENCE = 1;
                if (operationVal == 1) {
                    page_table[whichPage].MODIFIED = 1;
                }
                page_table[whichPage].INDEX = frameIndex;
                
                frame_table[frameIndex].setIndex(whichPage);
                
                // chech if new page has ever been swapped out
                if (pagedout) {       // if page has been swapped out
                    
                    // add operation strings to operations vector    IN MAP
                    operations.push_back("IN");
                    operations.push_back("MAP");
                    vector<int> temp;
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    
                    // increment count
                    stats.ins++;
                    stats.maps++;
                } else {               // if page never been swapped out
                    
                    // add operation strings to operations vector    ZERO  MAP
                    operations.push_back("ZERO");
                    operations.push_back("MAP");
                    vector<int> temp;
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    temp.push_back(whichPage);
                    temp.push_back(frameIndex);
                    parameters.push_back(temp);
                    temp.clear();
                    
                    // increment count
                    stats.zeros++;
                    stats.maps++;
                }
            }
        }
        
        validPageIndexQueue.push(whichPage);    // add new page into tail of queue,
                                                // because no matter there is a free frame, there will always be a MAP operation
    }
    updateLRUList(whichPage);         // update LRU order list
    
    if (option_O) {
        printOutput();
        
//        printPageTable();
//        printFrameTable();
    }

    
    // clear both vectors, since we only need to store this instruction's info
    operations.clear();
    parameters.clear();
}

void PageReplace::printOutput() {
    cout << "==> inst: " << operationVal << " " << whichPage << endl;
    for (int i = 0; i < operations.size(); i++) {
        cout << stats.inst_count << ": " << operations[i];
        if (operations[i] == "ZERO") {
            cout << setw(9) << (parameters[i])[0] << endl;
        } else if (operations[i] == "MAP") {
            cout << setw(6) << (parameters[i])[0] << setw(4) << (parameters[i])[1] << endl;
        } else if (operations[i] == "UNMAP") {
            cout << setw(4) << (parameters[i])[0] << setw(4) << (parameters[i])[1] << endl;
        } else if (operations[i] == "IN") {
            cout << setw(7) << (parameters[i])[0] << setw(4) << (parameters[i])[1] << endl;
        } else if (operations[i] == "OUT") {
            cout << setw(6) << (parameters[i])[0] << setw(4) << (parameters[i])[1] << endl;
        }
    }
    
}

void PageReplace::printPageTable() {
    for (int i = 0; i < 64; i++) {
        if (page_table[i].PRESENT == 0) {       // if PRESENT not set
            if (page_table[i].PAGEDOUT) {
                cout << "# ";
            } else {
                cout << "* ";
            }
        } else {                                // if PRESENT set
            cout << i << ":";
            if (page_table[i].REFERENCE) {              
                cout << "R";
            } else {
                cout << "-";
            }
            if (page_table[i].MODIFIED) {
                cout << "M";
            } else {
                cout << "-";
            }
            if (page_table[i].PAGEDOUT) {
                cout << "S";
            } else {
                cout << "-";
            }
            cout << " ";
        }
    }
    cout << endl;
}

void PageReplace::printFrameTable() {
    for (int i = 0; i < num_frames; i++) {
        if (frame_table[i].getIndexOfPageTable() == -1) {
            cout << "* ";
        } else {
            cout << frame_table[i].getIndexOfPageTable() << " ";
        }
    }
    cout << endl;
}

void PageReplace::printSum() {
    stats.print();
}


int PageReplace::getFreeFrameIndex() {
    for (int i = 0; i < num_frames; i++) {
        if (frame_table[i].getIndexOfPageTable() == -1) {       // -1 means this frame is free
            return i;
        }
    }
    return -1;
}

int PageReplace::myRandom(int size) {
    if (rofs >= numOfRandom) {
        rofs = 0;
    }
    int c = rofs;
    rofs++;
    return randvals[c] % size;
}

void PageReplace::updateLRUList(int pageIndex) {
    int index = -1;
    for (int i = 0; i < pageList_LRU.size(); i++) {
        if (pageList_LRU[i] == pageIndex) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {          // means new page doesn't exist in memory during this operation,
        pageList_LRU.push_front(pageIndex);                 // push page index to the head of list
    } else {                    // means this page existed in memory, this operation is just accessing a presented page
        pageList_LRU.erase(pageList_LRU.begin() + index);   // take out this page index from list
        pageList_LRU.push_front(pageIndex);                 // push page index to the head of list
    }
}

#endif
