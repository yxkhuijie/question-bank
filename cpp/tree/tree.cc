#include <iostream>
#include <stack>

struct Node {
  char data;
  Node* left;
  Node* right;
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

void preorder_stack(struct Node* node) {
  if (node == NULL) return;
  std::stack<Node*> n;
  n.push(node);
  while(!n.empty()) {
    Node* tmp = n.top();
    n.pop();
    std::cout << tmp->data;
    if (tmp->right != NULL) n.push(tmp->right);
    if (tmp->left != NULL) n.push(tmp->left);
  }
}

void midorder(struct Node* node) {
  if (node == NULL) return;
  midorder(node->left);
  std::cout << node->data;
  midorder(node->right);
}

void midorder_stack(struct Node* node) {
  if (node == NULL) return;
  std::stack<Node*> n;

  Node* tmp = node;
  while (tmp || !n.empty()) {
    while (tmp) {
      n.push(tmp);
      tmp = tmp->left;
    }
    tmp = n.top();
    n.pop();
    std::cout << tmp->data;
    tmp = tmp->right;
  }
}

void postorder(struct Node* node) {
  if (node == NULL) return;
  postorder(node->left);
  postorder(node->right);
  std::cout << node->data;
}

void postorder_stack(struct Node* node) {
  if (node == NULL) return;
  std::stack<Node*> n;
  n.push(node);
  n.push(node);
  Node* tmp = node;
  while (!n.empty()) {
    tmp = n.top();
    n.pop();
    if (!n.empty() && tmp == n.top()) {
      if (tmp->right) {
        n.push(tmp->right);
        n.push(tmp->right);
      }

      if (tmp->left) {
        n.push(tmp->left);
        n.push(tmp->left);
      }
    } else {
      std::cout << tmp->data;
    }
  }
}

int main(int argc, char** argv) {
  Node node('A');
  create_tree(&node);
  preorder(&node);
  std::cout << std::endl;

  preorder_stack(&node);
  std::cout << std::endl;

  midorder(&node);
  std::cout << std::endl;

  midorder_stack(&node);
  std::cout << std::endl;

  postorder(&node);
  std::cout << std::endl;

  postorder_stack(&node);
  std::cout << std::endl;
}

