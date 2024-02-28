#include "Parser.h"
#include "parallel_executor/Event/DeviceEvent.h"
#include "parallel_executor/Event/WorkDoneEvent.h"
#include "parallel_executor/Event/DataEvent.h"
#include <thread>
#include <iostream>

Parser::Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B) : queue(queue), A(A), B(B) {}

void Parser::run(size_t loop_count_A, size_t loop_count_B, int crush_index_A, int crush_index_B) {
    bool deviceAStopped = false;
    bool deviceBStopped = false;

    std::thread threadA(&Parser::read, this, A, std::chrono::seconds(1), loop_count_A, crush_index_A, std::ref(deviceAStopped));
    std::thread threadB(&Parser::read, this, B, std::chrono::seconds(5), loop_count_B, crush_index_B, std::ref(deviceBStopped));

    threadA.join();
    threadB.join();

    /*
    bool bothDevicesStopped = false;
    while (!bothDevicesStopped) {
        if (deviceAStopped && deviceBStopped) {
            bothDevicesStopped = true;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    */

    //if (deviceAStopped && deviceBStopped) {
        if (crush_index_A == -1 || crush_index_A >= loop_count_A) {
            queue->push(std::make_shared<WorkDoneEvent>(A));
        }
        if (crush_index_B == -1 || crush_index_B >= loop_count_B) {
            queue->push(std::make_shared<WorkDoneEvent>(B));
        }
}


void Parser::read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index, bool& deviceStopped) {
    for (size_t i = 0; i < loop_count; ++i) {
        if (crush_index != -1 && i == crush_index) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout << "Device " << device->getName() << " stopped" << std::endl;
            deviceStopped = true;
            return;
        }

        std::this_thread::sleep_for(sleep_duration);
        queue->push(std::make_shared<DataEvent>(device));
    }

    deviceStopped = true;
}

