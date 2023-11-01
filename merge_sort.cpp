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

template <typename T>
void mymerge_sort(std::vector<T> &arr, std::vector<T> &buf, size_t L,
                  size_t R) {
  if (R - L == 1) {
    return;
  }

  size_t mid = (L + R) / 2;
  mymerge_sort(arr, buf, L, mid);
  mymerge_sort(arr, buf, mid, R);

  size_t i = L;
  size_t j = mid;
  size_t k = L;
  while (i < mid && j < R) {
    if (arr[i] < arr[j]) {
      buf[k] = arr[i];
      ++i;
    } else {
      buf[k] = arr[j];
      ++j;
    }
    ++k;
  }

  while (i < mid) {
    buf[k] = arr[i];
    ++i;
    ++k;
  }

  while (j < R) {
    buf[k] = arr[j];
    ++j;
    ++k;
  }

  for (i = L; i < R; ++i) {
    arr[i] = buf[i];
  }
}

template <typename T> void merge_sort(std::vector<T> &arr) {
  if (!arr.empty()) {
    std::vector<T> buf(arr.size());
    mymerge_sort(arr, buf, 0, arr.size());
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Enter number of elemets" << std::endl;
    return 0;
  }

  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dis(0, 1000000);

  size_t n = std::stol(argv[1], nullptr);
  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    arr[i] = dis(gen);
  }

  clock_t start = clock();

  merge_sort(arr);

  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);
}