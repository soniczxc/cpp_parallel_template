#ifndef PARALLEL_EXECUTOR_EVENTQUEUE_H
#define PARALLEL_EXECUTOR_EVENTQUEUE_H
#include <iostream>
#include <memory>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "parallel_executor/Event/Event.h"

class EventQueue {
public:
    void push(const std::shared_ptr<const Event>& event);

    std::shared_ptr<const Event> pop(const std::chrono::seconds& duration);
private:
    std::queue<std::shared_ptr<const Event>> queue;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif //PARALLEL_EXECUTOR_EVENTQUEUE_H
