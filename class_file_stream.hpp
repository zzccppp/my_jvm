//
// Created by ZZDirty on 2020/5/22.
//

#ifndef JVM_DEMO1_CLASS_FILE_STREAM_HPP
#define JVM_DEMO1_CLASS_FILE_STREAM_HPP


#include "general_def.hpp"
#include <string>

typedef union Unaligned {
    u32 u;
    u16 us;
    u64 ul;
} __attribute__((packed)) Unaligned;

class ClassFileStream {
private:
    u8 *buf_start;
    u8 *buf_end;
    u8 *cur;
    std::string path;
    size_t file_size; //in u8 count
public:
    explicit ClassFileStream(std::string path);

    virtual ~ClassFileStream();

    u8 *buffer() { return buf_start; }

    size_t length() { return file_size; }

    bool is_avaliable(size_t expect_bytes) {
        return (buf_end - cur) < expect_bytes;
    }

    u8 read_u8();

    u16 read_u16();

    u32 read_u32();

    u64 read_u64();

};


#endif //JVM_DEMO1_CLASS_FILE_STREAM_HPP
