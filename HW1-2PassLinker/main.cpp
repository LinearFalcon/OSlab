//
//  main.cpp
//  2PassLinker
//
//  Created by Liang Fang on 2/11/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#include "Parser.h"

int main(int argc, char * argv[])
{
    char* inputPath = argv[1];      //take input from stdin

    parser_pass1(inputPath);        
    print_symboltable();
    parser_pass2(inputPath);
    check_symbol_usage();

    return 0;
}

