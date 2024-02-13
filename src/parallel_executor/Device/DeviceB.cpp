#include "DeviceB.h"
#include "string"
std::string DeviceB::getName() {
    return "B";
}

std::string DeviceB::getDataAsString() {
   std::string data = std::to_string(rand() % 199) + ' '+ std::to_string(rand()%199)+' '+ std::to_string(rand()%199);
   return data;
}
