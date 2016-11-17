//
//  test.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//
#include <stdio.h>
#include "../src/DDHookFunction.h"
#include "../src/ProcessStore.h"

#define noinline __attribute__((noinline))

noinline void test2() {
    int x = 41;
    printf("%d\n", x);
}

noinline void test(int x) {
    printf("%d\n", x);
}

int main(int argc, char **argv) {
    ProcessRef self = ProcessStore::SharedStore()->ProcessSelf();
    if (self) {
        printf("process has pid %d and task %d\n", self->process_id(),
               self->task());
    } else {
        printf("boo you\n");
    }
    DDHookFunctionEx((void *)test, (void *)test2, nullptr, DD_HOOK_EXC);
    test(1337);
}
