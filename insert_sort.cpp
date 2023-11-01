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

  insertion_sort(arr);

  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC);
}
