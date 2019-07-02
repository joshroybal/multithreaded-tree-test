#ifndef AVL_HPP
#define AVL_HPP

#include "bst.hpp"

class AVL : public BST
{  
   public:
      int Height() const;
      void Insert(int);
      void Remove(int);
      void Deserialize(std::istringstream&);
      void Deserialize(std::ifstream&);
   private:
      struct Node;
      int h(const Node*) const;
      int bf(const Node*) const;
      Node* insert(Node*, int);
      Node* remove(Node*, int);
      Node* rotate_left(Node*);
      Node* rotate_right(Node*);
      Node* deserialize(std::istringstream&, Node*);
      Node* deserialize(std::ifstream&, Node*);
};

struct AVL::Node : public BST::Node
{  
   int height;
   int bal_no;
   Node(int n) : BST::Node(n), height(0), bal_no(0) {}
};

#endif
