#include <functional>
#include <stdio.h>
#include <type_traits>

// https://stackoverflow.com/questions/9044866/how-to-get-the-number-of-arguments-of-stdfunction
template <typename T> struct function_traits;
template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>> {
  static const size_t nargs = sizeof...(Args);
  typedef R result_type;

  template <size_t i> struct arg {
    typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
  };
};

template <typename T> struct print_type {
  static void print() { printf("unknown type.\n"); }
};
template <> struct print_type<void> {
  static void print() { printf("void type.\n"); }
};
template <> struct print_type<int> {
  static void print() { printf("int type.\n"); }
};
template <> struct print_type<int *> {
  static void print() { printf("int* type.\n"); }
};
template <> struct print_type<double> {
  static void print() { printf("double type.\n"); }
};
template <> struct print_type<bool> {
  static void print() { printf("bool type.\n"); }
};

template <int N> struct run_func {
  template <typename T> static void run(T func) {}
};
template <> template <typename T> void run_func<0>::run(T func) { func(); }
template <> template <typename T> void run_func<1>::run(T func) {
  typedef
      typename function_traits<decltype(func)>::template arg<0>::type arg0_type;
  printf("Arg 0 type: ");
  print_type<arg0_type>::print();
  arg0_type arg0;
  func(arg0);
}
template <> template <typename T> void run_func<2>::run(T func) {
  typedef
      typename function_traits<decltype(func)>::template arg<0>::type arg0_type;
  printf("Arg 0 type: ");
  print_type<arg0_type>::print();
  arg0_type arg0;
  typedef
      typename function_traits<decltype(func)>::template arg<1>::type arg1_type;
  printf("Arg 1 type: ");
  print_type<arg1_type>::print();
  arg1_type arg1;
  func(arg0, arg1);
}

template <typename T> void call_function(std::function<T> func) {
  constexpr size_t nargs = function_traits<decltype(func)>::nargs;
  printf("Args number: %ld.\n", nargs);
  typedef typename function_traits<decltype(func)>::result_type result_type;
  printf("Result type: ");
  print_type<result_type>::print();
  run_func<nargs>::run(func);
}

bool f1(int *, int) {
  printf("Run f1.\n");
  return true;
}

void f2(double) { printf("Run f2.\n"); };

int main() {
  call_function(std::function<decltype(f1)>(f1));
  call_function(std::function<decltype(f2)>(f2));
  return 0;
}
