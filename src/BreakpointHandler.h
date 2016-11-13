//
//  BreakpointHandler.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include "Breakpoint.h"
#include "Process.h"

#define BKPT_ENABLED (1 << 0)
#define BKPT_DISABLED (1 << 1)
#define BKPT_ALL (BKPT_ENABLED | BKPT_DISABLED)

class BreakpointHandler {
public:
    BreakpointHandler() = default;
    static std::shared_ptr<BreakpointHandler> SharedHandler();

    bool InstallBreakpoint(BreakpointRef bp, bool immActive = true);
    bool UninstallBreakpoint(BreakpointRef bp);
    bool DisableBreakpoint(BreakpointRef bp);
    bool EnableBreakpoint(BreakpointRef bp);

    BreakpointRef BreakpointAtAddress(vm_address_t address);

    std::vector<BreakpointRef> Breakpoints(uint32_t flags = BKPT_ALL);

private:
    std::vector<BreakpointRef> _breakpoints;  // TODO: switch to smart pointer?
};
