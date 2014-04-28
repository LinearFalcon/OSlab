//
//  IORquest.h
//  IOSched
//
//  Created by Liang Fang on 4/24/14.
//  Copyright (c) 2014 Liang Fang. All rights reserved.
//

#ifndef IOSched_IORquest_h
#define IOSched_IORquest_h

class IORequest {
public:
    int index;          // index of one IO request, same as index of this IO request in the IO_queue
    int arrivalTime;
    int track;
    
    IORequest(int index, int arrivalTime, int track);
    
};

IORequest::IORequest(int index, int arrivalTime, int track) {   // index will be 0 to numOfRequest - 1
    this->index = index;
    this->arrivalTime = arrivalTime;
    this->track = track;
}

#endif
