#include <pthread.h>
#include <list>
#include <unistd.h>
#include <iostream>

struct Product {
  int data;
  Product() : data(0) {}
  Product(int d) : data(d) {}
};

std::list<Product*> data_list;

pthread_mutex_t mutex_;
pthread_cond_t provide_cond_;

void* provide(void* arg) {
  while (true) {
    Product* p = new Product(1);
    pthread_mutex_lock(&mutex_);
    data_list.push_back(p);
    std::cout << "provide: " << std::endl;
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&provide_cond_);
    ::sleep(1);
  }
}

void* custom(void* arg) {
  pthread_mutex_lock(&mutex_);
  while (true) {
    pthread_cond_wait(&provide_cond_, &mutex_);
    if (data_list.empty()) {
      pthread_mutex_unlock(&mutex_);
      continue;
    }
    std::list<Product*>::iterator it = data_list.begin();
    data_list.erase(it);
    std::cout << "custom **" << std::endl;
  }
  pthread_mutex_unlock(&mutex_);
}

int main(int argc, char** argv) {
  pthread_mutex_init(&mutex_, NULL);
  pthread_cond_init(&provide_cond_, NULL);
  pthread_t pid1;
  pthread_t pid2;
  pthread_create(&pid2, NULL, provide, NULL);
  pthread_create(&pid1, NULL, custom, NULL);
  void* status;
  pthread_join(pid1, &status);
  pthread_join(pid2, &status);
}
