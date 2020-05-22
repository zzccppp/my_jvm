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
        cp_info *inf;
        switch (tag) {
            case ClassFileConstants::CONSTANT_Class:
                inf = new CONSTANT_Class_info(cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Fieldref:
                inf = new CONSTANT_Fieldref_info(cfs.read_u16(), cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Methodref:
                inf = new CONSTANT_Methodref_info(cfs.read_u16(), cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_InterfaceMethodref:
                inf = new CONSTANT_InterfaceMethodref_info(cfs.read_u16(), cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_String:
                inf = new CONSTANT_String_info(cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Integer:
                inf = new CONSTANT_Integer_info(cfs.read_u32());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Float:
                inf = new CONSTANT_Float_info(cfs.read_u32());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Long:
                inf = new CONSTANT_Long_info(cfs.read_u32(), cfs.read_u32());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Double:
                inf = new CONSTANT_Double_info(cfs.read_u32(), cfs.read_u32());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_NameAndType:
                inf = new CONSTANT_NameAndType_info(cfs.read_u16(), cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_Utf8:
                //process out of switch
                break;
            case ClassFileConstants::CONSTANT_MethodHandle:
                inf = new CONSTANT_MethodHandle_info(cfs.read_u8(), cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_MethodType:
                inf = new CONSTANT_MethodType_info(cfs.read_u16());
                p[i] = inf;
                break;
            case ClassFileConstants::CONSTANT_InvokeDynamic:
                inf = new CONSTANT_InvokeDynamic_info(cfs.read_u16(), cfs.read_u16());
                p[i] = inf;
                break;
            default:
                std::cout << "Error !!";
                break;
        }
        if (tag == ClassFileConstants::CONSTANT_Utf8) {
            inf = new CONSTANT_Utf8_info(cfs.read_u16(), nullptr);
            auto *utf = static_cast<CONSTANT_Utf8_info *>(inf);
            utf->bytes = new u8[utf->length + 1];
            utf->bytes[utf->length] = 0;
            for (int j = 0; j < utf->length; ++j) {
                utf->bytes[j] = cfs.read_u8();
            }
            int x = 01;
        }
    }

    return 0;
}
