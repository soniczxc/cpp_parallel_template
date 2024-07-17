
add_executable(test_eventqueue Test_EventQueue.cpp)
target_include_directories(test_eventqueue PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_eventqueue eventQueue event device GTest::gtest_main)

add_executable(test_devices Test_Devices.cpp)
target_include_directories(test_devices PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_devices device GTest::gtest_main)

add_executable(test_events Test_Events.cpp)
target_include_directories(test_events PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_events event device GTest::gtest_main)

add_executable(test_parser Test_Parser.cpp)
target_include_directories(test_parser PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_parser parser eventQueue event device  GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_devices)
gtest_discover_tests(test_eventqueue)
gtest_discover_tests(test_events)
gtest_discover_tests(test_parser)
