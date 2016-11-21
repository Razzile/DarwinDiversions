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

#define noinline __attribute__((noinline)) extern "C"

void (*old_test)(int x);

noinline void test(int);
noinline void test2();

__attribute__((naked)) void test_tramp() {
    asm("push %rbp");
    asm("movabs $_test, %rax");
    asm("add $1, %rax");
    asm("jmp *%rax");
}

noinline void test(int x) {
    printf(">>> I like the number %d\n", x);
}

noinline void test2() {
    int x = 41;
    printf(">>> I like the number %d\n", x);
    old_test(100);
}

int main(int argc, char **argv) {
    DDHookFunctionEx((void *)test, (void *)test2, (void **)&old_test,
                     DD_HOOK_EXC);
    test(1337);
}
