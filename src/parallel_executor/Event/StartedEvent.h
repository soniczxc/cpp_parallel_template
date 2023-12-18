//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_STARTEDEVENT_H
#define PARALLEL_EXECUTOR_STARTEDEVENT_H


#include <utility>

#include "DeviceEvent.h"

class StartedEvent : public DeviceEvent {
public:
    explicit StartedEvent(const std::shared_ptr<Device>& device) : DeviceEvent(device){};
    std::string toString() const override;
};


#endif //PARALLEL_EXECUTOR_STARTEDEVENT_H
