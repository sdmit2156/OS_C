add_library(ring_buffer ring_buffer.cpp)
target_include_directories(ring_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(receiver receiver.cpp)
target_link_libraries(receiver ring_buffer)

add_executable(sender sender.cpp)
target_link_libraries(sender ring_buffer)
