#pragma once
#include <iostream>

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
                    
               
            }
            

            iterator(iterator &copy) = default;

            iterator &operator=(const iterator &it)
            {
                this->_iter = it->_iter;
                this->_end = it->_end;
                this->ftor = it->ftor;
                
                return *this;
            }
            iterator &operator++()
            {
                auto sum = (*_iter);
               do
                {
                  ++_iter;
                  sum +=(*_iter);
                } while (_iter != _end );
                return *this;
            }
            iterator operator++(int a)
            {
                iterator temp(*this);
                operator++();
                return temp;           
                
    
            }
            bool operator==(const iterator &it)
            {
              
                return (it._iter == this->_iter) ;
            }
            bool operator!=(const iterator &it)
            {
              // std::cout<<"in !="<<std::endl;
                return it._iter != this->_iter;
            }
            decltype(*_iter) operator*()//// I need to make it template
            {// i need to put here somthing that will return
                
                
                return (*_iter);
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