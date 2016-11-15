//
//  ExceptionHandler.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>
#include "ThreadState.h"

// TODO: be bothered to make getters for this
class Exception {
    friend class ExceptionHandler;

public:
    Exception(mach_port_t exception_port, mach_port_t thread, mach_port_t task,
              exception_type_t type, exception_data_t code,
              mach_msg_type_number_t code_count)
    : _exception_port(exception_port),
      _thread(thread),
      _task(task),
      _type(type),
      _code(code),
      _code_count(code_count) {}

    std::shared_ptr<ThreadState> ExceptionThreadState(mach_port_t thread);

protected:
    mach_port_t _exception_port;
    mach_port_t _thread;
    mach_port_t _task;
    exception_type_t _type;
    exception_data_t _code;
    mach_msg_type_number_t _code_count;
};

class ExceptionHandler {
public:
    ExceptionHandler(task_t task) : _task(task) {}

    bool SetupHandler();
    kern_return_t ExceptionCallback(Exception &);

private:
    task_t _task;
    std::vector<Exception> _exceptionHistory;
};
