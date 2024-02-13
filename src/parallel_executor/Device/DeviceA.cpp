#include "DeviceA.h"
#include <string>
#include <cstdlib>

char * generator(int len){
    char symbols[27]  = "abcdefghijklmnopqrstuvwxyz";
    char *output = new char[len];
    int random;
    int i;
    for (i = 0; i<len; i++) {
        random = rand()%(26);
        output[i] = symbols[random];
    }
    return output;
}
std::string DeviceA::getName() {
    return "A";
}

std::string DeviceA::getDataAsString() {
    return generator(rand()%501);
}
