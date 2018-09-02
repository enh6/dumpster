#ifndef _SMART_POINTER_H_
#define _SMART_POINTER_H_
#include <new>
#include <utility>

// reference:
// http://lokiastari.com/blog/2014/12/30/c-plus-plus-by-example-smart-pointer/index.html

template <typename T> class UniquePointer {
public:
  UniquePointer() : _raw_ptr(nullptr) {}
  // Avoid implicit construction
  explicit UniquePointer(T *ptr) : _raw_ptr(ptr) {}
  ~UniquePointer() { delete _raw_ptr; }

  // Ctor/Assignment for nullptr
  UniquePointer(std::nullptr_t) : _raw_ptr(nullptr) {}
  UniquePointer &operator=(std::nullptr_t) {
    reset();
    return *this;
  }

  // Rule of three
  // If we have constructor, we need to handle copy constructor
  // and assignment constructor.
  UniquePointer(UniquePointer const &) = delete;
  UniquePointer &operator=(UniquePointer const &) = delete;

  // move sematics
  UniquePointer(UniquePointer &&up) noexcept { up.swap(*this); }
  UniquePointer &operator=(UniquePointer &&up) noexcept {
    up.swap(*this);
    return *this;
  }

  // Ctor/Assignment for types derived from T
  template <typename U> UniquePointer(UniquePointer<U> &&up) {
    UniquePointer<T> tmp(up.release());
    tmp.swap(*this);
  }
  template <typename U> UniquePointer &operator=(UniquePointer<U> &&up) {
    UniquePointer tmp(up.release());
    tmp.swap(*this);
    return *this;
  }

  T &operator*() const { return *_raw_ptr; }
  T *operator->() const { return _raw_ptr; }
  T *get() const { return _raw_ptr; }
  explicit operator bool() { return _raw_ptr; } // bool conversion

  T *release() noexcept {
    T *ret = nullptr;
    std::swap(ret, _raw_ptr);
    return ret;
  }
  void swap(UniquePointer &up) noexcept { std::swap(_raw_ptr, up._raw_ptr); }
  void reset() {
    T *tmp = release();
    delete tmp;
  }

private:
  T *_raw_ptr;
};

template <typename T> void swap(UniquePointer<T> &lhs, UniquePointer<T> &rhs) {
  lhs.swap(rhs);
}

template <typename T> class SharedPointer {
public:
  // Dtor will not be called when Ctor throws,
  // manually release resource.
  explicit SharedPointer(T *ptr)
      : _raw_ptr(ptr), _count(new (std::nothrow) int(1)) {
    if (_count == nullptr) {
      delete _raw_ptr;
      throw std::bad_alloc();
    }
  }
  ~SharedPointer() {
    (*_count)--;
    if ((*_count) == 0) {
      delete _raw_ptr;
    }
  }
  SharedPointer(SharedPointer const &sp)
      : _raw_ptr(sp._raw_ptr), _count(sp._count) {
    (*_count)++;
  }
  // Copy and swap idiom
  SharedPointer &operator=(SharedPointer sp) {
    sp.swap(*this);
    return *this;
  }
  SharedPointer &operator=(T *ptr) {
    SharedPointer tmp(ptr);
    tmp.swap(*this);
    return *this;
  }
  void swap(SharedPointer &sp) noexcept {
    std::swap(_raw_ptr, sp._raw_ptr);
    std::swap(_count, sp._count);
  }
  T &operator*() const { return *_raw_ptr; }
  T *operator->() const { return _raw_ptr; }
  T *get() const { return _raw_ptr; }
  explicit operator bool() { return _raw_ptr; } // bool conversion
private:
  T *_raw_ptr;
  int *_count;
};

#endif
