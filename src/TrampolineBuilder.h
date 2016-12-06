//
//  TrampolineBuilder.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include <vector>
#include "JITRegion.h"

// class Instr;
class Process;

struct Trampoline {
    uintptr_t addr;
    uintptr_t src;
    // std::vector<Instr> instrs;
    Process *proc;

    Trampoline(uintptr_t addr, uintptr_t src, Process *proc)
    : addr(addr), src(src), proc(proc) {}

    void Install();
    void Uninstall();
};

class TrampolineBuilder {
public:
    Trampoline *CreateTrampoline(Process *proc, uintptr_t src, uintptr_t dest,
                                 size_t size);

private:
    JITRegion *_region;
};
