//
//  ProcessStore.cc
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ProcessStore.h"

extern "C" int proc_listpids(uint32_t type, uint32_t typeinfo, void *buffer,
                             int buffersize);
extern "C" int proc_pidpath(int pid, void *buffer, uint32_t buffersize);
extern "C" int proc_name(int pid, void *buffer, uint32_t buffersize);

ProcessStore *ProcessStore::SharedStore() {
    static ProcessStore *store = nullptr;
    if (!store) {
        store = new ProcessStore();
    }
    return store;
}

ProcessRef ProcessStore::GetProcess(std::string name) {
    int pid = PIDFromName(name);
    if (pid < 0) return nullptr;
    return GetProcess(pid);
}

// TODO: use some sort of mutex locking here
ProcessRef ProcessStore::GetProcess(int pid) {
    auto it = std::find_if(
        _processes.begin(), _processes.end(),
        [pid](const ProcessRef &p) { return pid == p->process_id(); });
    if (it != _processes.end()) return *it;

    task_t task;
    task_for_pid(mach_task_self(), pid, &task);  // TODO: error checking

    _processes.push_back(
        std::make_shared<Process>(pid, task));  // TODO: pid, task and name
    return _processes.back();
}

ProcessRef ProcessStore::ProcessSelf() {
    return GetProcess(getpid());
}

int ProcessStore::PIDFromName(std::string name) {
    int numberOfProcesses = proc_listpids(1, 0, NULL, 0);
    size_t sz = numberOfProcesses * sizeof(pid_t);
    pid_t *pids = (pid_t *)malloc(sz);
    proc_listpids(1, 0, pids, sz);
    for (int i = 0; i < numberOfProcesses; i++) {
        char *pid_name = new char[64];
        proc_name(pids[i], pid_name, 64);
        if (name == pid_name) {
            int pid = pids[i];
            free(pids);
            return pid;
        }
    }
    free(pids);
    return -1;
}
