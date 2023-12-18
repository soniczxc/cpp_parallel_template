//
// Created by osia on 05.05.23.
//

#ifndef PARALLEL_EXECUTOR_WORKDONEEVENT_H
#define PARALLEL_EXECUTOR_WORKDONEEVENT_H

#include "DeviceEvent.h"


class WorkDoneEvent : public DeviceEvent {
public:
    explicit WorkDoneEvent(const std::shared_ptr<Device>& device) : DeviceEvent(device){};
    std::string toString() const override;
};


#endif //PARALLEL_EXECUTOR_WORKDONEEVENT_H
