//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_EVENT_H
#define PARALLEL_EXECUTOR_EVENT_H

#include <iostream>

class Event {
public:
    virtual std::string toString() const = 0;
    virtual ~Event() = default;
};


#endif //PARALLEL_EXECUTOR_EVENT_H
