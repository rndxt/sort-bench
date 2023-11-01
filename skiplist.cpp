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
struct node {
  T value_;
  std::vector<node*> forward_; 

  node(T value, int size) : forward_(size, nullptr), value_(value) {} 
};

template <typename T>
class skip_list {
  using list_node = node<T>;

  list_node *header_;
  const size_t max_level = 10;
  int level_ = 0;


  size_t random_level() {
    static std::random_device rd; 
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0, 1.0);

    size_t lvl = 0;
    for (; lvl < max_level && dis(gen) < 0.25; ++lvl);
    return lvl;
  }

public:
  skip_list() { header_ = new list_node(T{}, max_level+1); }

  ~skip_list() {
    list_node *x = header_->forward_[0];
    list_node *next;
    while (x != nullptr) {
      next = x->forward_[0];
      delete x;
      x = next;
    }
    delete header_;
  }

  void insert(int key) {
    std::vector<list_node *> updatable(max_level);

    list_node *x = header_;
    for (size_t i = level_, j = 0; j <= level_; --i, ++j) {
      while (x->forward_[i] != nullptr && x->forward_[i]->value_ < key) {
        x = x->forward_[i];
      }
      updatable[i] = x;
    }

    int lvl = random_level();
    if (lvl > level_) {
      for (size_t i = level_+1; i <= lvl; ++i) {
        updatable[i] = header_;
      }
      level_ = lvl;
    }
    
    x = new list_node(key, level_+1);
    for (size_t i = 0; i <= lvl; ++i) {
      x->forward_[i] = updatable[i]->forward_[i];
      updatable[i]->forward_[i] = x;
    }
  }

  void print() {
    for (size_t i = level_, j = 0; j <= level_; --i, ++j) {
      list_node *x = header_->forward_[i];
      std::cout << "Level " << i << ": ";
      while (x != nullptr) {
        std::cout << x->value_ << " ";
        x = x->forward_[i];
      }
      std::cout << std::endl;
    }
  }
};

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Enter number of elemets" << std::endl;
    return 0;
  }
  size_t n = std::stol(argv[1], nullptr);

  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dis(0, 1000000);

  skip_list<int> L;
  clock_t start = clock();
  for (size_t i = 0; i < n; ++i) {
    L.insert(dis(gen));
  }
  clock_t finish = clock();
  std::printf("%f ms\n", 100. * (double)(finish - start) / CLOCKS_PER_SEC); //ms
}
