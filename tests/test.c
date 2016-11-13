//
//  test.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//
#include <stdio.h>
#include "../src/DDHookFunction.h"

void test() {
    printf("1\n");
}

void test2() {
    printf("2\n");
}

int main(int argc, char **argv) {
    DDHookFunctionEx(test, test2, 0, DD_HOOK_EXC);
}
