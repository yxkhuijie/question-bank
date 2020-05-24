#include <iostream>
#include <pthread.h>
#include <unistd.h>

int count = 20;
int current = 0;

pthread_mutex_t mutex;

void* func(void* arg) {
  int name = *((int*)arg);
  while(current < count) {
    if ((current + 1) % 4 != name % 4) {
      ::usleep(1000);
      continue;
    }
    pthread_mutex_lock(&mutex);
    std::cout << "print " << name << ": " << current << std::endl;
    current++;
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char** argv) {
  pthread_mutex_init(&mutex, NULL);

  pthread_t t1;
  pthread_t t2;
  pthread_t t3;
  pthread_t t4;

  int name1 = 1;
  int name2 = 2;
  int name3 = 3;
  int name4 = 4;

  pthread_create(&t1, NULL, func, &name1);
  pthread_create(&t2, NULL, func, &name2);
  pthread_create(&t3, NULL, func, &name3);
  pthread_create(&t4, NULL, func, &name4);

  void* status;
  pthread_join(t1, &status);
  pthread_join(t2, &status);
  pthread_join(t3, &status);
  pthread_join(t4, &status);

  pthread_mutex_destroy(&mutex);
}
