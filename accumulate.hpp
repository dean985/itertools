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
    
    template <typename Container,typename Ftor = add>
    class accumulate
    {
        Ftor _fnctor = [](int x, int y){return x*y;};
        Container _container;

    public:
        accumulate(Container cont, Ftor func) : _fnctor(func), _container(cont) {}
        accumulate(Container cont):_fnctor(add()), _container(cont)  { }

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
                // while (ftor(*_iter) && _iter != _end)
                // {
                //     _iter++;
                // }
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
                return (false);
            }
            decltype(*_iter) operator*()//// I need to make it template
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