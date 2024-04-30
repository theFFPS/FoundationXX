// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __FOUNDATION_XX__ARRAY__BASE_ARRAY__H__
#define __FOUNDATION_XX__ARRAY__BASE_ARRAY__H__

#include <FoundationXX/Int>
#include <cstring>

namespace foundation {

template<typename T> struct BaseArray {
private:
    T *m_data;
    u64 m_size = 0; 
public:
    BaseArray() {}
    BaseArray(const T *data) {
        for (;; m_size++) if (!data[m_size]) break;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
    }
    BaseArray(const T *data, u64 size) {
        m_data = new T [size];
        m_size = size;
        memcpy(m_data, data, m_size);
    }

    ~BaseArray() {
        delete[] m_data;
    }

    T *data() {
        return m_data;
    }
    u64 size() {
        return m_size;
    }
    bool empty() {
        return !m_size;
    }
    void clear() {
        m_size = 0;
        delete[] m_data;
    }

    BaseArray<T>& reverse() {
        T *tmp_data = new T [m_size];
        memcpy(tmp_data, m_data, m_size);
        for (i64 i = ((i64)m_size) - 1; i >= 0 ; i--) m_data[i] = tmp_data[i];
        delete[] tmp_data;
        return *this;
    }
    BaseArray<T> reverse() const {
        T *tmp_data = new T [m_size];
        memcpy(tmp_data, m_data, m_size);
        for (i64 i = ((i64)m_size) - 1; i >= 0 ; i--) m_data[i] = tmp_data[i];
        delete[] tmp_data;
        return *this;
    }
    BaseArray<T>& swapCharEndian(u64 pos) {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_data[pos], sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_data[pos], tmp, sizeof(T));
        return *this;
    }
    BaseArray<T> swapCharEndian(u64 pos) const {
        char tmp[sizeof(T)], tmp2[sizeof(T)];
        memcpy(tmp, &m_data[pos], sizeof(T));
        for (i64 i = ((i64)sizeof(T)) - 1; i >= 0 ; i--) tmp2[i] = tmp[i];
        memcpy(&m_data[pos], tmp, sizeof(T));
        return *this;
    }
    BaseArray<T>& swapCharsEndian() {
        for (u64 i = 0; i < m_size; i++) swapCharEndian(i);
        return *this;
    }
    BaseArray<T> swapCharsEndian() const {
        for (u64 i = 0; i < m_size; i++) swapCharEndian(i);
        return *this;
    }

    BaseArray<T>& append(T ch) {
        T *tmp;
        if (m_size) {
            tmp = new T [m_size];
            memcpy(tmp, m_data, m_size);
            delete[] m_data;
        }
        m_size++;
        m_data = new T [m_size];
        if (m_size) {
            memcpy(m_data, tmp, m_size);
            delete[] tmp;
        }
        m_data[m_size-1] = ch;
        return *this;
    }
    BaseArray<T>& append(const T *val) {
        u64 valSize = 0;
        for (;; valSize++) if (!val[valSize]) break;
        for (u64 i = 0; i < valSize; i++) append(val[i]);
        return *this;
    }
    BaseArray<T>& append(BaseArray<T> val) {
        for (u64 i = 0; i < val.size(); i++) append(val[i]);
        return *this;
    }
    void swap(BaseArray<T>& val) {
        T *tmp = m_data;
        u64 tmpSize = m_size;
        m_data = val.data();
        m_size = val.size();
        val = 
    }
    BaseArray<T>& assign(const T *data, u64 size) {
        if (m_size) delete[] m_data;
        m_size = size;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
        return *this;
    }
    BaseArray<T> assign(const T *data, u64 size) const {
        if (m_size) delete[] m_data;
        m_size = size;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
        return *this;
    }
    BaseArray<T>& assign(const T *data) {
        m_size = 0;
        if (m_size) delete[] m_data;
        for (;; m_size++) if (!data[m_size]) break;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
        return *this;
    }
    BaseArray<T> assign(const T *data) const {
        m_size = 0;
        if (m_size) delete[] m_data;
        for (;; m_size++) if (!data[m_size]) break;
        m_data = new T [m_size];
        memcpy(m_data, data, m_size);
        return *this;
    }
    BaseArray<T>& assign(BaseArray<T> data) {
        return assign(data.data(), data.size());
    }
    BaseArray<T> assign(BaseArray<T> data) const {
        return assign(data.data(), data.size());
    }
    bool compare(const T *data) {
        u64 size = 0;
        for (;; size++) if (!data[size]) break;
        if (m_size != size) return false;
        for (u64 i = 0; i < size; i++) if (data[i] != m_data[i]) return false;
        return true;
    }
    bool compare(BaseArray<T> data) {
        return compare(data.data());
    }
    bool compare(const T *data, u64 size) {
        if (m_size < size) return false;
        for (u64 i = 0; i < size; i++) if (data[i] != m_data[i]) return false;
        return true;
    }
    bool compare(BaseArray<T> data, u64 size) {
        return compare(data.data(), size);
    }
    T& at(u64 pos) {
        return m_data[pos];
    }
    T at(u64 pos) const {
        return m_data[pos];
    }

    bool operator==(const T *data) {
        return compare(data);
    }
    bool operator==(BaseArray<T> data) {
        return compare(data);
    }
    bool operator!=(const T *data) {
        return !compare(data);
    }
    bool operator!=(BaseArray<T> data) {
        return !compare(data);
    }
    BaseArray<T>& operator=(const T *data) {
        return assign(data);
    }
    BaseArray<T> operator=(const T *data) const {
        return assign(data);
    }
    BaseArray<T>& operator=(BaseArray<T> data) {
        return assign(data);
    }
    BaseArray<T> operator=(BaseArray<T> data) const {
        return assign(data);
    }
    BaseArray<T>& operator+=(T ch) {
        return append(ch);
    }
    BaseArray<T>& operator+=(const T *val) {
        return append(val);
    }
    BaseArray<T>& operator+=(BaseArray<T> val) {
        return append(val);
    }
    BaseArray<T>& operator+(T ch) {
        return append(ch);
    }
    BaseArray<T>& operator+(const T *val) {
        return append(val);
    }
    BaseArray<T>& operator+(BaseArray<T> val) {
        return append(val);
    }
    T& operator[](u64 pos) {
        return at(pos);
    }
    T operator[](u64 pos) const {
        return at(pos);
    }
};

};

#endif //__FOUNDATION_XX__ARRAY__BASE_ARRAY__H__