#pragma once

namespace itertools
{
    
    template <typename Container, typename Ftor = add>
    
    class accumulate
    {
    private:
         Container _container;
         Ftor _f;
        
        class iterator
        {
        public:
            // T value;//use the iterator.begin()* to get the element
            int sum;
            decltype(*(_container.begin())) _element;
            typename Container::iterator _iterator;
            typename Container::iterator _end;
            Ftor _fIter;
            iterator(typename Container::iterator i , typename Container::iterator end, Ftor f) :
                    _iterator(i), _end(end), _f(f) {sum = 0;}
            
            auto operator*() const
            {
                return _element;
            }
            iterator &operator++()
            {
                //value++;
                return *this;
            }
            iterator operator++(int)/// obj++3
            {
                // iterator temp(*this);
                // operator++();
                return this;
            }
            bool operator!=(iterator const &diff) const
            {
                return true;//!(value == (diff.value));
            }
        };
        
        
    typedef struct{
        template<typename T>
        T operator()(T a, T b)
        {
                return a+b;
        }
    } add;
        
    public:
        // accumulate(Con val) : _first((val.begin())), _last((val.end())) {}
        //accumulate(Container container) : _container(container){ }
        add a;
        
        accumulate(Container container, Ftor f=a) : _container(container), _f(f) {}

        iterator begin() const 
        { 
            return itertor(_container.begin(), _container.end(),_f ); 
            
        }

        iterator end() const { 
            return itertor(_container.begin(), _container.end(),_f );
        
        }

    };
} // namespace itertools