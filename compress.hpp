#pragma once

namespace itertools
{
  template <typename Container, typename Bool_Container>
  class compress
  {
    Container container;
    Bool_Container bool_container;

  public:
    compress(Container con, Bool_Container f) : container(con), bool_container(f) {}

    class iterator
    {
      typename Container::iterator c_current;
      typename Container::iterator c_end;
      typename Bool_Container::iterator b_current;
      typename Bool_Container::iterator b_end;

    public:
      iterator(typename Container::iterator c_cu, typename Container::iterator c_e,
               typename Bool_Container::iterator b_cu, typename Bool_Container::iterator b_e)
          : c_current(c_cu), c_end(c_e), b_current(b_cu), b_end(b_e) {}

      iterator &operator++()
      {
        do
        {
          ++b_current;
          ++c_current;
        } while (b_current != b_end && !*b_current);
        return *this;
      }
      iterator &operator++(int)
      {
        iterator copy = *this;
        ++(*this);
        return copy;
      }
      iterator &operator=(const iterator &other)
      {
        if (*this != other)
        {
          this->c_current = other.c_current;
          this->c_end = other.c_end;
          this->b_current = other.b_current;
          this->b_end = other.b_end;
        }
        return *this;
      }
      bool operator==(const iterator &other) const
      {
        return (c_current == other.c_current) && (b_current == other.b_current);
      }
      bool operator!=(const iterator &other) const
      {
        return (c_current != other.c_current) || (b_current != other.b_current);
      }
      auto operator*()
      {
        if (!(*b_current))
        {
          ++(*this);
        }
        return *c_current;
      }
    };

    iterator begin() { return iterator(container.begin(), container.end(), bool_container.begin(), bool_container.end()); }
    iterator end() { return iterator(container.end(), container.end(), bool_container.end(), bool_container.end()); }
  };
} // namespace itertools