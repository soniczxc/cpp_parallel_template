//
// Created by osia on 05.05.23.
//

#include "WorkDoneEvent.h"

std::string WorkDoneEvent::toString() const {
    return "Finished " + device->getName();
}
