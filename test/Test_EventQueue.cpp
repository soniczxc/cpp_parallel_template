#include "parallel_executor/EventQueue/EventQueue.h"

#include "parallel_executor/Event/StartedEvent.h"
#include "parallel_executor/Event/DataEvent.h"
#include "parallel_executor/Event/WorkDoneEvent.h"

#include "parallel_executor/Device/DeviceA.h"
#include "parallel_executor/Device/DeviceB.h"

#include <gtest/gtest.h>

#include <thread>

TEST(EventQueue, OnePushPopTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();

  std::shared_ptr<Device> device = std::make_shared<DeviceA>();
  queue->push(std::move(std::make_shared<StartedEvent>(device)));

  std::shared_ptr<const Event> event = queue->pop(std::chrono::seconds(0));

  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const StartedEvent *>(event.get()), nullptr);
}

TEST(EventQueue, SomePushPopTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();

  size_t loop = 5;
  std::shared_ptr<Device> device = std::make_shared<DeviceA>();
  for (size_t i = 0; i < loop; ++i)
    queue->push(std::move(std::make_shared<StartedEvent>(device)));

  for (size_t i = 0; i < loop; ++i)
  {
    std::shared_ptr<const Event> event = queue->pop(std::chrono::seconds(5));
    ASSERT_NE(event, nullptr);
    ASSERT_NE(dynamic_cast<const StartedEvent *>(event.get()), nullptr);
  }
}

TEST(EventQueue, PushPopOrderTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();

  std::shared_ptr<Device> device = std::make_shared<DeviceA>();

  queue->push(std::move(std::make_shared<StartedEvent>(device)));
  queue->push(std::move(std::make_shared<DataEvent>(device)));
  queue->push(std::move(std::make_shared<WorkDoneEvent>(device)));
  queue->push(std::move(std::make_shared<DataEvent>(device)));
  queue->push(std::move(std::make_shared<StartedEvent>(device)));

  std::shared_ptr<const Event> event = queue->pop(std::chrono::seconds(0));
  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const StartedEvent *>(event.get()), nullptr);

  event = queue->pop(std::chrono::seconds(0));
  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const DataEvent *>(event.get()), nullptr);

  event = queue->pop(std::chrono::seconds(0));
  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const WorkDoneEvent *>(event.get()), nullptr);

  event = queue->pop(std::chrono::seconds(0));
  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const DataEvent *>(event.get()), nullptr);

  event = queue->pop(std::chrono::seconds(0));
  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const StartedEvent *>(event.get()), nullptr);
}

TEST(EventQueue, EmptyQueueTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  auto event = queue->pop(std::chrono::seconds(0));
  ASSERT_EQ(event, nullptr);
}

TEST(EventQueue, TimeoutTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> device = std::make_shared<DeviceA>();
  std::shared_ptr<const Event> event = nullptr;

  std::thread thread = std::thread([&queue, &event]()
                                   { event = queue->pop(std::chrono::seconds(5)); });

  queue->push(std::move(std::make_shared<StartedEvent>(device)));
  if (thread.joinable())
    thread.join();

  ASSERT_NE(event, nullptr);
  ASSERT_NE(dynamic_cast<const StartedEvent *>(event.get()), nullptr);
}

TEST(EventQueue, ThreadSafeTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();

  size_t loop = 100;
  std::function<void(std::shared_ptr<EventQueue>, std::shared_ptr<Device>)> f = [loop](std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> device)
  {
    for (size_t i = 0; i < loop; ++i)
      if (i % 2 == 0)
        queue->push(std::move(std::make_shared<StartedEvent>(device)));
      else
        queue->push(std::move(std::make_shared<WorkDoneEvent>(device)));
  };

  size_t count = 10;
  std::vector<std::thread> threads;
  for (size_t i = 0; i < count; ++i)
    threads.emplace_back(f, queue, std::move(std::make_shared<DeviceA>()));

  for (auto &t : threads)
    if (t.joinable())
      t.join();

  size_t num_started_events = 0;
  size_t num_work_done_events = 0;
  std::shared_ptr<const Event> e;
  while ((e = queue->pop(std::chrono::seconds(1))) != nullptr)
    if (dynamic_cast<const StartedEvent *>(e.get()))
      num_started_events += 1;
    else if (dynamic_cast<const WorkDoneEvent *>(e.get()))
      num_work_done_events += 1;

  ASSERT_EQ(num_started_events, num_work_done_events);
  ASSERT_EQ(
      num_started_events + num_work_done_events,
      count * loop);
}
