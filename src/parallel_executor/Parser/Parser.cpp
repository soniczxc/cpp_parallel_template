#include "Parser.h"
#include "parallel_executor/Event/StartedEvent.h"
#include "parallel_executor/Event/WorkDoneEvent.h"
#include "parallel_executor/Event/DataEvent.h"
#include <thread>
#include <chrono>
Parser::Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B)
        : queue(queue), A(A), B(B) {
    if (!queue || !A || !B){
        throw std::runtime_error("Can't be nullptr!");
    }
}

void Parser::read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index) {
    queue->push(std::make_shared<StartedEvent>(device)); // Помещаем событие StartedEvent в очередь

    for (size_t i = 0; i < loop_count; ++i) {
        std::shared_ptr<const Event> event = queue->pop(std::chrono::seconds(0)); // Извлекаем сообщение из очереди
        if (event != nullptr) {
            std::cout << event->toString() << std::endl << std::flush;
        }

        if (i == crush_index) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue->push(std::make_shared<WorkDoneEvent>(device));
            break;
        }

        std::this_thread::sleep_for(sleep_duration);
        auto data = device->getDataAsString();
        queue->push(std::make_shared<DataEvent>(device)); // Помещаем событие DataEvent в очередь
    }

    if (crush_index == -1) {
        queue->push(std::make_shared<WorkDoneEvent>(device));
    }
}




void Parser::run(size_t loop_count_A, size_t loop_count_B, int crush_index_A, int crush_index_B) {
    std::thread threadA(&Parser::read, this, A, std::chrono::seconds(1), loop_count_A, crush_index_A);
    std::thread threadB(&Parser::read, this, B, std::chrono::seconds(5), loop_count_B, crush_index_B);
    threadA.join();
    threadB.join();
}
