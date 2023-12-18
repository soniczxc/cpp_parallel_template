//
// Created by osia on 05.05.23.
//

#include "DataEvent.h"

std::string DataEvent::toString() const {
    return device->getDataAsString()+" from " + device->getName();
}

