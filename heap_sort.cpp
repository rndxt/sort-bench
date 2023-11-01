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
void sift_down(std::vector<T> &arr, size_t i, size_t heap_size) {
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;
  size_t j = i;
  if (left < heap_size && arr[left] > arr[j]) {
    j = left;
  }
  if (right < heap_size && arr[right] > arr[j]) {
    j = right;
  }
  if (j != i) {
    std::swap(arr[i], arr[j]);
    sift_down(arr, j, heap_size);
  }
}

template <typename T> void make_heap(std::vector<T> &arr) {
  for (size_t i = 0; i <= arr.size() / 2; ++i) {
    sift_down(arr, arr.size() / 2 - i, arr.size());
  }
}

template <typename T> void heap_sort(std::vector<T> &arr) {
  make_heap(arr);
  size_t heap_size = arr.size();
  while (heap_size > 1) {
    std::swap(arr[0], arr[heap_size - 1]);
    --heap_size;
    sift_down(arr, 0, heap_size);
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

  heap_sort(arr);

  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);
#if DEBUG
  for (size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << std::endl;
  }
#endif
}
