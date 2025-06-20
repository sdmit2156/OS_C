enable_testing()

add_executable(test_ring_buffer test_ring_buffer.cpp)

# Подключаем include директорию с doctest.h и src для ring_buffer.hpp
target_include_directories(test_ring_buffer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(test_ring_buffer PRIVATE ring_buffer)

add_test(NAME ring_buffer_test COMMAND test_ring_buffer)
