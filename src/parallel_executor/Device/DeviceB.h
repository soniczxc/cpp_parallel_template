//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_DEVICEB_H
#define PARALLEL_EXECUTOR_DEVICEB_H
#include "Device.h"


class DeviceB : public Device {
public:
    std::string getName() override;
    std::string getDataAsString() override;
};


#endif //PARALLEL_EXECUTOR_DEVICEB_H
