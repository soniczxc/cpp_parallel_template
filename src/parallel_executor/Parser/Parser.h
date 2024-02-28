#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <chrono>
#include "parallel_executor/EventQueue/EventQueue.h"
#include "parallel_executor/Device/Device.h"

class Parser {
public:
    Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B);

    void run(size_t loop_count_A, size_t loop_count_B, int crush_index_A, int crush_index_B);

private:
    void read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index, bool& deviceStopped);

    std::shared_ptr<EventQueue> queue;
    std::shared_ptr<Device> A;
    std::shared_ptr<Device> B;
};

#endif
