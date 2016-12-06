//
//  DarwinDiversions.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include <thread>
#include "BreakpointFactory.h"
#include "BreakpointHandler.h"
#include "DDHookFunction.h"
#include "ProcessStore.h"
#include "TrampolineBuilder.h"

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

extern void test_tramp();

bool DDHookFunctionMethodException(void *addr, void *replacement,
                                   void **original) {
    // must install breakpoint in a new thread
    auto store = ProcessStore::SharedStore();
    auto process = store->ProcessSelf();
    auto bpHandler = BreakpointHandler::SharedHandler();
    auto excHandler = process->exception_handler();
    std::thread([&]() {
        printf("hooking %p\n", addr);

        TrampolineBuilder builder;
        Trampoline *tramp = builder.CreateTrampoline(
            process.get(), (uintptr_t)addr, (uintptr_t)replacement, 1);
        *(uintptr_t *)original = tramp->addr;

        delete tramp;

        excHandler.SetupHandler();
        auto bp = BreakpointFactory::MakeBreakpointForProcess(
            process.get(), (vm_address_t)addr, BreakpointType::Hardware);
        if (!bp) return false;
        bp->AddCallback([&](ThreadState &state) {
            vm_address_t addr = state.CurrentAddress();
            vm_address_t stack = state["RSP"];
            stack -= 8;
            *(uint64_t *)stack = addr;
            state["RIP"] = (vm_address_t)replacement;
        });

        bpHandler->InstallBreakpoint(bp);
    }).join();

    return true;
}
