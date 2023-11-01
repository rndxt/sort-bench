//#########################################
//
// Source code for homework HSE sort bench
//
//#########################################

#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename T> void sort5(std::vector<T> &arr, size_t L) {
  assert(arr.size() - L >= 5);
  T t;
  T &a = arr[L];
  T &b = arr[L + 1];
  T &c = arr[L + 2];
  T &d = arr[L + 3];
  T &e = arr[L + 4];

  if (a > e) {
    std::swap(a, e);
  }

  if (b > d) {
    std::swap(b, d);
  }

  if (a > b) {
    std::swap(a, b);
    std::swap(e, d);
  }

  if (c < b) {
    if (c < a) {
      std::swap(c, a);
    }
    std::swap(c, b);
  } else if (d < c) {
    std::swap(c, d);
  }

  if (e < c) {
    t = e;
    e = d;
    d = c;
    if (t < b) {
      c = b;
      b = t;
    } else {
      c = t;
    }
  } else if (e < d) {
    std::swap(e, d);
  }
}

template <typename T>
size_t partition(std::vector<T> &arr, size_t L, size_t R, size_t pivot_ind) {
  // [L; R]
  T pivot_value = arr[pivot_ind];
  std::swap(arr[pivot_ind], arr[R]);
  size_t i = L;
  for (size_t j = L; j < R; ++j) {
    if (arr[j] <= pivot_value) {
      std::swap(arr[i], arr[j]);
      ++i;
    }
  }
  std::swap(arr[i], arr[R]);
  return i;
}

template <typename T>
size_t select_order(std::vector<T> &arr, size_t L, size_t R, size_t n) {
  // n-th order statistics
  // [L; R]
  if (L == R) {
    return L;
  }

  size_t q = (R - L + 1) / 5;
  size_t r = (R - L + 1) % 5;

  size_t j = L;
  for (size_t i = 0; i < q; ++i) {
    sort5(arr, j);
    size_t median5 = j + 2;
    std::swap(arr[median5], arr[L + i]);
    j += 5;
  }

  if (r != 0) {
    std::sort(arr.begin() + j, arr.begin() + R + 1);
    size_t median5 = j + (R - j + 2) / 2 - 1;
    std::swap(arr[median5], arr[L + q]);
    q += 1;
  }

  size_t median_of_medians = select_order(arr, L, L + q - 1, (q + 1) / 2);
  size_t ind = partition(arr, L, R, median_of_medians);
  size_t k = ind - L + 1;
  if (n == k) {
    return ind;
  } else if (n < k) {
    return select_order(arr, L, ind - 1, n);
  } else {
    return select_order(arr, ind + 1, R, n - k);
  }
}

template <typename T>
void myquick_sort(std::vector<T> &arr, size_t L, size_t R) {
  // QuickSort implementation with tail recursion
  while (L < R) {
    size_t median_ind = select_order(arr, L, R, (R - L + 2) / 2);
    size_t q = partition(arr, L, R, median_ind);
    if (q > L) {
      myquick_sort(arr, L, q - 1);
    }
    L = q + 1;
  }
}

template <typename T> void quick_sort(std::vector<T> &arr) {
  if (!arr.empty()) {
    myquick_sort(arr, 0, arr.size() - 1);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Enter number of elemets" << std::endl;
    return 0;
  }
  size_t n = std::stol(argv[1], nullptr);

  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dis(0, 100);

  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    arr[i] = dis(gen);
  }

  clock_t start = clock();
  select_order(arr, 0, arr.size() - 1, (arr.size() + 1) / 2);
  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);

#if DEBUG
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
#endif
}
