#include <iostream>
#include <fstream>
#include <string>
#include "class_file.hpp"
#include "class_file_stream.hpp"

int main() {

    ClassFileStream cfs("../java_test/HelloWorld.class");
    ClassFile cf{};

    cf.magic = cfs.read_u32();
    cf.minor_version = cfs.read_u16();
    cf.major_version = cfs.read_u16();
    cf.constant_pool_count = cfs.read_u16();

    auto **p = new cp_info *[cf.constant_pool_count];

    for (int i = 1; i <= cf.constant_pool_count; ++i) {
        u8 tag = cfs.read_u8();
        switch (tag) {
            case ClassFileConstants::CONSTANT_Class:

                break;
            case ClassFileConstants::CONSTANT_Fieldref:
                break;
            case ClassFileConstants::CONSTANT_Methodref:
                break;
            case ClassFileConstants::CONSTANT_InterfaceMethodref:
                break;
            case ClassFileConstants::CONSTANT_String:
                break;
            case ClassFileConstants::CONSTANT_Integer:
                break;
            case ClassFileConstants::CONSTANT_Float:
                break;
            case ClassFileConstants::CONSTANT_Long:
                break;
            case ClassFileConstants::CONSTANT_Double:
                break;
            case ClassFileConstants::CONSTANT_NameAndType:
                break;
            case ClassFileConstants::CONSTANT_Utf8:
                break;
            case ClassFileConstants::CONSTANT_MethodHandle:
                break;
            case ClassFileConstants::CONSTANT_MethodType:
                break;
            case ClassFileConstants::CONSTANT_InvokeDynamic:
                break;
            default:
                std::cout << "Error !!";
                break;
        }
    }

    return 0;
}
