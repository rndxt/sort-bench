//#########################################
//
// Source code for homework HSE sort bench
//
//#########################################

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename T> void insertion_sort(std::vector<T> &arr) {
  for (size_t i = 1; i < arr.size(); ++i) {
    T x = arr[i];
    size_t j = i;
    while (j > 0 && arr[j - 1] > x) {
      arr[j] = arr[j - 1];
      --j;
    }
    arr[j] = x;
  }
}

template <typename T>
size_t bin_search(std::vector<T> &arr, T key, size_t L, size_t R) {
  // левосторонний бинарный поиск
  // ищем самый левый элемент, который > key
  while (L < R) {
    size_t mid = L + (R - L) / 2;
    if (arr[mid] > key) {
      R = mid; // если средний элемент > key, то сдвигаем границы поиска,
               // учитывается средний
    } else {
      L = mid + 1; // сдвигаем границы поиска, не учитывая средний
    }
  }
  return L;
}

template <typename T> void bin_search_insert_sort(std::vector<T> &arr) {
  for (size_t i = 1; i < arr.size(); ++i) {
    T x = std::move(arr[i]);
    size_t ind = bin_search(arr, x, 0, i);

    size_t j = i;
    while (j > ind) {
      arr[j] = std::move(arr[j - 1]);
      --j;
    }
    arr[j] = std::move(x);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Enter number of elemets" << std::endl;
    return 0;
  }
  size_t n = std::stol(argv[1], nullptr);
  size_t m = std::stol(argv[2], nullptr);

  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dis('a', 'z');
  std::vector<std::string> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::string s;
    for (size_t j = 0; j < m; ++j) {
      s.push_back(dis(gen));
    }
    arr[i] = std::move(s);
  }

  auto arr_copy(arr);
  clock_t start = clock();
  insertion_sort(arr);
  clock_t finish = clock();
  std::printf("basic insert: %f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);


  start = clock();
  bin_search_insert_sort(arr_copy);
  finish = clock();
  std::printf("binsearch insert: %f ms\n",
              100. * (double)(finish - start) / CLOCKS_PER_SEC);

}
