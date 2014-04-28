//
//  HelperFunc.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_HelperFunc_h
#define IOSched_HelperFunc_h

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstring>

#include "UniversalVar.h"

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

void read(int argc, char** argv) {
    char schedulerInfo[1000];
    int c;
    while ((c = getopt(argc, argv, "s:")) != -1) {
        switch (c) {
            case 's':
                strcpy(schedulerInfo, optarg);
                break;
            case '?':
                return;
            default:
                abort();
        }
    }
    char* inputPath;
    inputPath = argv[optind];
    
    /* check which kind of scheduler is used **/
    if (schedulerInfo[0] == 'i') {  // FIFO
        scheduleType = type_FIFO;
    } else if (schedulerInfo[0] == 'j') {   // SSTF
        scheduleType = type_SSTF;
    } else if (schedulerInfo[0] == 's') {   // SCAN
        scheduleType = type_SCAN;
    } else if (schedulerInfo[0] == 'c') {   // CSCAN
        scheduleType = type_CSCAN;
    } else if (schedulerInfo[0] == 'f') {   // FSCAN
        scheduleType = TYPE_FSCAN;
    }
    
    /* generate IO_queue from inputPath file **/
    ifstream infile;
    infile.open(inputPath);
    if (infile.is_open()) {
        int index = 0;
        while (getline(infile, str)) {
            vector<string> tokens = splitString(str);
            if ((tokens[0])[0] != '#') {                // ignore comment
                int arriveT = atoi(tokens[0].c_str());
                int trackNum = atoi(tokens[1].c_str());
                IORequest temp(index, arriveT, trackNum);
                IO_queue.push_back(temp);

                numOfRequest++;                         // count number of IO requests
                index++;
            }
        }
    }
    infile.close();
}



#endif
