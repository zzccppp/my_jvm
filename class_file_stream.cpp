//
// Created by ZZDirty on 2020/5/22.
//

#include "class_file_stream.hpp"
#include "bytes_x86.hpp"

#include <utility>
#include <fstream>
#include <stdexcept>
#include <iostream>

ClassFileStream::ClassFileStream(std::string path) : path(std::move(path)) {
    std::ifstream in;
    in.open(this->path, std::ios::in | std::ios::binary);
    std::cout << this->path;
    if (!in) {
        throw std::runtime_error("open file failed");
    }
    in.seekg(0, std::ios::end);
    this->file_size = in.tellg();
    in.seekg(std::ios::beg);
    this->cur = new u8[this->file_size];
    this->buf_start = this->cur;
    this->buf_end = this->cur + this->file_size;

    in.read(reinterpret_cast<char *>(this->cur), this->file_size);
}

ClassFileStream::~ClassFileStream() {
    delete[] this->buf_start;
}

u8 ClassFileStream::read_u8() {
    if (!is_avaliable(1)) {
        u8 tmp = *cur;
        cur++;
        return tmp;
    }
    throw std::runtime_error("cannot read more");
}

u16 ClassFileStream::read_u16() {
    if (!is_avaliable(2)) {
        auto *tmp = reinterpret_cast<Unaligned *>(this->cur);
        u16 r = Bytes::swap_u16(tmp->us);
        this->cur += 2;
        return r;
    }
    throw std::runtime_error("cannot read more");
}

u32 ClassFileStream::read_u32() {
    if (!is_avaliable(4)) {
        auto *tmp = (Unaligned *) (this->cur);
        u32 r = Bytes::swap_u32(tmp->u);
        this->cur += 4;
        return r;
    }
    throw std::runtime_error("cannot read more");
}

u64 ClassFileStream::read_u64() {
    if (!is_avaliable(8)) {
        auto *tmp = reinterpret_cast<Unaligned *>(this->cur);
        u64 r = Bytes::swap_u64(tmp->ul);
        this->cur += 8;
        return r;
    }
    throw std::runtime_error("cannot read more");
}
