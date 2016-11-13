//
//  x86_64Host.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include "Host.h"

#if defined (__i386__) || defined(__x86_64__)  // we're targeting an x86 system

class x86_64Host : public Host {
public:
    virtual int HardwareBreakpointCount();
    virtual int HardwareWatchpointCount();  // unusued in liberation
    virtual enum Platform Platform() { return Platform::x86_64; }
};


#else  // we're targeting something else (likely ARM)

#include "NOPHost.h"
using x86_64Host = NOPHost;

#endif /* _x86_64_ */
