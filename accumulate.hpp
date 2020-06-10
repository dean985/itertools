#pragma once

namespace itertools
{
    typedef struct
    {
        template <typename T>
        T operator()(T a, T b)
        {
            return a + b;
        }
    } add;
    template <typename Container, typename Ftor = add>

    class accumulate
    {
    private:
        Container _container;
        Ftor _f;

    public:
        accumulate(Container container, Ftor f = add()) : _container(container), _f(f) {}

        class iterator
        {
        public:
            // T value;//use the iterator.begin()* to get the element
            int sum;
            decltype(*(_container.begin())) _element;
            typename Container::iterator _iterator;
            typename Container::iterator _end;
            Ftor _fIter;
            iterator(typename Container::iterator i, typename Container::iterator end, Ftor f) : 
            _iterator(i), _end(end), _fIter(f) { sum = 0; }

            auto operator*() const
            {
                return _element;
            }
            iterator &operator++()
            {
                //value++;
                return *this;
            }
            iterator operator++(int) /// obj++3
            {
                // iterator temp(*this);
                // operator++();
                return this;
            }
            bool operator!=(iterator const &diff) const
            {
                return false; //!(value == (diff.value));
            }
        };

        iterator begin() const
        {
            return iterator(_container.begin(), _container.end(), _f);
        }

        iterator end() const
        {
            return iterator(_container.begin(), _container.end(), _f);
	   
        }
    };
} // namespace itertools
