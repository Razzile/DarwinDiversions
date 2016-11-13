//
//  DDHookFunction.h
//  DarwinDiversions
//
//  Created by callum
//  Copyright © 2016 callum. All rights reserved.
//

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#define API_CALL extern "C"
#else
#define API_CALL
#endif

typedef enum {
  DD_HOOK_TRAMPOLINE,
  DD_HOOK_INTERPOSE,
  DD_HOOK_VTABLE,
  DD_HOOK_EXC,
  DD_HOOK_DEFAULT = DD_HOOK_TRAMPOLINE
} DDHookMethod;

typedef struct _DDHook {
  uintptr_t address;
  uintptr_t replacement;
  uintptr_t old;
  DDHookMethod method;
  bool active;
} * DDHookRef;

API_CALL DDHookRef DDHookFunction(void *addr, void *replacement, void **original);
API_CALL DDHookRef DDHookFunctionEx(void *addr, void *replacement, void **original, DDHookMethod method);

API_CALL void DDUnhook(DDHookRef ref);
