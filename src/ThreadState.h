//
//  ThreadState.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include <mach/mach.h>
#include <string>
#include <vector>

#define STATE_ADD_REGISTER(state, reg, pointer) \
    state->_registers.emplace_back(pointer, reg)

class ThreadState {
public:
    ThreadState(mach_port_t thread) : _thread(thread) {}

    virtual ~ThreadState() = default;
    // nasty wrapper around a register from a thread state
    class Register {
    public:
        Register(void *value, std::string name) : _regVal(value), _name(name) {}

        template <typename U>
        operator U() {
            return *(U *)_regVal;
        }

        template <typename U>
        U Value() {
            return *(U *)_regVal;
        }

        template <typename U>
        Register &operator=(U val) {
            *(U *)_regVal = val;
            return *this;
        }

        std::string Name() { return _name; }

    private:
        void *_regVal;
        std::string _name;
    };

    virtual std::string Description() = 0;
    virtual bool Load() = 0;
    virtual bool Save() = 0;
    virtual vm_address_t CurrentAddress() = 0;

    ThreadState::Register operator[](std::string key) {
        // nasty way to make string uppercase
        for (auto &c : key) c = toupper(c);

        for (Register &reg : _registers) {
            if (reg.Name() == key) return reg;
        }
        // PLEASE cheaters, don't make this get called
        throw std::runtime_error("invalid register called on thread state: \n" +
                                 this->Description() + "\n");
    }

protected:
    mach_port_t _thread;
    std::vector<Register> _registers;
};

#include "AArch64/AArch64ThreadState.h"
#include "ARMv7/ARMv7ThreadState.h"
#include "x86_64/x86_64ThreadState.h"
