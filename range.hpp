#pragma once

namespace itertools
{
    template <typename T>
    class range
    {
    private:
        const T _first;
        const T _last;
        
        class iterator
        {
        public:
            T value;
            iterator(T v) : value(v) {}
            T operator*() const
            {
                return value;
            }
            iterator &operator++()
            {
                value++;
                return *this;
            }
            iterator operator++(int)
            {
                iterator temp(*this);
                operator++();
                return temp;
            }
            bool operator!=(iterator const &diff) const
            {
                return !(value == (diff.value));
            }
        };

    public:
        range(T first, T last) : _first(first), _last(last) {}

        iterator begin() const { return iterator(_first); }

        iterator end() const { return iterator(_last); }
    };
} // namespace itertools