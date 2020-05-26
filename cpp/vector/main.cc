#include <iostream>
#include <vector>

class Node {
 public:
  Node() : data(0) {
    std::cout << "default constructor" << std::endl;
  }
  explicit Node(int d) : data(d) {
    std::cout << "constructor" << std::endl;
  }
  Node(const Node& node) {
    std::cout << "copy constructor" << std::endl;
  }
  ~Node() {
    std::cout << "destructor" << std::endl;
  }
 private:
  int data;
};

void print(const std::vector<Node>& data, const std::string& str) {
  std::cout << str << ": vector size: " << data.size() << ", capacity: " << data.capacity() << std::endl;
}

int main(int argc, char** argv) {
  std::vector<Node> data;
  Node node(0);
  for (int i = 0; i < 2; i++) {
    data.push_back(node);
    print(data, "push");
  }

  print(data, "resize begin");
  data.resize(5);
  print(data, "resize end");

  print(data, "reserve begin");
  data.reserve(8);
  print(data, "reserve end");
}

