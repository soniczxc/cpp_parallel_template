#include "parallel_executor/Device/DeviceA.h"
#include "parallel_executor/Device/DeviceB.h"

#include <gtest/gtest.h>

TEST(DeviceA, GetNameTest)
{
  DeviceA device;
  ASSERT_EQ(device.getName(), "A");
}

TEST(DeviceA, GetDataTest)
{
  size_t length = 500;
  DeviceA device;
  for (size_t i = 0; i < 10000; ++i)
  {
    std::string data = device.getDataAsString();
    ASSERT_TRUE(data.size() <= length) << "Data size: " << data.size();
  }
}

TEST(DeviceB, GetNameTest)
{
  DeviceB device;
  ASSERT_EQ(device.getName(), "B");
}

TEST(DeviceB, GetDataTest)
{
  DeviceB device;
  for (size_t i = 0; i < 10000; ++i)
  {
    int number;
    int count = 0;
    std::string data = device.getDataAsString();
    std::istringstream iss(data);
    while (iss >> number)
      count += 1;
    ASSERT_EQ(count, 3) << "Data: " << data;
  }
}
