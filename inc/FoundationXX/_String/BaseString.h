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
    BaseString(const T *data) {
        for (;; m_size++) if (!data[m_size]) break;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
    }
    BaseString(const T *data, u64 size) {
        m_data = new T [size];
        m_size = size;
        memcpy(m_data, data, m_size);
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
        for (u64 i = 0; i < m_size; i++) swapCharEndian(i);
        return *this;
    }
    BaseString<T> swapCharsEndian() const {
        for (u64 i = 0; i < m_size; i++) swapCharEndian(i);
        return *this;
    }

    BaseString<T>& append(T ch) {
        T *tmp = new T [m_size];
        memcpy(tmp, m_data, m_size);
        m_size++;
        delete[] m_data;
        m_data = new T [m_size];
        memcpy(m_data, tmp, m_size);
        delete[] tmp;
        m_data[m_size-1] = ch;
        return *this;
    }
    BaseString<T>& append(const T *val) {
        u64 valSize = 0;
        for (;; valSize++) if (!val[valSize]) break;
        for (u64 i = 0; i < valSize; i++) append(val[i]);
        return *this;
    }
    BaseString<T>& append(BaseString<T> val) {
        for (u64 i = 0; i < val.size(); i++) append(val[i]);
        return *this;
    }

    BaseString<T>& operator+=(T ch) {
        return append(ch);
    }
    BaseString<T>& operator+=(const T *val) {
        return append(val);
    }
    BaseString<T>& operator+=(BaseString<T> val) {
        return append(val);
    }
    BaseString<T>& operator+(T ch) {
        return append(ch);
    }
    BaseString<T>& operator+(const T *val) {
        return append(val);
    }
    BaseString<T>& operator+(BaseString<T> val) {
        return append(val);
    }
    T operator[](u64 pos) {
        return m_data[pos];
    }
};

};

#endif //__FOUNDATION_XX__STRING__BASE_STRING__H__