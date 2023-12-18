#ifndef PARALLEL_EXECUTOR_DEVICEA_H
#define PARALLEL_EXECUTOR_DEVICEA_H
#include "Device.h"

class DeviceA : public Device {
public:
    std::string getName() override;
    std::string getDataAsString() override;
};


#endif //PARALLEL_EXECUTOR_DEVICEA_H
