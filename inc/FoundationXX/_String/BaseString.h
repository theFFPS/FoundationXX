// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __FOUNDATION_XX__STRING__BASE_STRING__H__
#define __FOUNDATION_XX__STRING__BASE_STRING__H__

#include <FoundationXX/Int>
#include <cstring>

namespace foundation {

template<typename T> struct BaseString {
private:
    T *m_data;
    u64 m_size = 0; 
public:
    BaseString() {}
    BaseString(T *data) {
        for (;; m_size++) if (!data[i]) break;
        memcpy(data, m_data, m_size);
    }
    BaseString(T *data, u64 size) {
        m_data = new T [size];
        m_size = size;
        memcpy(data, m_data, m_size);
    }
    BaseString(BaseString<T> value) {
        m_data = new T [value.Size()];
        m_size = value.Size();
        for (u64 i = 0; i < m_size; i++) m_data[i] = value.Data()[i];
    }

    ~BaseString() {
        delete[] m_data;
    }

    T *data() {
        return m_data;
    }
    u64 size() {
        return m_size;
    }

    BaseString<T>& reverse() {
        T *tmp_data = new T [m_size];
        memcpy(tmp_data, m_data, m_size);
        for (i64 i = ((i64)m_size) - 1; i >= 0 ; i--) m_data[i] = tmp_data[i];
        delete[] tmp_data;
        return *this;
    }
    BaseString<T> reverse() const {
        T *tmp_data = new T [m_size];
        memcpy(tmp_data, m_data, m_size);
        for (i64 i = ((i64)m_size) - 1; i >= 0 ; i--) m_data[i] = tmp_data[i];
        delete[] tmp_data;
        return *this;
    }
    BaseString<T>& swapCharEndian(u64 pos) {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_data[pos], sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_data[pos], tmp, sizeof(T));
        return *this;
    }
    BaseString<T> swapCharEndian(u64 pos) const {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_data[pos], sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_data[pos], tmp, sizeof(T));
        return *this;
    }
    BaseString<T>& swapCharsEndian() {
        for (u64 i = 0; i < m_size; i++) SwapCharEndian(i);
        return *this;
    }
    BaseString<T> swapCharsEndian() const {
        for (u64 i = 0; i < m_size; i++) SwapCharEndian(i);
        return *this;
    }
};

};

#endif //__FOUNDATION_XX__STRING__BASE_STRING__H__