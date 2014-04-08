//
//  HelperFunc.h
//  2PassLinker
//
//  Created by Liang Fang on 2/11/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef _PassLinker_HelperFunc_h
#define _PassLinker_HelperFunc_h
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Token.h"
#include <stdio.h>
using namespace std;

// change integer to string form
string IntToString(int i) {
    char result[32];
    sprintf(result, "%d", i);
    return string(result);
}

// split string into tokens by space and return vector with these tokens
vector<string> split(string str) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// store tokens' offset into vector
void getTokenOffset(string str, vector<int>& offsets) {
    bool notEncounter = true;
    for (int i = 0; i < str.length(); i++) {
        if (notEncounter) {
            if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
                offsets.push_back(i + 1);       // offset starts from 1
                notEncounter = false;
            }
        } else {
            if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
                notEncounter = true;
            }
        }
        
    }
}

// determine if a token is number
bool isTokenNumber(Token t) {
    string s = t.getStr();
    for (int i = 0; i < s.length(); i++) {
        if (s.length() == 1) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        } else {
            if (i == 0 ) {
                if (s[i] < '1' || s[i] > '9')
                    return false;
            } else {
                if (s[i] < '0' || s[i] > '9')
                    return false;
            }
        }
    }
    return true;
}

// determine if a instruction is valid
bool isInstrValid(Token t) {
    string s = t.getStr();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

// change int count to "000" form
string reformInt(int i) {
    if (i < 10) {
        return "00" + IntToString(i);
    } else if (i < 100) {
        return "0" + IntToString(i);
    } else {
        return IntToString(i);
    }
}

// change instruction from integer to string
string reformInstr(int instr) {
    if (instr < 10) {
        return "000" + IntToString(instr);
    } else if (instr < 100) {
        return "00" + IntToString(instr);
    } else if (instr < 1000) {
        return "0" + IntToString(instr);
    } else {
        return IntToString(instr);
    }
}

// determine if a symbol is used but not defined in symboltable
bool usedButNotDefined(vector< pair<string, int> > symbolTable, string s) {
    vector<pair<string, int> >::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); it++) {
        if (it->first == s) {
            return false;
        }
    }
    return true;
}

// get symbol value from symboltable
int getSymbolValue(vector< pair<string, int> > symbolTable, string s) {
    vector<pair<string, int> >::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); it++) {
        if (it->first == s) {
            return it->second;
        }
    }
    return -1;
}

// parse error info
void parseerror(int errcode, int linenum, int offset) {
    static char* errstr[] = {
        "NUM_EXPECTED",
        "SYM_EXPECTED",
        "ADDR_EXPECTED",
        "SYM_TOLONG",
        "TO_MANY_DEF_IN_MODULE",
        "TO_MANY_USE_IN_MODULE",
        "TO_MANY_INSTR",
    };
    
    cout << "Parse Error line " << linenum << " offset " << offset << ": " << errstr[errcode] << endl;
}

#endif
