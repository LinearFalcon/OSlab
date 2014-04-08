//
//  Token.h
//  2PassLinker
//
//  Created by Liang Fang on 2/14/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef _PassLinker_Token_h
#define _PassLinker_Token_h
#include <iostream>
using namespace std;

class Token {
    int linenum;
    int offset;
    string str;
    
public:
    Token() {
        linenum = 0;
        offset = 0;
        str = "";
    }
    
    Token(int l, int o, string s) {
        linenum = l;
        offset = o;
        str = s;
    }
    
    int getLinenum() {
        return linenum;
    }
    
    int getOffset() {
        return offset;
    }
    
    string getStr() {
        return str;
    }
    
};

#endif
