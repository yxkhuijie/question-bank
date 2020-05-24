#include <iostream>

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

void* myfunc(void* arg);

void* func(void* arg) {
  int* socket_fd = (int*)arg;
  while(true) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int client = ::accept(*socket_fd, (struct sockaddr*)&addr, (socklen_t*)&len);
    if (client < 0 ) {
      std::cout << "socket server accept error: clent: " << client << std::endl;
      continue;
    }

    // client address
    const char* res = inet_ntoa(addr.sin_addr);
    unsigned int port = ntohs(addr.sin_port);

    std::cout << "accept from " << res << ":" << port << std::endl;

    pthread_t tid;
    pthread_create(&tid, NULL, myfunc, &client);
  }
  return 0;
}

void* myfunc(void* arg) {
  int socket_fd = *((int*)arg);
  
  std::cout << "recv thread start" << std::endl;
  while (true) {
    char buff[250] = { 0 };
    int res = ::recv(socket_fd, buff, 250, 0);
    if (res > 0) {
      std::cout << "recv data: " << buff << std::endl;
    } else if (res == 0) {
      std::cout << "client closed!" << std::endl;
      break;
    } else {
      std::cout << "recv error: " << errno << ": " << strerror(errno) << std::endl;
      if (res == EAGAIN) {
        continue;
      }
    }
  }
  ::close(socket_fd);
  std::cout << "close socket: " << socket_fd << std::endl;
  return 0;
}

int main(int argc, char** argv) {
  // 创建socket描述符
  //
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(8090);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  int res = bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr));

  if (res < 0) {
    std::cout << "socket server bind error!" << std::endl;
    return -1;
  }

  res = listen(socket_fd, 10);
  if (res < 0) {
    std::cout << "socket server listen error!" << std::endl;
    return -1;
  }

  pthread_t thread_id;
  if (pthread_create(&thread_id, NULL, func, &socket_fd) < 0) {
    std::cout << "socket server thread create error!" << std::endl;
    return -1;
  }

  std::cout << "serve listening on: 0.0.0.0:8090" << std::endl;

  void* status;
  pthread_join(thread_id, &status);

  return 0;
}
