#pragma once
#include <algorithm>
#include <exception>
#include <vector>
//#include "build/googletest-src/googletest/include/gtest/internal/gtest-port.h"

namespace usu
{
    template <typename T, typename R = unsigned int>
    class priority_queue
    {
      public:
        using priority_type = R;
        using value_type = T;
        using size_type = std::size_t;

        struct queue_item
        {
            value_type value = value_type();
            priority_type priority = 0;
        };

        using difference_type = size_type;
        using reference = queue_item&;
        using pointer = queue_item*;

      private:
        //member variables
        size_type m_n = 0;
        size_type m_size = 0;
        std::vector<queue_item> m_queue;

      public:
        class iterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            using iterator_category = std::forward_iterator_tag;
            //constructors
            iterator() :
                iterator(nullptr)
            {
            }
            iterator(pointer ptr) :
                m_pos(0),
                m_queue_item_ptr(ptr)
            {
            }
            iterator(size_type pos, pointer ptr) :
                m_pos(pos),
                m_queue_item_ptr(ptr)
            {
            }
            iterator(const iterator& iter);
            iterator(iterator&& iter) noexcept;
            //methods
            iterator& operator++();
            iterator operator++(int);
            iterator& operator=(const iterator& rhs);
            iterator& operator=(iterator&& rhs);
            queue_item operator*();
            pointer operator->();
            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);
            size_type pos() { return m_pos; }

          private:
            size_type m_pos;
            pointer m_queue_item_ptr;
        };
        //constructors
        priority_queue() = default;
        priority_queue(const std::initializer_list<std::pair<T, R>>& init_list);
        //methods
        void enqueue(T value, priority_type priority);
        auto dequeue();
        iterator find(T value);
        void update(iterator i, priority_type priority);
        bool empty();
        size_type size();
        iterator begin();
        iterator end();

      private:
        //methods
        bool is_leaf(size_type pos);
        size_type left_child(size_type pos);
        size_type right_child(size_type pos);
        size_type parent(size_type pos);
        void build_heap();
        void sift_down(size_type pos);
        void update_heap(size_type pos);
    };
    template <typename T, typename R>
    priority_queue<T, R>::priority_queue(const std::initializer_list<std::pair<T, R>>& init_list)
    {
        //Add entire list to m_queue, then call build_heap()
        while (init_list.size() >= m_size)
        {
            m_size = static_cast<size_type>(m_size * 1.25 + 1);
            m_queue.resize(m_size);
        }
        size_type pos = 0;

        for (auto i = init_list.begin(); i != init_list.end(); ++i, pos++)
        {
            queue_item item;
            item.value = (*i).first;
            item.priority = (*i).second;

            m_queue.at(pos) = item;
            m_n++;
        }
        while (m_n + 1 >= m_size)
        {
            m_size = static_cast<size_type>(m_size * 1.25 + 1);
            m_queue.resize(m_size);
        }
        build_heap();
    }

    template <typename T, typename R>
    void priority_queue<T, R>::enqueue(T value, priority_type priority)
    {
        while (m_n + 1 >= m_size)
        {
            m_size = static_cast<size_type>(m_size * 1.25 + 1);
            m_queue.resize(m_size);
        }
        size_type curr_pos = m_n++;
        size_type parent_pos = parent(curr_pos);
        queue_item item;
        item.value = value;
        item.priority = priority;
        m_queue.at(curr_pos) = item;

        while ((curr_pos != 0) && (m_queue.at(parent_pos).priority < m_queue.at(curr_pos).priority))
        {
            auto curr_it = m_queue.begin() + curr_pos;
            auto parent_it = m_queue.begin() + parent_pos;

            std::iter_swap(curr_it, parent_it);
            curr_pos = parent_pos;
            parent_pos = parent(curr_pos);
        }
    }
    template <typename T, typename R>
    auto priority_queue<T, R>::dequeue()
    {
        if (empty())
        {
            throw std::exception("priority queue is empty");
        }
        auto it = m_queue.begin() + (--m_n);
        std::iter_swap(m_queue.begin(), it);
        sift_down(0);
        return m_queue.at(m_n);
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator priority_queue<T, R>::find(T value)
    {
        for (size_type i = 0; i < m_n; i++)
        {
            if (m_queue.at(i).value == value)
            {
                return iterator(i, &m_queue.at(i));
            }
        }
        return end();
    }
    template <typename T, typename R>
    void priority_queue<T, R>::update(priority_queue<T, R>::iterator i, priority_type priority)
    {
        i->priority = priority;
        update_heap(i.pos());
    }
    template <typename T, typename R>
    bool priority_queue<T, R>::empty()
    {
        if (m_n == 0)
        {
            return true;
        }
        return false;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::size_type priority_queue<T, R>::size()
    {
        return m_n;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator priority_queue<T, R>::begin()
    {
        if (m_n == 0)
        {
            return end();
        }
        return iterator(&(m_queue.at(0)));
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator priority_queue<T, R>::end()
    {
        if (m_size == 0)
        {
            return iterator();
        }
        return iterator(m_n, &(m_queue.at(m_n)));
    }
    template <typename T, typename R>
    bool priority_queue<T, R>::is_leaf(size_type pos)
    {
        return (pos >= m_n / 2) && (pos < m_n);
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::size_type priority_queue<T, R>::left_child(size_type pos)
    {
        return 2 * pos + 1;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::size_type priority_queue<T, R>::right_child(size_type pos)
    {
        return 2 * pos + 2;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::size_type priority_queue<T, R>::parent(size_type pos)
    {
        return (pos - 1) / 2;
    }
    template <typename T, typename R>
    void priority_queue<T, R>::build_heap()
    {
        for (size_type i = m_n / 2; i > 0; i--)
        {
            sift_down(i - 1);
        }
    }
    template <typename T, typename R>
    void priority_queue<T, R>::sift_down(size_type pos)
    {
        if ((pos < 0) || (pos >= m_n))
        {
            return;
        }
        while (!is_leaf(pos))
        {
            size_type j = left_child(pos);

            if ((j < (m_n - 1)) && (m_queue.at(j).priority < m_queue.at(j + 1).priority))
            {
                j++;
            }
            if (m_queue.at(pos).priority >= m_queue.at(j).priority)
            {
                return;
            }
            auto curr_it = m_queue.begin() + j;
            auto parent_it = m_queue.begin() + pos;
            std::iter_swap(curr_it, parent_it);
            pos = j;
        }
    }
    template <typename T, typename R>
    void priority_queue<T, R>::update_heap(size_type pos)
    {
        auto parent_pos = parent(pos);

        while ((pos > 0) && (m_queue.at(pos).priority > m_queue.at(parent_pos).priority))
        {
            auto curr_it = m_queue.begin() + pos;
            auto parent_it = m_queue.begin() + parent_pos;
            std::iter_swap(curr_it, parent_it);
            pos = parent_pos;
            parent_pos = parent(pos);
        }
        sift_down(pos);
    }

    template <typename T, typename R>
    priority_queue<T, R>::iterator::iterator(const iterator& iter)
    {
        m_pos = iter.m_pos;
        m_queue_item_ptr = iter.m_queue_item_ptr;
    }
    template <typename T, typename R>
    priority_queue<T, R>::iterator::iterator(iterator&& iter) noexcept
    {
        m_pos = iter.m_pos;
        m_queue_item_ptr = iter.m_queue_item_ptr;

        iter.m_pos = 0;
        iter.m_queue_item_ptr = nullptr;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator& priority_queue<T, R>::iterator::operator++()
    {
        m_queue_item_ptr++;
        m_pos++;
        return *this;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator priority_queue<T, R>::iterator::operator++(int)
    {
        iterator i = *this;
        ++(*this);
        return i;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator& priority_queue<T, R>::iterator::operator=(const iterator& rhs)
    {
        m_pos = rhs.m_pos;
        m_queue_item_ptr = rhs.m_queue_item_ptr;
        return *this;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::iterator& priority_queue<T, R>::iterator::operator=(iterator&& rhs)
    {
        if (this != &rhs)
        {
            std::swap(m_pos, rhs.m_pos);
            std::swap(m_queue_item_ptr, rhs.m_queue_item_ptr); // *NEED HELP*
        }
        return *this;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::queue_item priority_queue<T, R>::iterator::operator*()
    {
        return *m_queue_item_ptr;
    }
    template <typename T, typename R>
    typename priority_queue<T, R>::pointer priority_queue<T, R>::iterator::operator->()
    {
        return m_queue_item_ptr;
    }
    template <typename T, typename R>
    bool priority_queue<T, R>::iterator::operator==(const iterator& rhs)
    {
        return m_queue_item_ptr == rhs.m_queue_item_ptr;
    }
    template <typename T, typename R>
    bool priority_queue<T, R>::iterator::operator!=(const iterator& rhs)
    {
        return m_queue_item_ptr != rhs.m_queue_item_ptr;
    }
} // namespace usu