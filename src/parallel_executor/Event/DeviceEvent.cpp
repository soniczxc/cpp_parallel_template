#include "DeviceEvent.h"

std::string DeviceEvent::toString() const {
    return "Device " + device->getName() + "";
}
