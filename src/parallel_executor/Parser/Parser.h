#ifndef PARSER_H
#define PARSER_H

#include "parallel_executor/EventQueue/EventQueue.h"
#include "parallel_executor/Device/Device.h"
#include "stdexcept"
#include <mutex>

class Parser {
public:
    Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B);
    void QueueOut();
    void run(size_t loop_count_A = 1, size_t loop_count_B = 1, int crush_index_A = -1, int crush_index_B = -1);

private:
    void read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index);

private:
    std::shared_ptr<EventQueue> queue;
    std::shared_ptr<Device> A;
    std::shared_ptr<Device> B;
    std::mutex queueMutex;
};

#endif


