#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <algorithm>
#include <utility>

// reference: http://lokiastari.com/blog/2016/02/27/vector/index.html

template <typename T> class Vector {
public:
  Vector(int capacity = 8)
      : _capacity(capacity), _size(0),
        _array(static_cast<T *>(::operator new(sizeof(T) * capacity))) {}
  ~Vector() {
    // exception unsafe
    // Call dtor in reverse order
    for (std::size_t i = 0; i < _size; i++) {
      _array[_size - 1 - i].~T();
    }
    // delete buffer
    ::operator delete(_array);
  }

  Vector(Vector const &v)
      : _capacity(v._size), _size(0),
        _array(static_cast<T *>(::operator new(sizeof(T) * v._size))) {
    // exception unsafe
    for (std::size_t i = 0; i < v._size; i++) {
      push_back(v._array[i]);
    }
  }
  // Copy and swap idiom
  Vector &operator=(Vector const &v) {
    Vector tmp(v);
    tmp.swap(*this);
    return *this;
  }

  // move sematics
  Vector(Vector &&v) noexcept { v.swap(*this); }
  Vector &operator=(Vector &&v) noexcept {
    v.swap(*this);
    return *this;
  }

  void swap(Vector &v) noexcept {
    std::swap(_capacity, v._capacity);
    std::swap(_size, v._size);
    std::swap(_array, v._array);
  }

  void push_back(T const &e) {
    resize_if_require();
    push_back_internal(e);
  }
  void pop_back() {
    _size--;
    // Manually call dtor, because we used placement new
    _array[_size].~T();
  }
  void reserve(std::size_t capacity) {
    if (capacity > _capacity) {
      reserve_capacity(capacity);
    }
  }

private:
  void push_back_internal(T const &e) {
    // Use placement new
    new (_array + _size) T(e);
    _size++;
  }
  void resize_if_require() {
    if (_size == _capacity) {
      // growth factor: 1.5 or 2
      std::size_t new_capacity = _capacity * 2;
      if (new_capacity < 2) {
        new_capacity = 2;
      }
      reserve_capacity(new_capacity);
    }
  }
  void reserve_capacity(std::size_t new_capacity) {
    Vector<T> tmp(new_capacity);
    std::for_each(_array, _array + _size,
                  [&tmp](T const &item) { tmp.push_back_internal(item); });
    tmp.swap(*this);
  }

  std::size_t _capacity;
  std::size_t _size;
  T *_array;
};

#endif
