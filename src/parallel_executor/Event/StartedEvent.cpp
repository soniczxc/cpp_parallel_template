//
// Created by osia on 05.05.23.
//

#include "StartedEvent.h"

std::string StartedEvent::toString() const {
    return "Started " + device->getName();
}
