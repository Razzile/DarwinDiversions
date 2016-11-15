//
//  ProcessStore.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include "Process.h"

class ProcessStore {
public:
    static ProcessStore *SharedStore();

    ProcessRef GetProcess(std::string name);
    ProcessRef GetProcess(int pid);
    ProcessRef ProcessSelf();

    ProcessRef operator[](int pid) { return GetProcess(pid); }
    ProcessRef operator[](std::string name) { return GetProcess(name); }

private:
    int PIDFromName(std::string name);
    std::vector<ProcessRef> _processes;
};
