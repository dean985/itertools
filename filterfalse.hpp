#pragma once

namespace itertools
{
    template <typename Ftor, typename Container>
    class filterfalse
    {
        Ftor _fnctor;
        Container _container;

    public:
        filterfalse(Ftor func, Container cont) : _fnctor(func), _container(cont) {}

        class iterator
        {
            typename Container::iterator _iter;
            typename Container::iterator _end;
            Ftor ftor;

        public:
            iterator(typename Container::iterator iter,
                     typename Container::iterator end,
                     Ftor functor) : _iter(iter), _end(end), ftor(functor)
            {
                while (ftor(*_iter) && _iter != _end)
                {
                    _iter++;
                }
            }

            iterator(iterator &copy) = default;

            iterator &operator=(const iterator &it)
            {
                return *this;
            }
            iterator &operator++()
            {
                return *this;
            }
            iterator operator++(int a)
            {
                return *this;
            }
            bool operator==(const iterator &it)
            {
                return false;
            }
            bool operator!=(const iterator &it)
            {
                return false;
            }
            int operator*()
            {
                return *_iter;
            }
        };
        iterator begin()
        {
            return iterator(_container.begin(), _container.end(), _fnctor);
        }
        iterator end()
        {
            return iterator(_container.end(), _container.end(), _fnctor);
        }
    };
} // namespace itertools