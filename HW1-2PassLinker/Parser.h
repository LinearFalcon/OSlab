//
//  Parser.h
//  2PassLinker
//
//  Created by Liang Fang on 2/15/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef _PassLinker_Parser_h
#define _PassLinker_Parser_h
#include "HelperFunc.h"
#include "Variable.h"
#include "Module.h"
#include <cstdlib>

/*
 * parse text for the first time, generate symbol table and moduletable
 */
void parser_pass1(char* inputPath) {
    ifstream infile;
    infile.open(inputPath);         //This is the first pass
    
    
    if (infile.is_open()) {
        while (getline(infile, str)) {
            getTokenOffset(str, offsets);
            tokens = split(str);
            for (int i = 0; i < tokens.size(); i++) {
                Token k(linecount, offsets[i], tokens[i]);
                tokenList.push(k);
            }
            
            last = Token(linecount, str.length() + 1, "this is a mark token");     //store ending linenum and offset of the file
            
            linecount++;
            tokens.clear();
            offsets.clear();
        }
        tokenList.push(last);      // take last as the last token
    
        
        while (tokenList.size() > 1) {
            
            /********* process definition list **********/
            
            token = tokenList.front();
            defcount = atoi(token.getStr().c_str());
            tokenList.pop();
            if (tokenList.empty()) {
                parseerror(0, token.getLinenum(), token.getOffset());       //missing defcount, parse error: NUM_EXPECTED
                exit(0);
            }
            if (defcount > 16) {
                parseerror(4, token.getLinenum(), token.getOffset());             //parse error: TO_MANY_DEF_IN_MODULE
                exit(0);
            } else {
                for (int i = 0; i < defcount; i++) {
                    token = tokenList.front();
                    tokenList.pop();
                    if (tokenList.empty()) {
                        parseerror(1, token.getLinenum(), token.getOffset());    //parse error: SYM_EXPECTED
                        exit(0);
                    } else if (token.getStr().length() > 16) {
                        parseerror(3, token.getLinenum(), token.getOffset());    //parse error: SYM_TOLONG
                        exit(0);
                    } else if (!((token.getStr()[0] >= 'a' && token.getStr()[0] <= 'z') || (token.getStr()[0] >= 'A' && token.getStr()[0] <= 'Z'))) {
                        parseerror(1, token.getLinenum(), token.getOffset());    //parse error: SYM_EXPECTED
                        exit(0);
                    }
                    Token symbol_defined = token;
                    
                    token = tokenList.front();
                    tokenList.pop();
                    if (tokenList.empty() || !isTokenNumber(token)) {
                        parseerror(0, token.getLinenum(), token.getOffset());    //parse error: NUM_EXPECTED
                        exit(0);
                    }
                    relativeAddr = atoi(token.getStr().c_str());
                    symbolTable.push_back(make_pair(symbol_defined.getStr(), relativeAddr + baseAddr));
                }
            }
            
            /********* process use list **********/
            
            token = tokenList.front();
            usecount = atoi(token.getStr().c_str());
            tokenList.pop();
            if (tokenList.empty()) {
                parseerror(0, token.getLinenum(), token.getOffset());       //missing usecount, parse error: NUM_EXPECTED
                exit(0);
            }
            if (usecount > 16) {
                parseerror(5, token.getLinenum(), token.getOffset());             //parse error: TO_MANY_DEF_IN_MODULE
                exit(0);
            } else {
                for (int i = 0; i < usecount; i++) {
                    token = tokenList.front();
                    tokenList.pop();
                    if (tokenList.empty()) {
                        parseerror(1, token.getLinenum(), token.getOffset());    //parse error: SYM_EXPECTED
                        exit(0);
                    } else if (token.getStr().length() > 16) {
                        parseerror(3, token.getLinenum(), token.getOffset());    //parse error: SYM_TOLONG
                        exit(0);
                    } else if (!((token.getStr()[0] >= 'a' && token.getStr()[0] <= 'z') || (token.getStr()[0] >= 'A' && token.getStr()[0] <= 'Z'))) {
                        parseerror(1, token.getLinenum(), token.getOffset());    //parse error: SYM_EXPECTED
                        exit(0);
                    }

                }
            }
            
            /********* process program text **********/
            
            token = tokenList.front();
            codecount = atoi(token.getStr().c_str());
            tokenList.pop();
            if (tokenList.empty()) {
                parseerror(0, token.getLinenum(), token.getOffset());       //missing codecount, parse error: NUM_EXPECTED
                exit(0);
            }
            if (codecount + baseAddr > 512) {
                parseerror(6, token.getLinenum(), token.getOffset());             //parse error: TO_MANY_INSTR
                exit(0);
            } else {
                for (int i = 0; i < codecount; i++) {
                    token = tokenList.front();
                    tokenList.pop();
                    if (tokenList.empty() || (token.getStr().compare("A") != 0 && token.getStr().compare("R") != 0 && token.getStr().compare("I") != 0 && token.getStr().compare("E") != 0)) {
                        parseerror(2, token.getLinenum(), token.getOffset());    //parse error: ADDR_EXPECTED
                        exit(0);
                    }
                    
                    token = tokenList.front();
                    tokenList.pop();

                    if (tokenList.empty() || !isInstrValid(token)) {
                        parseerror(2, token.getLinenum(), token.getOffset());    //parse error: ADDR_EXPECTED
                        exit(0);
                    }

                }
            }
            
            moduleCount++;
            moduleDefCount.push_back(defcount);
            moduleBaseAddr.push_back(baseAddr);
            moduleSize.push_back(codecount);
            baseAddr += codecount;
        }
        tokenList.pop();
    }
    infile.close();
}

/*
 * print out symbol table
 */
void print_symboltable() {
    int index = 0;
    vector<bool> definedBefore;                     // each element is a flag for each one in symbolTable
    for (int i = 0; i < symbolTable.size(); i++) {  // check if one element has been defined before
        bool pushed = false;
        for (int j = 0; j < i; j++) {
            if (symbolTable[j].first == symbolTable[i].first) {
                definedBefore.push_back(true);
                pushed = true;
                break;
            }
        }
        if (!pushed) {
            definedBefore.push_back(false);
        }
        
    }

    for (int i = 0; i < moduleCount; i++) {
        if (moduleDefCount[i] != 0) {
            for (int j = index; j < index + moduleDefCount[i]; j++) {
                if (!definedBefore[j]) {
                    pair<string, int> pair = symbolTable[j];
                    if (pair.second - moduleBaseAddr[i] > moduleSize[i] - 1) {
                        cout << "Warning: Module " << i + 1 << ": " << pair.first << " to big "
                        << pair.second << " (max=" << moduleSize[i] - 1
                        << ") assume zero relative" << endl;
                        symbolTable[j].second = 0 + moduleBaseAddr[i];               //symbol value too big, so set it to zero relative
                    }
                }
            }
            index += moduleDefCount[i];
        }
    }
    
    cout << "Symbol Table" << endl;                                 //print out symbol table
    for (int i = 0; i < symbolTable.size(); i++) {
        string s = symbolTable[i].first;
        bool isDefinedLater = false;

        for (int k = i + 1; k < symbolTable.size(); k++) {
            if (symbolTable[k].first == s) {
                isDefinedLater = true;
                break;
            }
        }
        
        if (!definedBefore[i]) {
            cout << symbolTable[i].first << "=" << symbolTable[i].second;
            if (isDefinedLater) {
                cout << " Error: This variable is multiple times defined; first value used" << endl;
            } else {
                cout << endl;
            }
        }

    }
    cout << endl;
}

/*
 * parse text for the second time, generating memory map
 */
void parser_pass2(char* inputPath) {
    ifstream infile;
    infile.open(inputPath);         //This is the first pass
    

    baseAddr = 0;
    if (infile.is_open()) {
        while (getline(infile, str)) {
            getTokenOffset(str, offsets);
            tokens = split(str);
            for (int i = 0; i < tokens.size(); i++) {
                Token k(linecount, offsets[i], tokens[i]);
                tokenList.push(k);
            }
            
            last = Token(linecount, str.length() + 1, "this is a mark token");     //store ending linenum and offset of the file
            
            linecount++;
            tokens.clear();
            offsets.clear();
        }
        tokenList.push(last);      // take last as the last token
        
        
        while (tokenList.size() > 1) {
            
            /* process definition list */
            
            token = tokenList.front();
            defcount = atoi(token.getStr().c_str());
            tokenList.pop();
            
            for (int i = 0; i < defcount; i++) {
                token = tokenList.front();
                tokenList.pop();
                    
                token = tokenList.front();
                tokenList.pop();
                
            }

            /* process use list */
            
            token = tokenList.front();
            usecount = atoi(token.getStr().c_str());
            tokenList.pop();

            for (int i = 0; i < usecount; i++) {
                token = tokenList.front();
                tokenList.pop();
                Token symbol_used = token;
                useList.push_back(symbol_used.getStr());
                allUseList.push_back(symbol_used.getStr());
            }
            
            /* process program text */
            
            token = tokenList.front();
            codecount = atoi(token.getStr().c_str());
            tokenList.pop();
            
            for (int i = 0; i < codecount; i++) {
                token = tokenList.front();
                tokenList.pop();
                    
                Token type = token;
            
                token = tokenList.front();
                tokenList.pop();
                    
                instruction = atoi(token.getStr().c_str());
                instrTable.push_back(make_pair(type.getStr(), instruction));
           
            }
            Module module(defcount, useList, instrTable, baseAddr, codecount);         //create a new module object using tokens parsed above
            moduleTable.push_back(module);
            useList.clear();
            instrTable.clear();
            baseAddr += codecount;
        }
    }
    infile.close();



    
    
    /* Begin output memory map and errors */
    cout << "Memory Map" << endl;
    int count = 0;
    vector<Module>::iterator i;
    vector<pair<string, int> >::iterator j;

    for (i = moduleTable.begin(); i != moduleTable.end(); i++) {
        vector<string> symbolUseList = i->getUseList();
        vector<pair<string, int> > instructions = i->getInstrTable();
        int baseAddr = i->getBaseAddr();
        int size = i->getModuleSize();
        vector<bool> symbolUsed(symbolUseList.size(), false);                   //store bool for whether symbol in uselist is actually used
        
        for (j = instructions.begin(); j != instructions.end(); j++) {
            string type = j->first;
            int instr = j->second;
            int opcode = j->second / 1000;
            int oprand = j->second - opcode * 1000;
            
            cout << reformInt(count) << ": ";
            if (type == "I") {                  //Immediate type
                if (instr > 9999) {                                             //rule 10
                    instr = 9999;
                    cout << reformInstr(instr) << " Error: Illegal immediate value; treated as 9999" << endl;
                } else {
                    cout << reformInstr(instr) << endl;
                }
            } else if (type == "A") {           //Absolute type
                if (instr > 9999) {                                             //rule 11
                    instr = 9999;
                    cout << reformInstr(instr) << " Error: Illegal opcode; treated as 9999" << endl;
                } else if (oprand > 512) {                                      //rule 8
                    cout << reformInstr(opcode * 1000) << " Error: Absolute address exceeds machine size; zero used" << endl;
                } else {
                    cout << reformInstr(instr) << endl;
                }
            } else if (type == "R") {           //Relative type
                if (instr > 9999) {                                             //rule 11
                    instr = 9999;
                    cout << reformInstr(instr) << " Error: Illegal opcode; treated as 9999" << endl;
                } else if (oprand > size) {
                    cout << reformInstr(opcode * 1000 + baseAddr) << " Error: Relative address exceeds module size; zero used" << endl;
                } else {
                    cout << reformInstr(instr + baseAddr) << endl;
                }
            } else if (type == "E") {           //External type
                if (instr > 9999) {                                             //rule 11
                    instr = 9999;
                    cout << reformInstr(instr) << " Error: Illegal opcode; treated as 9999" << endl;
                } else if (oprand > symbolUseList.size() - 1) {                    //rule 6
                    cout << reformInstr(instr) << " Error: External address exceeds length of uselist; treated as immediate" << endl;
                } else if (usedButNotDefined(symbolTable, symbolUseList[oprand])) { //rule 3
                    cout << reformInstr(opcode * 1000) << " Error: " << symbolUseList[oprand] << " is not defined; zero used" << endl;
                    symbolUsed[oprand] = true;                      //if used but not defined, treat as symbol used
                } else {
                    symbolUsed[oprand] = true;
                    int newoprand = getSymbolValue(symbolTable, symbolUseList[oprand]);
                    cout << reformInstr(opcode * 1000 + newoprand) << endl;
                }
            }
            count++;
        }

        for (int m = 0; m < symbolUsed.size(); m++) {
            if (!symbolUsed[m]) {
                cout << "Warning: Module " << i - moduleTable.begin() + 1 << ": "
                << symbolUseList[m] << " appeared in the uselist but was not actually used" << endl;
            }
        }
    }
}

void check_symbol_usage() {
    cout << endl;
    
    vector<bool> definedBefore;                     // each element is a flag for each one in symbolTable
    for (int i = 0; i < symbolTable.size(); i++) {  // check if one element has been defined before
        bool pushed = false;
        for (int j = 0; j < i; j++) {
            if (symbolTable[j].first == symbolTable[i].first) {
                definedBefore.push_back(true);
                pushed = true;
                break;
            }
        }
        if (!pushed) {
            definedBefore.push_back(false);
        }
        
    }
    

    for (int i = 0; i < symbolTable.size(); i++) {
        bool used = false;
        if (!definedBefore[i]) {

            for (int j = 0; j < allUseList.size(); j++) {
                if (symbolTable[i].first == allUseList[j]) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                int index = i;
                int pos = 0;
                for (int k = 0; k < moduleTable.size(); k++) {
                    if (index < moduleTable[k].getDefcount()) {
                        pos = k + 1;
                        break;
                    }
                    index -= moduleTable[k].getDefcount();
                }
                cout << "Warning: Module " << pos << ": " << symbolTable[i].first << " was defined but never used" << endl;
            }
        }
    }
}

#endif
