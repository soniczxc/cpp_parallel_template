#include "StartedEvent.h"

std::string StartedEvent::toString() const {
    return "Started " + device->getName();
}
