#include <functional>
#include <sstream>
#include "DeviceA.h"
#include "DeviceB.h"
#include "DataEvent.h"
#include "EventQueue.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
    std::shared_ptr<Device> A = std::make_shared<DeviceA>();
    std::shared_ptr<Device> B = std::make_shared<DeviceB>();

    Parser parser(queue, A, B);

    parser.run(10,2, -1, -1);
    return 0;
}
