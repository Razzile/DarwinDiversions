//
//  BreakpointFactory.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include "Breakpoint.h"
#include "Process.h"

#include "AArch64/AArch64Breakpoint.h"
#include "ARMv7/ARMv7Breakpoint.h"
#include "NOP/NOPBreakpoint.h"
#include "x86_64/x86_64Breakpoint.h"

#define MAKE_BREAKPOINT(arch, type, proc, address) \
    std::make_shared<arch##type##Breakpoint>(proc, address)

class Breakpoint;
class Process;

enum class BreakpointType { Hardware, Software };

// TODO: merge this into BreakpointHandler
class BreakpointFactory {
public:
    static std::shared_ptr<Breakpoint> MakeBreakpointForProcess(
        Process *proc, vm_address_t address, BreakpointType type) {
        switch (proc->RunningPlatform()) {
            case Platform::AArch64: {
                if (type == BreakpointType::Hardware) {
                    return MAKE_BREAKPOINT(AArch64, Hardware, proc, address);
                } else {
                    return MAKE_BREAKPOINT(AArch64, Software, proc, address);
                }
            }

            case Platform::ARMv7: {
                if (type == BreakpointType::Hardware) {
                    return MAKE_BREAKPOINT(ARMv7, Hardware, proc, address);
                } else {
                    return MAKE_BREAKPOINT(ARMv7, Software, proc, address);
                }
            }

            case Platform::x86_64: {
                if (type == BreakpointType::Hardware) {
                    return MAKE_BREAKPOINT(x86_64, Hardware, proc, address);
                } else {
                    return MAKE_BREAKPOINT(x86_64, Software, proc, address);
                }
            }

            default: { return std::make_shared<NOPBreakpoint>(proc, address); }
        }
    }
};
