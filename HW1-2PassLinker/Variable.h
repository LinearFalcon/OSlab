//
//  Variable.h
//  2PassLinker
//
//  Created by Liang Fang on 2/15/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef _PassLinker_Variable_h
#define _PassLinker_Variable_h
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include "Token.h"
#include "Module.h"
using namespace std;

string str;
int defcount;               //num of definitions
int usecount;               //num of used symbols
int codecount;              //length of the module
int linecount = 1;          //line starts from 1, offset also starts from 1
int moduleCount = 0;
int baseAddr = 0;

Token last;
Token token;
int relativeAddr;
int instruction;

vector<int> moduleDefCount;     //store defcount of each module in pass 1
vector<int> moduleBaseAddr;     //store base address of each module in pass 1
vector<int> moduleSize;         //store size of each module in pass 1


vector<string> tokens;          //store tokens of parsed line
vector<int> offsets;
queue<Token> tokenList;

vector<string> useList;                    //Temporarily store symbol token in use list section
vector<pair<string, int> > instrTable;     //Temporarily store instr pairs in a module

vector<string> allUseList;                  //store all symbols from uselist of every module
vector<pair<string, int> > symbolTable;     //Store all defined symbols(including multiple defined) and address <symbol, absoluteAddr>
vector<Module> moduleTable;                 //Store all module object

#endif
