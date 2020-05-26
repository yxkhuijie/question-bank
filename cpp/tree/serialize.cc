#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>

struct Node {
  char data;
  Node* left;
  Node* right;
  Node() : data(0), left(NULL), right(NULL) {}
  Node(char d) : data(d), left(NULL), right(NULL) {}
};

void create_tree(struct Node* A) {
  Node* B = new Node('B');
  Node* C = new Node('C');
  Node* D = new Node('D');
  Node* E = new Node('E');
  Node* F = new Node('F');
  Node* G = new Node('G');
  Node* H = new Node('H');
  Node* K = new Node('K');
  A->left = B;
  B->right = C;
  C->left = D;
  A->right = E;
  E->right = F;
  F->left = G;
  G->left = H;
  G->right = K;
}

void preorder(struct Node* node) {
  if (node == NULL) return;
  std::cout << node->data;
  preorder(node->left);
  preorder(node->right);
}

void preorder_serialize(struct Node* node, std::string* str) {
  if (node == NULL) {
    str->append("# ");
    return;
  } else {
    char c[3];
    c[0] = node->data;
    c[1] = ' ';
    c[2] = '\0';
    str->append(c);
  }
  preorder_serialize(node->left, str);
  preorder_serialize(node->right, str);
}

void split(const std::string& str, std::vector<std::string>* v, const std::string& p) {
  if (str.empty() || p.empty()) return;
  std::string s = str; 
  std::size_t index = s.find(p);
  while (index != std::string::npos) {
    v->push_back(s.substr(0, index));
    s = s.substr(index + p.length()); 
    index = s.find(p);
  }
  if (!s.empty()) v->push_back(s);
}

Node* deserialize(std::queue<std::string> q) {
  std::string s = q.front();
  q.pop();
  std::cout << "s: " << s << std::endl;
  if (s == "#") return NULL;
  std::cout << "****: " << s << std::endl;
  Node* res = new Node;
  res->data = s.at(0);
  res->left = deserialize(q);
  res->right = deserialize(q);
  std::cout << "****" << std::endl;
  return res;
}

Node* preorder_deserialize(const std::string& str) {
  std::vector<std::string> v;
  split(str, &v, " ");
  std::queue<std::string> q;
  std::vector<std::string>::iterator it;
  for(it = v.begin(); it != v.end(); ++it) {
    q.push(*it);
    std::cout << *it;
  }
  std::cout << std::endl;
  Node* res = deserialize(q);
  if (res == NULL) {
    std::cout << "++++++" << std::endl;
  }
  preorder(res);
  return res;
}

int main(int argc, char** argv) {
  Node node('A');
  create_tree(&node);
  std::string str;
  preorder_serialize(&node, &str);
  std::cout << str << std::endl;
  preorder_deserialize(str);
}

