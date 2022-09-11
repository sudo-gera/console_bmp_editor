#include <stdexcept>

template <typename T, int N>
class Array {
 public:
  Array() = default;

  Array(std::initializer_list<T> lst) {  // Do not touch.
    std::copy(lst.begin(), lst.end(), arr_);
  }

  T& Front();

  T& Back();

  int Size();

  bool Empty();

  T* Data();

  T& operator[](int i);

  void Swap(Array<T, N>& cur);

 private:
  T arr_[N];
};
