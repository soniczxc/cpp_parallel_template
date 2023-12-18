//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_DEVICE_H
#define PARALLEL_EXECUTOR_DEVICE_H
#include <iostream>
#include <thread>

class Device {
public:
    virtual std::string getName() = 0;
    virtual std::string getDataAsString() = 0;
    virtual ~Device() = default;
};

#endif //PARALLEL_EXECUTOR_DEVICE_H
