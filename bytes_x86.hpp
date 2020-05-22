//
// Created by ZZDirty on 2020/5/22.
//

#ifndef JVM_DEMO1_BYTES_X86_HPP
#define JVM_DEMO1_BYTES_X86_HPP

#include "general_def.hpp"

namespace Bytes {
    inline u16 swap_u16(u16 x) {
        u8 *p = reinterpret_cast<u8 *>(&x);
        return ((u16(p[0]) << 8) | (u16(p[1])));
    }

    inline u32 swap_u32(u32 x) {
        u8 *p = reinterpret_cast<u8 *>(&x);
        return ((u32(p[0]) << 24) | (u32(p[1]) << 16) | (u32(p[2]) << 8) | u32(p[3]));
    }

    inline u64 swap_u64(u64 x) {
        u8 *p = reinterpret_cast<u8 *>(&x);
        return ((u64(p[0]) << 56) | (u64(p[1]) << 48) | (u64(p[2]) << 40) | (u64(p[3]) << 32) |
                (u64(p[4]) << 24) | (u64(p[5]) << 16) | (u64(p[6]) << 8) | u64(p[7]));
    }
}

#endif //JVM_DEMO1_BYTES_X86_HPP
