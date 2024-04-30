// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __FOUNDATION_XX__MEMORY__POINTER__H__
#define __FOUNDATION_XX__MEMORY__POINTER__H__

#include <FoundationXX/Int>

namespace foundation {

template<typename T> struct Pointer {
private:
    T *m_pointer;
    u64 m_size = 0;
public:
    Pointer(T& value) {
        m_pointer = &value;
        m_size = sizeof(value);
    }
    Pointer(T *value) {
        m_pointer = value;
        m_size = sizeof(value);
    }
    Pointer() {}

    u64 size() {
        return m_size;
    }
    T *get() {
        return m_pointer;
    }
    T& unpoint() {
        return *m_pointer;
    }
    T unpoint() const {
        return *m_pointer;
    }
    T& unpoint(u64 pos) {
        if (pos * sizeof(T) >= m_size) return *m_pointer;
        return m_pointer[pos];
    }
    T unpoint(u64 pos) const {
        if (pos * sizeof(T) >= m_size) return *m_pointer;
        return m_pointer[pos];
    }

    Pointer<T>& swapEndian() {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_pointer, sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_pointer, tmp, sizeof(T));
        return *this;
    } 
    Pointer<T> swapEndian() const {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_pointer, sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_pointer, tmp, sizeof(T));
        return *this;
    }

    Pointer<T>& operator=(T *value) {
        m_pointer = value;
        m_size = sizeof(value);
    }
    Pointer<T> operator=(T *value) const {
        m_pointer = value;
        m_size = sizeof(value);
    }
    Pointer<T>& operator=(T& value) {
        m_pointer = &value;
        m_size = sizeof(value);
    }
    Pointer<T> operator=(T& value) const {
        m_pointer = &value;
        m_size = sizeof(value);
    }
    Pointer<T>& operator=(Pointer<T> value) {
        m_pointer = value.get();
        m_size = value.size();
    }
    Pointer<T> operator=(Pointer<T> value) const {
        m_pointer = value.get();
        m_size = value.size();
    }
    bool operator==(T *value) {
        return *value == *m_pointer;
    }
    bool operator==(T &value) {
        return value == *m_pointer;
    }
    bool operator==(Pointer<T> value) {
        return value.get() == *m_pointer;
    }
    bool operator!=(T *value) {
        return *value != *m_pointer;
    }
    bool operator!=(T &value) {
        return value != *m_pointer;
    }
    bool operator!=(Pointer<T> value) {
        return value.get() != *m_pointer;
    }
};

}

#endif //__FOUNDATION_XX__MEMORY__POINTER__H__