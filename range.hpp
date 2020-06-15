#pragma once

namespace itertools {
class range {
private:
  int _first;
  int _last;

public:
  range(int first, int last) : _first(first), _last(last) {}
  class iterator {
    int value;

  public:
    iterator(int v = 0) : value(v) {}
    //    iterator &operator=(const iterator &other) {
    //      if (this != &other)
    //        this->value = other.value;
    //      return *this;
    //    }
    int operator*() const { return value; }
    iterator &operator++() {
      value++;
      return *this;
    }
    iterator operator++(int) {
      iterator temp = *this;
      value++;
      return temp;
    }
    bool operator==(const iterator &it) const { return value == it.value; }

    bool operator!=(const iterator &it) const { return value != it.value; }
  };

  iterator begin() const { return iterator(_first); }

  iterator end() const { return iterator(_last); }
};
} // namespace itertools
