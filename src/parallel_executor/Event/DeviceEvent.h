#ifndef PARALLEL_EXECUTOR_DEVICEEVENT_H
#define PARALLEL_EXECUTOR_DEVICEEVENT_H
#include <memory>
#include "Event.h"
#include "parallel_executor/Device/Device.h"


class DeviceEvent : public Event {
public:
    explicit DeviceEvent(std::shared_ptr<Device> device) : device(std::move(device)) {
    };

    std::string toString() const override;

protected:
    std::shared_ptr<Device> device;
};

#endif //PARALLEL_EXECUTOR_DEVICEEVENT_H
