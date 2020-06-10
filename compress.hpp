#pragma once

namespace itertools
{
    template <typename Container, typename Bool_Container>
    class compress
    {
        Container _container;
        Bool_Container bool_container;

    public:
        compress(Container cont, Bool_Container bool_cont) : _container(cont), bool_container(bool_cont) {}

        class iterator
        {
            typename Container::iterator _iter;
            typename Container::iterator _end;
            typename Bool_Container::iterator _bool_iter;

        public:
            iterator(typename Container::iterator iter, typename Container::iterator end, typename Bool_Container::iterator bool_iter)
                : _iter(iter), _end(end), _bool_iter(bool_iter)
            {
                while (_iter != _end && !(*_bool_iter))
                {
                    ++_iter;
                    ++_bool_iter;
                }
            }
            iterator(const iterator &other) = default;

            iterator &operator=(const iterator &other)
            {
                return *this;
            };
            iterator &operator++()
            {
                return *this;
            }
            iterator operator++(int)
            {
                return *this;
            }
            bool operator==(const iterator &other)
            {
                return false;
            }
            bool operator!=(const iterator &other)
            {
                return false;
            }
            auto operator*()
            {
                return *_iter;
            }
        };
        iterator begin()
        {
            return iterator(_container.begin(), _container.end(), bool_container.begin());
        }
        iterator end()
        {
            return iterator(_container.end(), _container.end(), bool_container.end());
        }
    };
} // namespace itertools