//#########################################
//
// Source code for homework HSE sort bench
//
//#########################################

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct two_ind {
  size_t q, t;
};

template <typename T>
two_ind partition(std::vector<T> &arr, size_t L, size_t R) {
  // [L; R]
  // return two index q and t:
  //    all elements of arr[L..q-1] < pivot
  //    all elements of arr[q..t] == pivot
  //    all elements of arr[t+1..R] > pivot

  T pivot_value = arr[(L + R) / 2];
  size_t i = L;
  for (size_t j = L; j <= R; ++j) { // loop invariant:
    if (arr[j] < pivot_value) {     //     all element of A[L..i-1] < pivot
      std::swap(arr[i], arr[j]);    //     all elements of A[i..R] >= pivot
      ++i;
    }
  }
  size_t q = i;

  for (size_t j = i; j <= R; ++j) { // loop invariant:
    if (arr[j] == pivot_value) {    //    all elements A[q..i-1] == pivot
      std::swap(arr[i], arr[j]);
      ++i;
    }
  }

  size_t t = i - 1;
  return {q, t};
}

template <typename T>
void myquick_sort(std::vector<T> &arr, size_t L, size_t R) {
  // tail recursion
  while (L < R) {
    two_ind three_partitions = partition(arr, L, R);
    size_t q = three_partitions.q;
    size_t t = three_partitions.t;
    if (q > L) {
      myquick_sort(arr, L, q - 1);
    }
    L = t + 1;
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
  std::uniform_int_distribution<std::mt19937::result_type> dis(0, 1000000);

  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    arr[i] = dis(gen);
  }

  clock_t start = clock();

  quick_sort(arr);

  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);

#if DEBUG
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
#endif
}
