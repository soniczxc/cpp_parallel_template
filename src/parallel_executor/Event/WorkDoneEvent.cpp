#include "WorkDoneEvent.h"

std::string WorkDoneEvent::toString() const {
    return "Finished " + device->getName();
}
