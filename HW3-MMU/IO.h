//
//  IO.h
//  MMU
//
//  Created by Liang Fang on 4/5/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef MMU_IO_h
#define MMU_IO_h

#include "UniversalVar.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "PageReplace.h"
#include "NRU.h"
#include "LRU.h"
#include "Random.h"
#include "FIFO.h"
#include "SecondChance.h"
#include "Clock.h"
#include "Aging.h"


// process command line and store info
void processCommand(int argc, char** argv) {
    
    char algotype[1000];
    char options[1000];
    char frame[1000];
    bool hasFrameNum = false;   // true if has -f option
    bool hasOptions = false;    // true if has -o options
    int c;
    while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
        switch (c) {
            case 'a':
                strcpy(algotype, optarg);
                break;
            case 'o':
                hasOptions = true;
                strcpy(options, optarg);
                break;
            case 'f':
                hasFrameNum = true;
                strcpy(frame, optarg);
                break;
            case '?':
                return;
            default:
                abort ();
        }
    }
    
    inputPath = argv[optind];
    randPath = argv[optind + 1];

    // process algotype option
    if (algotype[0] == 'N') {
        algoType = type_NRU;
    } else if (algotype[0] == 'l') {
        algoType = type_LRU;
    } else if (algotype[0] == 'r') {
        algoType = type_Random;
    } else if (algotype[0] == 'f') {
        algoType = type_FIFO;
    } else if (algotype[0] == 's') {
        algoType = type_SecondChance;
    } else if (algotype[0] == 'c') {
        algoType = type_PhysicalClock;
    } else if (algotype[0] == 'C') {
        algoType = type_VirtualClock;
    } else if (algotype[0] == 'a') {
        algoType = type_PhysicalAging;
    } else if (algotype[0] == 'A') {
        algoType = type_VirtualAging;
    }
    
    // process frame number option
    if (hasFrameNum) {
        num_frames = atoi(frame);
    }
    
    // process output options
    if (hasOptions) {
        int length = (unsigned)strlen(options);
        for (int i = 0; i < length; i++) {
            if (options[i] == 'O') {
                option_O = true;
            } else if (options[i] == 'P') {
                option_P = true;
            } else if (options[i] == 'F') {
                option_F = true;
            } else if (options[i] == 'S') {
                option_S = true;
            } else if (options[i] == 'p') {
                option_p = true;
            } else if (options[i] == 'f') {
                option_f = true;
            }
        }
    }
    
    
    
    
    /* generate randvals array from randPath file **/
    ifstream infile;
    infile.open(randPath);
    if (infile.is_open()) {
        getline(infile, str);   // first line is count of random number
        numOfRandom = atoi(str.c_str());            // remember number of random num
        randvals = new int[numOfRandom];
        int count = 0;
        while (getline(infile, str)) {
            randvals[count] = atoi(str.c_str());
            count++;
        }
    }
    infile.close();

    
}


void initializePageTableAndFrameTable() {
    // initialize virtual page table
    for (int i = 0; i < 64; i++) {
        page_table[i].PRESENT = 0;
        page_table[i].MODIFIED = 0;
        page_table[i].REFERENCE = 0;
        page_table[i].PAGEDOUT = 0;
        page_table[i].INDEX = 0;
    }
    
    // initialize physical frame table
    frame_table = new frame[num_frames];    
}

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

#endif
