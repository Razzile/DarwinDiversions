//
//  NOPBreakpoint.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include "Breakpoint.h"

class NOPBreakpoint : public Breakpoint {
public:
    NOPBreakpoint(Process *proc, vm_address_t addr) : Breakpoint(proc, addr) {}
    virtual bool Apply() {
        throw std::runtime_error("NOP implementation called");
    };

    virtual bool Reset() {
        throw std::runtime_error("NOP implementation called");
    };
};
