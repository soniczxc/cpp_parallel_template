#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <atomic>
#include "Device/DeviceA.h"
#include "Device/DeviceB.h"
#include "EventQueue/EventQueue.h"
#include "Parser.h"

void printEvents(std::shared_ptr<EventQueue> eventQueue, std::atomic<bool>& running, std::mutex& mutex, std::condition_variable& cv) {
    while (running) {
        std::shared_ptr<const Event> event = eventQueue->pop(std::chrono::seconds(0));
        if (event != nullptr) {
            std::cout << event->toString() << std::endl;
        }
    }
}

int main(/*int argc, char *argv[] */) {
    std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
    std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

    std::shared_ptr<EventQueue> eventQueue = std::make_shared<EventQueue>();

    Parser parser(eventQueue, deviceA, deviceB);

    std::atomic<bool> parserRunning(true);

    /*int loop_countA = int(argv[1]);
    int loop_countB = int(argv[2]);
    int crushA = int(argv[3]);
    int crushB = int(argv[4]);*/
    std::thread parserThread([&]() {
        //parser.run(loop_countA, loop_countB, crushA, crushB);
        parser.run(5,2,-1,-1);
        parserRunning = false;
    });

    std::mutex mutex;
    std::condition_variable cv;
    std::thread printThread(printEvents, eventQueue, std::ref(parserRunning), std::ref(mutex), std::ref(cv));
    printThread.detach();

    parserThread.join();

    return 0;
}
