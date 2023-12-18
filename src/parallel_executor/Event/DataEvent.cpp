#include "DataEvent.h"

std::string DataEvent::toString() const {
    return device->getDataAsString()+" from " + device->getName();
}

