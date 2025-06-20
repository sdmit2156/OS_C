#include "ring_buffer.hpp"
#include <fstream>
#include <cstring>
#include <stdexcept>

RingBuffer::RingBuffer(const std::string& file, size_t cap)
    : filename(file)
{
    if (cap > 0) {
        header = { 0, 0, 0, cap };
        std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
        if (!ofs) throw std::runtime_error("Cannot create file");
        ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

        char empty[MESSAGE_SIZE]{ 0 };
        for (size_t i = 0; i < cap; ++i) {
            ofs.write(empty, MESSAGE_SIZE);
        }
        ofs.close();
    }
    else {
        loadHeader();
    }
}

void RingBuffer::loadHeader() {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) throw std::runtime_error("Cannot open file");
    ifs.read(reinterpret_cast<char*>(&header), sizeof(header));
    ifs.close();
}

void RingBuffer::saveHeader() {
    std::fstream fs(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs) throw std::runtime_error("Cannot open file");
    fs.seekp(0);
    fs.write(reinterpret_cast<const char*>(&header), sizeof(header));
    fs.close();
}

bool RingBuffer::isFull() {
    loadHeader();
    return header.count == header.capacity;
}

bool RingBuffer::isEmpty() {
    loadHeader();
    return header.count == 0;
}

void RingBuffer::writeToFile(size_t index, const std::string& message) {
    std::fstream fs(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs) throw std::runtime_error("Cannot open file");
    size_t pos = sizeof(Header) + index * MESSAGE_SIZE;
    fs.seekp(pos);
    char buffer[MESSAGE_SIZE]{ 0 };
    std::strncpy(buffer, message.c_str(), MESSAGE_SIZE - 1);
    fs.write(buffer, MESSAGE_SIZE);
    fs.close();
}

std::string RingBuffer::readFromFile(size_t index) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) throw std::runtime_error("Cannot open file");
    size_t pos = sizeof(Header) + index * MESSAGE_SIZE;
    ifs.seekg(pos);
    char buffer[MESSAGE_SIZE]{ 0 };
    ifs.read(buffer, MESSAGE_SIZE);
    ifs.close();
    return std::string(buffer);
}

void RingBuffer::writeMessage(const std::string& message) {
    std::lock_guard lock(mtx);
    loadHeader();
    if (header.count == header.capacity) {
        throw std::runtime_error("Buffer full");
    }
    writeToFile(header.tail, message);
    header.tail = (header.tail + 1) % header.capacity;
    ++header.count;
    saveHeader();
}

std::string RingBuffer::readMessage() {
    std::lock_guard lock(mtx);
    loadHeader();
    if (header.count == 0) {
        throw std::runtime_error("Buffer empty");
    }
    std::string msg = readFromFile(header.head);
    header.head = (header.head + 1) % header.capacity;
    --header.count;
    saveHeader();
    return msg;
}
