//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_DATAEVENT_H
#define PARALLEL_EXECUTOR_DATAEVENT_H
#include "DeviceEvent.h"

class DataEvent : public DeviceEvent{
public:
    explicit DataEvent(const std::shared_ptr<Device>& device) : DeviceEvent(device) {};
    std::string toString() const override;
};

#endif //PARALLEL_EXECUTOR_DATAEVENT_H
