#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ring_buffer.hpp"
#include <filesystem>
#include <cstdio>

TEST_CASE("RingBuffer basic operations") {
    const std::string filename = "test_ringbuffer.bin";
    if (std::filesystem::exists(filename))
        std::filesystem::remove(filename);

    RingBuffer ring(filename, 3);

    CHECK(ring.isEmpty());
    CHECK_FALSE(ring.isFull());

    ring.writeMessage("msg1");
    ring.writeMessage("msg2");

    CHECK_FALSE(ring.isEmpty());

    auto m1 = ring.readMessage();
    CHECK(m1 == "msg1");

    ring.writeMessage("msg3");
    ring.writeMessage("msg4");

    CHECK(ring.isFull());

    auto m2 = ring.readMessage();
    CHECK(m2 == "msg2");

    auto m3 = ring.readMessage();
    CHECK(m3 == "msg3");

    CHECK_FALSE(ring.isFull());
    CHECK_FALSE(ring.isEmpty());

    auto m4 = ring.readMessage();
    CHECK(m4 == "msg4");

    CHECK(ring.isEmpty());

    // Cleanup
    std::filesystem::remove(filename);
}
