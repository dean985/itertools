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
            typename Container::iterator _current;
            typename Container::iterator _end;
            Ftor ftor;
            decltype(*_iter) sum;

        public:
            iterator(typename Container::iterator iter,
                     typename Container::iterator end,
                     Ftor functor) : _iter(iter), _end(end), _current(_iter), ftor(functor), sum(*_iter)
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
                std::not_equal_to neq;
                auto temp_iter = _iter;
                sum = (*temp_iter);
                ++temp_iter;
                
                if((neq(_current, _end)) ){
                    ++_current;
                    
                    for(;neq(temp_iter, _current );++temp_iter)
                    {
                    
                     sum = ftor(sum, (*temp_iter)); 

                    }
                    if(neq(temp_iter,_end))
                    {
                        sum = ftor(sum, (*temp_iter)); 
                    }
                    // do
                    // {
                    //     sum = ftor(sum, (*temp_iter)); 
                    //     ++temp_iter;
                      
                    // }while (eq(temp_iter, _current ));

                
                } 
               

                return (*this);
            }
            iterator operator++(int a)
            {
                iterator temp(*this);
                operator++();
                return temp;           
            }

            bool operator==(const iterator &it)
            {
              
                return (it._iter == this->_current) ;
            }
            bool operator!=(const iterator &it)
            {
              // std::cout<<"in !="<<std::endl;
                return it._iter != this->_current;
            }
            decltype(*_iter) operator*()//// I need to make it template
            {// i need to put here somthing that will return
                
                return sum;
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