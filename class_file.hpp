//
// Created by ZZDirty on 2020/5/21.
//

#ifndef JVM_DEMO1_CLASS_FILE_HPP
#define JVM_DEMO1_CLASS_FILE_HPP

#include "general_def.hpp"

namespace ClassFileConstants {
    //--------- access_flags definitions ---------
    constexpr u16 ACC_PUBLIC = 0x0001;
    constexpr u16 ACC_PRIVATE = 0x0002;
    constexpr u16 ACC_PROTECTED = 0x0004;
    constexpr u16 ACC_STATIC = 0x0008;
    constexpr u16 ACC_FINAL = 0x0010;
    constexpr u16 ACC_SYNCHRONIZED = 0x0020;
    constexpr u16 ACC_SUPER = 0x0020;
    constexpr u16 ACC_VOLATILE = 0x0040;
    constexpr u16 ACC_BRIDGE = 0x0040;
    constexpr u16 ACC_TRANSIENT = 0x0080;
    constexpr u16 ACC_VARARGS = 0x0080;
    constexpr u16 ACC_NATIVE = 0x0100;
    constexpr u16 ACC_INTERFACE = 0x0200;
    constexpr u16 ACC_ABSTRACT = 0x0400;
    constexpr u16 ACC_STRICT = 0x0800; //strictfp; floating-point mode is FP-strict
    constexpr u16 ACC_SYNTHETIC = 0x1000;
    constexpr u16 ACC_ANNOTATION = 0x2000;
    constexpr u16 ACC_ENUM = 0x4000;
    //-------- constant pool tag types -------
    constexpr u8 CONSTANT_Class = 7;
    constexpr u8 CONSTANT_Fieldref = 9;
    constexpr u8 CONSTANT_Methodref = 10;
    constexpr u8 CONSTANT_InterfaceMethodref = 11;
    constexpr u8 CONSTANT_String = 8;
    constexpr u8 CONSTANT_Integer = 3;
    constexpr u8 CONSTANT_Float = 4;
    constexpr u8 CONSTANT_Long = 5;
    constexpr u8 CONSTANT_Double = 6;
    constexpr u8 CONSTANT_NameAndType = 12;
    constexpr u8 CONSTANT_Utf8 = 1;
    constexpr u8 CONSTANT_MethodHandle = 15;
    constexpr u8 CONSTANT_MethodType = 16;
    constexpr u8 CONSTANT_InvokeDynamic = 18;
}

struct cp_info {
    u8 tag;

    explicit cp_info(u8 tag) : tag(tag) {}

    cp_info() : tag(0) {}
};

struct ClassFile {
    u32 magic;
    u16 minor_version;
    u16 major_version;
    u16 constant_pool_count;
    cp_info **infos;
    u16 access_flags;
    u16 this_class;
    u16 super_class;
    u16 interfaces_count;
    u16 *interfaces;
    u16 fields_count;
    //filed_info
    u16 methods_count;
    //method_info
    u16 attributes_count;
    //attribute_info
};

struct CONSTANT_Class_info : public cp_info {
    u16 name_index;

    explicit CONSTANT_Class_info(u16 nameIndex) : cp_info(ClassFileConstants::CONSTANT_Class), name_index(nameIndex) {}
};

struct CONSTANT_Fieldref_info : public cp_info {
    u16 class_index;
    u16 name_and_type_index;

    CONSTANT_Fieldref_info(u16 classIndex, u16 nameAndTypeIndex) : cp_info(ClassFileConstants::CONSTANT_Fieldref),
                                                                   class_index(classIndex),
                                                                   name_and_type_index(nameAndTypeIndex) {}
};

struct CONSTANT_Methodref_info : public cp_info {
    u16 class_index;
    u16 name_and_type_index;

    CONSTANT_Methodref_info(u16 classIndex, u16 nameAndTypeIndex) : cp_info(ClassFileConstants::CONSTANT_Methodref),
                                                                    class_index(classIndex),
                                                                    name_and_type_index(nameAndTypeIndex) {}
};

struct CONSTANT_InterfaceMethodref_info : public cp_info {
    u16 class_index;
    u16 name_and_type_index;

    CONSTANT_InterfaceMethodref_info(u16 classIndex, u16 nameAndTypeIndex) : cp_info(
            ClassFileConstants::CONSTANT_InterfaceMethodref), class_index(classIndex),
                                                                             name_and_type_index(nameAndTypeIndex) {}
};

struct CONSTANT_String_info : public cp_info {
    u16 string_index;

    explicit CONSTANT_String_info(u16 stringIndex) : cp_info(ClassFileConstants::CONSTANT_String),
                                                     string_index(stringIndex) {}
};

struct CONSTANT_Integer_info : public cp_info {
    u32 bytes;  //big endian

    explicit CONSTANT_Integer_info(u32 bytes) : cp_info(ClassFileConstants::CONSTANT_Integer), bytes(bytes) {}
};

struct CONSTANT_Float_info : public cp_info {
    u32 bytes; //big endian

    explicit CONSTANT_Float_info(u32 bytes) : cp_info(ClassFileConstants::CONSTANT_Float), bytes(bytes) {}
};

struct CONSTANT_Long_info : public cp_info {
    union {
        u64 bytes;
        struct {
            u32 high_bytes;
            u32 low_bytes;
        };
    };

    CONSTANT_Long_info(u32 highBytes, u32 lowBytes) : cp_info(ClassFileConstants::CONSTANT_Long), high_bytes(highBytes),
                                                      low_bytes(lowBytes) {}
};

struct CONSTANT_Double_info : public cp_info {
    u32 high_bytes;
    u32 low_bytes;

    CONSTANT_Double_info(u32 highBytes, u32 lowBytes) : cp_info(ClassFileConstants::CONSTANT_Double),
                                                        high_bytes(highBytes),
                                                        low_bytes(lowBytes) {}
};

struct CONSTANT_NameAndType_info : public cp_info {
    u16 name_index;
    u16 descriptor_index;

    CONSTANT_NameAndType_info(u16 nameIndex, u16 descriptorIndex) : cp_info(ClassFileConstants::CONSTANT_NameAndType),
                                                                    name_index(nameIndex),
                                                                    descriptor_index(descriptorIndex) {}
};

struct CONSTANT_Utf8_info : public cp_info {
    u16 length;//count of u8
    u8 *bytes;

    CONSTANT_Utf8_info(u16 length, u8 *bytes) : cp_info(ClassFileConstants::CONSTANT_Utf8), length(length),
                                                bytes(bytes) {}
};

//page 88 todo
struct CONSTANT_MethodHandle_info : public cp_info {
    u8 reference_kind; //$5.4.3.5
    u16 reference_index;

    CONSTANT_MethodHandle_info(u8 referenceKind, u16 referenceIndex) : cp_info(
            ClassFileConstants::CONSTANT_MethodHandle),
                                                                       reference_kind(referenceKind),
                                                                       reference_index(referenceIndex) {}
};

struct CONSTANT_MethodType_info : public cp_info {
    u16 descriptor_index;

    explicit CONSTANT_MethodType_info(u16 descriptorIndex) : cp_info(ClassFileConstants::CONSTANT_MethodType),
                                                             descriptor_index(descriptorIndex) {}
};

struct CONSTANT_InvokeDynamic_info : public cp_info {
    u16 bootstrap_method_attr_index;
    u16 name_and_type_index;

    CONSTANT_InvokeDynamic_info(u16 bootstrapMethodAttrIndex, u16 nameAndTypeIndex) : cp_info(
            ClassFileConstants::CONSTANT_InvokeDynamic),
                                                                                      bootstrap_method_attr_index(
                                                                                              bootstrapMethodAttrIndex),
                                                                                      name_and_type_index(
                                                                                              nameAndTypeIndex) {}
};

//-------- field_info

struct field_info {
    u16 access_flags;
    u16 name_index;
    u16 descriptor_index;
    u16 attributes_count;
    //attribute_info todo
};

//-------- method_info

struct method_info {
    u16 access_flags;
    u16 name_index;
    u16 descriptor_index;
    u16 attributes_count;
    //attribute_info todo
};

//-------- attribute_info

struct attribute_info {
    u16 attribute_name_index;
    u32 attribute_length;
    u8 *info;
};

#endif //JVM_DEMO1_CLASS_FILE_HPP
