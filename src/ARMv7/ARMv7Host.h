//
//  ARMv7Host.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include "Host.h"

#if defined (__arm__) || defined (__arm64__)

class ARMv7Host : public Host {
public:
    virtual int HardwareBreakpointCount();
    virtual int HardwareWatchpointCount();  // unusued in liberation
    virtual enum Platform Platform() { return Platform::ARMv7; }
};

#else

#include "NOPHost.h"
using ARMv7Host = NOPHost;

#endif
