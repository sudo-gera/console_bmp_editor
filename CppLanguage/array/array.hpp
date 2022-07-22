#pragma once
// NOLINT

#include <stdexcept>

template <typename T, int N>
class Array {
 public:
  T& Front();
  T& Back();
  int Size();
  bool Empty();
  T* Data();
  T& operator[](int i);
  
  void Swap(Array<T, N>& cur);
};