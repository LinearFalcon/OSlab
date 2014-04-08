//
//  Module.h
//  2PassLinker
//
//  Created by Liang Fang on 2/13/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef _PassLinker_Module_h
#define _PassLinker_Module_h
#include <vector>
#include <iostream>
using namespace std;

class Module {
    int defcount;
    vector<string> useList;                    //useList to store symbol token in use list section
    vector<pair<string, int> > instrTable;     //instrTable stores instr pairs
    int baseAddr;
    int size;
    
public:
    Module(int defcount,
           vector<string> useList,
           vector<pair<string, int> > instrTable,
           int baseAddr,
           int size) {
        this->defcount = defcount;
        this->useList = useList;
        this->instrTable = instrTable;
        this->baseAddr = baseAddr;
        this->size = size;
    }
    
    int getBaseAddr() {
        return baseAddr;
    }
    
    int getModuleSize() {
        return size;
    }
    
    vector<string> getUseList() {
        return useList;
    }
    
    vector<pair<string, int> > getInstrTable() {
        return instrTable;
    }
    
    int  getDefcount() {
        return defcount;
    }
};

#endif
