//
//  DarwinDiversions.cc
//  DarwinDiversions
//
//  Created by callum
//  Copyright © 2016 callum. All rights reserved.
//

#include "DDHookFunction.h"


DDHookRef DDHookFunction(void *addr, void *replacement, void **original) {
  return DDHookFunctionEx(addr, replacement, original, DD_HOOK_DEFAULT);
}

DDHookRef DDHookFunctionEx(void *addr, void *replacement, void **original, DDHookMethod method) {
  if (!addr || !replacement) return nullptr;

  switch (method) {
    case DD_HOOK_TRAMPOLINE: {
      // do arch specific construction of a trampoline at addr
      break;
    }

    case DD_HOOK_INTERPOSE: {
      // look up data in __LINKEDIT
      // this one is weird and may not fit in this function. come back to me later
      break;
    }

    case DD_HOOK_VTABLE: {
      // as with interpose, this may belong in its own function
      break;
    }

    case DD_HOOK_EXC: {
      // install new bp handler at addr (use hw until no slots left, then try sw)
      // then do exception magic
      break;
    }
    default: return nullptr;
  }
}
