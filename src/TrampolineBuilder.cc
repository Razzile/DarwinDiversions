//
//  TrampolineBuilder.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include "Process.h"
#include "TrampolineBuilder.h"

void Trampoline::Install() {}

void Trampoline::Uninstall() {}

//---

Trampoline *TrampolineBuilder::CreateTrampoline(Process *proc, uintptr_t src,
                                                uintptr_t dest, size_t size) {
    _region = JITRegion::CreateRegion(1024 * 10 * 4);
    if (!proc || !src || !dest || !size | !_region) return nullptr;

    // test code pls remove
    {
        unsigned char data[] = {0x41, 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                                0xA0, 0x25, 0x00, 0x00, 0x01, 0x00};
        printf("%p\n", data);
        *(uintptr_t *)(data + 6) = src;

        proc->ReadMemory(src, (char *)data, 1);

        memcpy(_region->base(), data, sizeof(data));

        Trampoline *tramp =
            new Trampoline((uintptr_t)_region->base(), src, proc);
        return tramp;
    }
}
