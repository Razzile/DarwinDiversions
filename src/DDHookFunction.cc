//
//  DarwinDiversions.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include "BreakpointFactory.h"
#include "BreakpointHandler.h"
#include "DDHookFunction.h"
#include "Process.h"

DDHookRef DDHookFunction(void *addr, void *replacement, void **original) {
    return DDHookFunctionEx(addr, replacement, original, DD_HOOK_DEFAULT);
}

DDHookRef DDHookFunctionEx(void *addr, void *replacement, void **original,
                           DDHookMethod method) {
    if (!addr || !replacement) return nullptr;

    switch (method) {
        case DD_HOOK_TRAMPOLINE: {
            // do arch specific construction of a trampoline at addr
            break;
        }

        case DD_HOOK_INTERPOSE: {
            // look up data in __LINKEDIT
            // this one is weird and may not fit in this function. come back to
            // me later
            break;
        }

        case DD_HOOK_VTABLE: {
            // as with interpose, this may belong in its own function
            break;
        }

        case DD_HOOK_EXC: {
            DDHookFunctionMethodException(addr, replacement, original);
            break;
        }
        default:
            return nullptr;
    }
    return 0;
}

bool DDHookFunctionMethodException(void *addr, void *replacement,
                                   void **original) {
    auto process = Process::Self();
    auto bpHandler = BreakpointHandler::SharedHandler();
    auto excHandler = process->exception_handler();

    auto bp = BreakpointFactory::MakeBreakpointForProcess(
        process.get(), (vm_address_t)addr, BreakpointType::Software);
    if (!bp) return false;
    bp->AddCallback([&](ThreadState &state) {
        vm_address_t addr = state.CurrentAddress();
    });

    bpHandler->InstallBreakpoint(bp);
}
