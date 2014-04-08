//
//  IO.h
//  Scheduler
//
//  Created by Liang Fang on 3/8/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef Scheduler_IO_h
#define Scheduler_IO_h

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Variable.h"
#include "Process.h"
using namespace std;

// split string into tokens by space and return vector with these tokens
vector<string> splitString(string str) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

/*
 * Process arguments of input
 * Only assume input will have 3 arguments: scheduler, inputfile, randomfile, ignoring -v
 */
void processInput(int argc, char** argv) {

    char schedulerInfo[1000];
    int c;
    while ((c = getopt(argc, argv, "vs:")) != -1) {
        switch (c) {
        case 's':
            strcpy(schedulerInfo, optarg);
            break;
        case 'v':
            break;
        case '?':
            return;
        default:
            abort ();
        }
    }
    
    inputPath = argv[optind];
    randPath = argv[optind + 1];
    
    /* check which kind of scheduler is used **/
    if (schedulerInfo[0] == 'F') {  // FCFS
        schedulerType = FCFS;
    } else if (schedulerInfo[0] == 'L') {   // LCFS
        schedulerType = LCFS;
    } else if (schedulerInfo[0] == 'S') {   // SJF
        schedulerType = SJF;
    } else if (schedulerInfo[0] == 'R') {   // RoundRobin
        schedulerType = RR;
        int length = (unsigned)strlen(schedulerInfo);  //cout << length << endl;
        for (int i = 1; i < length; i++) {
            quantum += (schedulerInfo[i] - '0') * pow(10, length - i - 1);
        }
    }
    
    ifstream infile;
    
    /* generate randvals array from randPath file **/
    infile.open(randPath);
    if (infile.is_open()) {
        getline(infile, str);   // first line is count of random number
        numOfRandom = atoi(str.c_str());            // remember number of random num
        randvals = new int[atoi(str.c_str())];
        int count = 0;
        while (getline(infile, str)) {
            randvals[count] = atoi(str.c_str());
            count++;
        }
    }
    infile.close();
    
    
    /* generate vector inputStrings from inputPath file **/
    infile.open(inputPath);
    if (infile.is_open()) {
        int index = 0;
        while (getline(infile, str)) {                  // create Process object using each line
            vector<string> tokens = splitString(str);
            vector<int> paras;
            for (int i = 0; i < tokens.size(); i++) {
                paras.push_back(atoi(tokens[i].c_str()));
            }
            Process process(index, paras[0], paras[1], paras[2], paras[3]);
            allProcess.push(process);
            index++;
        }
    }
    infile.close();
}


#endif
