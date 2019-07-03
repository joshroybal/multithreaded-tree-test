// BST balanced binary search tree
// recursive implementations
#ifndef BST_HPP
#define BST_HPP

#include <sstream>
#include <fstream>

class BST
{
   public:
      BST() : root(0) {}
      virtual ~BST();
      virtual int Height() const;
      int Size() const;
      int Minimum() const;
      int Maximum() const;
      void Search(int);
      virtual void Insert(int);
      virtual void Remove(int);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void Serialize(std::ostringstream&) const;
      void Serialize(std::ofstream&) const;
      virtual void Deserialize(std::istringstream&);
      virtual void Deserialize(std::ifstream&);
   protected:
      struct Node;
      Node* root;
      void destroy(Node*&);
      int h(const Node*) const;
      int size(const Node*) const;
      Node* search(Node*, int);
      void insert(Node*&, int);
      Node* remove(Node*, int);
      Node* minimum(Node*) const;
      Node* maximum(Node*) const;
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void serialize(std::ostringstream&, const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::istringstream&, Node*);
      Node* deserialize(std::ifstream&, Node*);
};

struct BST::Node
{  
   int key;
   Node* left;
   Node* right;
   Node(int n) : key(n), left(0), right(0) {}
   virtual ~Node() {}
};

#endif
