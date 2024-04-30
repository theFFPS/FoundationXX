// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __FOUNDATION_XX__MEMORY__ALLOCATOR__H__
#define __FOUNDATION_XX__MEMORY__ALLOCATOR__H__

#include <FoundationXX/Int>
#include "Pointer.h"
#include <cstdio>
#include <cstring>

namespace foundation {

struct AllocatorConfig {
    bool hasMaxPointerSize = false; // is there maximum pointer size for this allocator?
    u64 maxPointerSize = 0; // maximum pointer size

    bool hasMaxMemory = false; // is there "reserved memory" for this allocator?
    u64 maxMemory = 0; // "reserved memory"
};
extern AllocatorConfig allocatorConfig;
extern u64 FOUNDATIONXX__allocated;


template<typename T> void unallocate(Pointer<T> pointer) {
    FOUNDATIONXX__allocated -= pointer.size();
    delete[] pointer.get();
}
template<typename T> Pointer<T> allocate(u64 size) {
    if (allocatorConfig.hasMaxPointerSize && size * sizeof(T) > allocatorConfig.maxPointerSize) {
        perror("Unable to allocate %llu because max pointer size is %llu!\n", size * sizeof(T), allocatorConfig.maxPointerSize);
        return Pointer<T>();
    }
    if (allocatorConfig.hasMaxMemory && FOUNDATIONXX__allocated + (size * sizeof(T)) > allocatorConfig.maxMemory) {
        perror("Unable to allocate %llu because memory reserve (%llu) will be overflowed!\n", size * sizeof(T), allocatorConfig.maxMemory);
        return Pointer<T>();
    }
    FOUNDATIONXX__allocated += size * sizeof(T);
    T *ptr = new T [size];
    return Pointer<T>(ptr);
}
template<typename T> Pointer<T> reallocate(Pointer<T> pointer, u64 size) {
    T *data = new T [pointer.size()], *tmp = pointer.get();
    memcpy(data, tmp, pointer.size());
    unallocate(pointer);
    Pointer<T> result = allocate(size + pointer.size());
    T *ptr = result.get();
    memcpy(ptr, data, pointer.size());
    delete[] data;
    return result;
}
template<typename T> Pointer<T> allocateRaw(u64 size) {
    if (allocatorConfig.hasMaxPointerSize && size > allocatorConfig.maxPointerSize) {
        perror("Unable to allocate %llu because max pointer size is %llu!\n", size, allocatorConfig.maxPointerSize);
        return Pointer<T>();
    }
    if (allocatorConfig.hasMaxMemory && FOUNDATIONXX__allocated + (size) > allocatorConfig.maxMemory) {
        perror("Unable to allocate %llu because memory reserve (%llu) will be overflowed!\n", size, allocatorConfig.maxMemory);
        return Pointer<T>();
    }
    FOUNDATIONXX__allocated += size;
    T *ptr = (T*)(new char [size]);
    return Pointer<T>(ptr);
}
template<typename T> Pointer<T> reallocateRaw(Pointer<T> pointer, u64 size) {
    T *data = (T*)(new char [pointer.size()]), *tmp = pointer.get();
    memcpy(data, tmp, pointer.size());
    unallocate(pointer);
    Pointer<T> result = allocate(size + pointer.size());
    T *ptr = result.get();
    memcpy(ptr, data, pointer.size());
    delete[] data;
    return result;
}

}

#endif //__FOUNDATION_XX__MEMORY__ALLOCATOR__H__