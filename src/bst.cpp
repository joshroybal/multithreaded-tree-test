#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "bst.hpp"

// class destructor
BST::~BST()
{
   destroy(root);
}

// template class public accessor methods

int BST::Height() const
{
   return h(root);
}

int BST::Size() const
{
   return size(root);
}

int BST::Minimum() const
{
   int z = 0;
   if (root) {
      Node* node = minimum(root);
      if (node) z = node->key;
   }
   return z;
}

int BST::Maximum() const
{
   int z = 0;
   if (root) {
      Node* node = maximum(root);
      if (node) z = node->key;
   }
   return z;
}

void BST::Search(int key)
{
   Node* target = search(root, key);
   if ( target ) std::cout << "key = " << target->key << std::endl;
   else std::cout << "node = " << target << std::endl;
}

void BST::Insert(int n)
{
   insert(root, n);
}

void BST::Remove(int n)
{
   root = remove(root, n);
}

void BST::PreOrder() const
{
   preorder(root);
   std::cout << std::endl;
}

void BST::InOrder() const
{
   inorder(root);
   std::cout << std::endl;
}

void BST::PostOrder() const
{
   postorder(root);
   std::cout << std::endl;
}

void BST::Serialize(std::ostringstream& osstr) const
{
   serialize(osstr, root);
}

void BST::Serialize(std::ofstream& ofstr) const
{
   serialize(ofstr, root);
}

void BST::Deserialize(std::istringstream& isstr)
{
   root = deserialize(isstr, root);
}

void BST::Deserialize(std::ifstream& ifstr)
{
   root = deserialize(ifstr, root);
}

// template class private methods
void BST::destroy(Node*& p)
{
   if ( !p ) return;
   destroy(p->left);
   destroy(p->right);
   delete p;
}

int BST::h(const Node* p) const
{
   if ( !p ) return -1;

   int hl = h(p->left);
   int hr = h(p->right);

   if ( hl > hr ) return 1 + hl;
   else return 1 + hr;
}

int BST::size(const Node* p) const
{
   if ( !p ) return 0;
   else return 1 + size(p->left) + size(p->right);
}

BST::Node* BST::search(Node* p, int key)
{
   if ( !p ) return p;

   if ( key < p->key )
      return search(p->left, key);
   else if ( key > p->key)
      return search(p->right, key);
   else
      return p;
}

void BST::insert(Node*& p, int key)
{
   if ( !p ) {
     p = new Node(key);
     return;
   }

   if (key < p->key) insert(p->left, key);
   else if (key > p->key) insert(p->right, key);
   else return;
}

BST::Node* BST::remove(Node* p, int key)
{
   if (p == 0) return p;

   if (key < p->key)
      p->left = remove(p->left, key);
   else if (key > p->key)
      p->right = remove(p->right, key);
   else {
      if (p->left == 0) {
         Node* leaf = p->right;
         delete p;
         return leaf;
      } else if (p->right == NULL) {
         Node* leaf = p->left;
         delete p;
         return leaf;
      }
      Node* leaf = minimum(p->right);
      p->key = leaf->key;
      p->right = remove(p->right, leaf->key);
   }
   return p;
}

BST::Node* BST::minimum(Node* p) const
{
   if ( p->left == 0 ) return p;
   return minimum(p->left);
}

BST::Node* BST::maximum(Node* p) const
{
   if ( p->right == 0 ) return p;
   return maximum(p->right);
}

void BST::preorder(const Node* p) const
{
   if ( !p ) return;
   std::cout << ' ' << p->key;
   preorder(p->left);
   preorder(p->right);
}

void BST::inorder(const Node* p) const
{
   if ( !p ) return;
   inorder(p->left);
   std::cout << ' ' << p->key;
   inorder(p->right);
}

void BST::postorder(const Node* p) const
{
   if ( !p ) return;
   postorder(p->left);
   postorder(p->right);
   std::cout << ' ' << p->key;
}

// pre-order
void BST::serialize(std::ostringstream& osstr, const Node* p) const
{
   if ( !p ) {
      osstr << ' ' << 0;
      return;
   }
   osstr << ' ' << p->key;
   serialize(osstr, p->left);
   serialize(osstr, p->right);
}

// pre-order
void BST::serialize(std::ofstream& ofstr, const Node* p) const
{
   if ( !p ) {
      ofstr << 0 << std::endl;
      return;
   }
   ofstr << p->key << std::endl;
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);
}

// pre-order
BST::Node* BST::deserialize(std::istringstream& isstr, Node* p)
{
   int n;
   isstr >> n;
   if ( n != 0 ) {
      p = new Node(n);
      p->left = deserialize(isstr, p->left);
      p->right = deserialize(isstr, p->right);
   }
   return p;
}

// pre-order
BST::Node* BST::deserialize(std::ifstream& ifstr, Node* p)
{
   int n;
   ifstr >> n;
   if ( n != 0 ) {
      p = new Node(n);
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
   }
   return p;
}
