#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr() = default;
        shared_ptr(T* raw_pointer);
        shared_ptr(const shared_ptr<T>& ptr);
        shared_ptr(shared_ptr<T>&& ptr);
        ~shared_ptr();

        shared_ptr<T>& operator=(const shared_ptr<T>& ptr);
        shared_ptr<T>& operator=(shared_ptr<T>&& ptr);
        T* operator->();
        T operator*();

        T* get();
        unsigned short use_count();

      private:
        T* m_raw_pointer = nullptr;
        unsigned short* m_use_count = nullptr;
    };
    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr() = default;
        shared_ptr(T* raw_array_pointer, unsigned int N);
        shared_ptr(const shared_ptr<T[]>& array_ptr);
        shared_ptr(shared_ptr<T[]>&& array_ptr);
        ~shared_ptr();

        shared_ptr<T[]>& operator=(const shared_ptr<T[]>& array_ptr);
        shared_ptr<T[]>& operator=(shared_ptr<T[]>&& array_ptr);
        T& operator[](const unsigned int i);

        unsigned short use_count();
        unsigned int size();

      private:
        T* m_raw_array_pointer = nullptr;
        unsigned short* m_use_count = nullptr;
        unsigned int* m_size = nullptr;
    };

    template <typename T>
    shared_ptr<T>::shared_ptr(T* raw_pointer) :
        m_raw_pointer(raw_pointer)
    {
        unsigned short* initial_count = new unsigned short(1);
        m_use_count = initial_count;
    }
    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T>& ptr)
    {
        ++*ptr.m_use_count;

        m_raw_pointer = ptr.m_raw_pointer;
        m_use_count = ptr.m_use_count;
    }
    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& ptr)
    {
        m_raw_pointer = ptr.m_raw_pointer;
        m_use_count = ptr.m_use_count;

        ptr.m_raw_pointer = nullptr;
        ptr.m_use_count = nullptr;
    }
    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        if (m_use_count != nullptr)
        {
            --*m_use_count;

            if (*m_use_count <= 0)
            {
                delete m_raw_pointer;
                delete m_use_count;
                m_raw_pointer = nullptr;
                m_use_count = nullptr;
            }
        }
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr)
    {
        ++*ptr.m_use_count;
        --*m_use_count;

        m_raw_pointer = ptr.m_raw_pointer;
        m_use_count = ptr.m_use_count;

        return *this;
    }
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& ptr)
    {
        if (this != &ptr)
        {
            std::swap(m_raw_pointer, ptr.m_raw_pointer);
            std::swap(m_use_count, ptr.m_use_count);
        }
        return *this;
    }
    template <typename T>
    T* shared_ptr<T>::operator->()
    {
        return m_raw_pointer;
    }
    template <typename T>
    T shared_ptr<T>::operator*()
    {
        return *m_raw_pointer;
    }

    template <typename T>
    T* shared_ptr<T>::get()
    {
        return m_raw_pointer;
    }
    template <typename T>
    unsigned short shared_ptr<T>::use_count()
    {
        return *m_use_count;
    }

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    shared_ptr<T[]>::shared_ptr(T* raw_array_pointer, unsigned int N) :
        m_raw_array_pointer(raw_array_pointer)
    {
        unsigned short* initial_count = new unsigned short(1);
        unsigned int* initial_size = new unsigned int(N);

        m_use_count = initial_count;
        m_size = initial_size;
    }
    template <typename T>
    shared_ptr<T[]>::shared_ptr(const shared_ptr<T[]>& array_ptr)
    {
        ++*array_ptr.m_use_count;

        m_raw_array_pointer = array_ptr.m_raw_array_pointer;
        m_use_count = array_ptr.m_use_count;
        m_size = array_ptr.m_size;
    }
    template <typename T>
    shared_ptr<T[]>::shared_ptr(shared_ptr<T[]>&& array_ptr)
    {
        m_raw_array_pointer = array_ptr.m_raw_array_pointer;
        m_use_count = array_ptr.m_use_count;
        m_size = array_ptr.m_size;

        array_ptr.m_raw_array_pointer = nullptr;
        array_ptr.m_use_count = nullptr;
        array_ptr.m_size = nullptr;
    }
    template <typename T>
    shared_ptr<T[]>::~shared_ptr()
    {
        --*m_use_count;

        if (*m_use_count <= 0)
        {
            delete[] m_raw_array_pointer;
            delete m_use_count;
            delete m_size;
            m_raw_array_pointer = nullptr;
            m_use_count = nullptr;
            m_size = nullptr;
        }
    }

    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(const shared_ptr<T[]>& array_ptr)
    {
        ++*array_ptr.m_use_count;
        --*m_use_count;

        m_raw_array_pointer = array_ptr.m_raw_array_pointer;
        m_use_count = array_ptr.m_use_count;
        m_size = array_ptr.m_size;

        return *this;
    }
    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(shared_ptr<T[]>&& array_ptr)
    {
        if (this != &array_ptr)
        {
            std::swap(m_raw_array_pointer, array_ptr.m_raw_array_pointer);
            std::swap(m_use_count, array_ptr.m_use_count);
            std::swap(m_size, array_ptr.m_size);
        }
        return *this;
    }
    template <typename T>
    T& shared_ptr<T[]>::operator[](const unsigned int i)
    {
        return m_raw_array_pointer[i];
    }

    template <typename T>
    unsigned int shared_ptr<T[]>::size()
    {
        return *m_size;
    }
    template <typename T>
    unsigned short shared_ptr<T[]>::use_count()
    {
        return *m_use_count;
    }

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }

} // namespace usu