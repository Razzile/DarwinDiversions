//
//  Breakpoint.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include <mach/mach.h>
#include <functional>
#include <vector>

class Process;
class ThreadState;

using BreakpointCallback = std::function<void(ThreadState &)>;

class Breakpoint {
public:
    Breakpoint(Process *proc, vm_address_t address)
    : _address(address), _proc(proc) {}
    virtual ~Breakpoint() {}

    virtual bool Apply() = 0;
    virtual bool Reset() = 0;

    virtual bool active() { return this->_active; }
    virtual vm_address_t address() { return this->_address; }
    virtual BreakpointCallback callback() { return this->_callback; }

    virtual void AddCallback(BreakpointCallback cb) { _callback = cb; }

protected:
    bool _active;
    vm_address_t _address;
    Process *_proc;
    BreakpointCallback _callback;
};

using BreakpointRef = std::shared_ptr<Breakpoint>;
