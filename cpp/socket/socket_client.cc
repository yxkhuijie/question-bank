#include <iostream>

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

void* func(void* arg) {
  int* socket_fd = (int*)arg;
  while(true) {
    const char* data = "hello!";
    int res = ::send(*socket_fd, data, 6, 0);
    std::cout << "send data: " << data << std::endl;
    ::sleep(1);
  }
  return 0;
}

int main(int argc, char** argv) {
  // 创建socket描述符
  //
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(8090);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int res = connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr));

  if (res < 0) {
    std::cout << "socket client connect error!" << std::endl;
    return -1;
  }

  pthread_t thread_id;
  if (pthread_create(&thread_id, NULL, func, &socket_fd) < 0) {
    std::cout << "socket client thread create error!" << std::endl;
    return -1;
  }

  std::cout << "client connect to: 127.0.0.1:8090" << std::endl;

  void* status;
  pthread_join(thread_id, &status);

  return 0;
}
