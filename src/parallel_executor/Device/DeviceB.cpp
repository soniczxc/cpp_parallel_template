#include "DeviceB.h"

std::string DeviceB::getName() {
    return "B";
}

std::string DeviceB::getDataAsString() {
    std::string data{"198 0 100"};
    return data;
}