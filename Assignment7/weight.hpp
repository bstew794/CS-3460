#pragma once
#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename T, typename R = std::uint64_t>
    class weight
    {
      public:
        weight();
        weight(R start_count);
        R count() const;
        weight<T, R> operator+(const weight<T, R>& w);
        weight<T, R> operator-(const weight<T, R>& w);

        using conversion = T;

      private:
        R m_count;
    };
    using microgram = weight<std::ratio<1, 1000000>>;
    using gram = weight<std::ratio<1, 1>>;
    using kilogram = weight<std::ratio<1000, 1>>;
    using ounce = weight<std::ratio<28349523125, 1000000000>, double>;
    using pound = weight<std::ratio<45359237, 100000>, double>;
    using ton = weight<std::ratio<90718474, 100>, double>;

    template <typename T, typename R>
    weight<T, R>::weight() :
        m_count(0)
    {
    }

    template <typename T, typename R>
    weight<T, R>::weight(R start_count) :
        m_count(start_count)
    {
    }

    template <typename T, typename R>
    R weight<T, R>::count() const
    {
        return m_count;
    }

    template <typename T, typename R>
    weight<T, R> weight<T, R>::operator+(const weight<T, R>& w)
    {
        usu::weight<T, R> result(this->count() + w.count());
        return result;
    }

    template <typename T, typename R>
    weight<T, R> weight<T, R>::operator-(const weight<T, R>& w)
    {
        weight<T, R> result(this->count() - w.count());
        return result;
    }
    // How do I change the storage type of T to double?
    template <typename T, typename R>
    T weight_cast(R w)
    {
        T empty_w;

        auto gram_count = (static_cast<double>(w.count()) * R::conversion::num) / R::conversion::den;
        auto converted_count = (static_cast<double>(gram_count) * T::conversion::den) / T::conversion::num;

        return T(static_cast<decltype(empty_w.count())>(converted_count));
    }

    template <typename T, typename R, typename U>
    weight<T, R> operator*(const weight<T, R>& w, const U s)
    {
        weight<T, R> result((w.count() * static_cast<R>(s)));
        return result;
    }

    template <typename T, typename R, typename U>
    weight<T, R> operator*(const U s, const weight<T, R>& w)
    {
        weight<T, R> result((static_cast<R>(s) * w.count()));
        return result;
    }

    template <typename T, typename R>
    bool operator==(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() == new_w2.count())
        {
            return true;
        }
        return false;
    }

    template <typename T, typename R>
    bool operator!=(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() != new_w2.count())
        {
            return true;
        }
        return false;
    }

    template <typename T, typename R>
    bool operator<(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() < new_w2.count())
        {
            return true;
        }
        return false;
    }

    template <typename T, typename R>
    bool operator>(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() > new_w2.count())
        {
            return true;
        }
        return false;
    }

    template <typename T, typename R>
    bool operator<=(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() <= new_w2.count())
        {
            return true;
        }
        return false;
    }

    template <typename T, typename R>
    bool operator>=(const T& w1, const R& w2)
    {
        auto new_w2 = weight_cast<T>(w2);

        if (w1.count() >= new_w2.count())
        {
            return true;
        }
        return false;
    }
} // namespace usu