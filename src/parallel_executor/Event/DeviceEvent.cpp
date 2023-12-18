//
// Created by osia on 05.05.23.
//

#include "DeviceEvent.h"

std::string DeviceEvent::toString() const {
    return "Device " + device->getName() + "";
}
