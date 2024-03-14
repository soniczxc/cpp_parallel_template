#include "Parser.h"
#include "parallel_executor/Event/StartedEvent.h"
#include "parallel_executor/Event/WorkDoneEvent.h"
#include "parallel_executor/Event/DataEvent.h"
#include <thread>
#include <chrono>
#include <iostream>

Parser::Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B)
        : queue(queue), A(A), B(B) {
    if (!queue || !A || !B) {
        throw std::runtime_error("Can't be nullptr!");
    }
}

void Parser::QueueOut() {
    while (true) {

        std::shared_ptr<const Event> event;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            event = queue->pop(std::chrono::seconds(1));
        }

        if (!event) {
            auto start = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            auto end = std::chrono::steady_clock::now();
            auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            std::cout<< time.count()<< 'proshlo' << std::endl;
            if ((time.count() == 5)&&(!event)){
                std::cout<< "Device stopped" <<std::endl;
                break;
            }


        }
        std::cout << event->toString() << std::endl << std::flush;
    }
}

void Parser::read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index) {
    queue->push(std::make_shared<StartedEvent>(device));
    for (size_t i = 0; i < loop_count; ++i) {
        std::this_thread::sleep_for(sleep_duration);
        queue->push(std::make_shared<DataEvent>(device));
        if (i == crush_index - 1) {
            std::cout << "Device " << device->getName() << " stopped." << std::endl << std::flush;
            break;
        }
    }
    if (loop_count < crush_index) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        queue->push(std::make_shared<WorkDoneEvent>(device));
    }
}

void Parser::run(size_t loop_count_A, size_t loop_count_B, int crush_index_A, int crush_index_B) {
    std::thread threadQueueOut(&Parser::QueueOut, this);
    std::thread threadA(&Parser::read, this, A, std::chrono::seconds(1), loop_count_A, crush_index_A);
    std::thread threadB(&Parser::read, this, B, std::chrono::seconds(5), loop_count_B, crush_index_B);
    threadA.join();
    threadB.join();

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        queue->push(nullptr);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    threadQueueOut.join();
}
