#include <iostream>
#include <algorithm>
#include "avl.hpp"

// template class public accessor methods
int AVL::Height() const
{
   if ( !root ) return -1;
   return static_cast<Node*>(root)->height;
}

void AVL::Insert(int key)
{
   root = insert(static_cast<Node*>(root), key);
}

void AVL::Remove(int key)
{
   root = remove(static_cast<Node*>(root), key);
}

void AVL::Deserialize(std::istringstream& isstr)
{
   root = deserialize(isstr, static_cast<Node*>(root));
}

void AVL::Deserialize(std::ifstream& ifstr)
{
   root = deserialize(ifstr, static_cast<Node*>(root));
}

// template class private methods
int AVL::h(const Node* node) const
{
   if ( !node ) return -1;
   return node->height;
}

int AVL::bf(const Node* node) const
{
   if ( !node ) return 0;
   return h(static_cast<Node*>(node->left)) - h(static_cast<Node*>(node->right));
}

AVL::Node* AVL::insert(Node* p, int key)
{
   if ( !p ) return new Node(key);

   if (key < p->key) p->left = insert(static_cast<Node*>(p->left), key);
   else if (key > p->key) p->right = insert(static_cast<Node*>(p->right), key);
   else return p;

   p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
   p->bal_no = bf(p);

   // Left Left Case
   if (p->bal_no > 1 && static_cast<Node*>(p->left)->bal_no > 0)
      return rotate_right(p);

   // Right Right Case
   if (p->bal_no < -1 && static_cast<Node*>(p->right)->bal_no < 0)
      return rotate_left(p);

   // Left Right Case
   if (p->bal_no > 1 && static_cast<Node*>(p->left)->bal_no < 0) {
      p->left = rotate_left(static_cast<Node*>(p->left));
      return rotate_right(p);
   }

   // Right Left Case
   if (p->bal_no < -1 && static_cast<Node*>(p->right)->bal_no > 0) {
      p->right = rotate_right(static_cast<Node*>(p->right));
      return rotate_left(p);
   }

   return p;
}


AVL::Node* AVL::remove(Node* p, int key)
{
   if ( !p ) return p;
   
   if (key < p->key)
      p->left = remove(static_cast<Node*>(p->left), key); 
   else if (key > p->key) 
      p->right = remove(static_cast<Node*>(p->right), key); 
   else { 
      if (p->left == 0) { 
         Node* node = static_cast<Node*>(p->right);
         delete p;
         return node; 
      } else if (p->right == 0) { 
         Node* node = static_cast<Node*>(p->left);
         delete p;
         return node; 
      } else if (p == 0) {
         
      }
      // fielder's choice - in-order successor or predecessor
      // in-order successor (least in right sub-tree)
      Node* node = static_cast<Node*>(minimum(p->right));
      p->key = node->key; 
      p->right = remove(static_cast<Node*>(p->right), node->key); 
      // in-order predecessor (greatest in left sub-tree)
      // Node* node = static_cast<Node*>(maximum(p->left));
      // p->key = node->key; 
      // p->left = remove(static_cast<Node*>p->left, node->key);
   }

   // AVL maintenance section
   // If the tree had only one node then return  
   if ( !p ) return p;
  
   p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
   p->bal_no = bf(p);

   // Left Left Case
   if (p->bal_no > 1 && (static_cast<Node*>(p->left))->bal_no >= 0)
      return rotate_right(p);

   // Right Right Case
   if (p->bal_no < -1 && (static_cast<Node*>(p->right))->bal_no <= 0)
      return rotate_left(p);

   // Left Right Case
   if (p->bal_no > 1 && (static_cast<Node*>(p->left))->bal_no < 0) {
      p->left = rotate_left(static_cast<Node*>(p->left));
      return rotate_right(p);
   }

   // Right Left Case
   if (p->bal_no < -1 && (static_cast<Node*>(p->right))->bal_no > 0) {
      p->right = rotate_right(static_cast<Node*>(p->right));
      return rotate_left(p);
   }   

   return p;
}

AVL::Node* AVL::rotate_left(Node* p)
{
   Node* q = static_cast<Node*>(p->right);
   Node* ql = static_cast<Node*>(q->left);

   q->left = p;
   p->right = ql;

   p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
   q->height = 1 + std::max(h(static_cast<Node*>(q->left)), h(static_cast<Node*>(q->right)));

   p->bal_no = bf(p);
   q->bal_no = bf(q); 

   return q;
}

AVL::Node* AVL::rotate_right(Node* p)
{
   Node* q = static_cast<Node*>(p->left);
   Node* qr = static_cast<Node*>(q->right);

   q->right = p;
   p->left = qr;

   p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
   q->height = 1 + std::max(h(static_cast<Node*>(q->left)), h(static_cast<Node*>(q->right)));

   p->bal_no = bf(p);
   q->bal_no = bf(q); 

   return q;
}


// pre-order
AVL::Node* AVL::deserialize(std::istringstream& isstr, Node* p)
{
   int n;
   isstr >> n;
   if ( n != 0 ) {
      p = new Node(n);
      p->left = deserialize(isstr, static_cast<Node*>(p->left));
      p->right = deserialize(isstr, static_cast<Node*>(p->right));
      p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
      p->bal_no = bf(p);
   }
   return p;
}

// pre-order
AVL::Node* AVL::deserialize(std::ifstream& ifstr, Node* p)
{
   int n;
   ifstr >> n;
   if ( n != 0 ) {
      p = new Node(n);
      p->left = deserialize(ifstr, static_cast<Node*>(p->left));
      p->right = deserialize(ifstr, static_cast<Node*>(p->right));
      p->height = 1 + std::max(h(static_cast<Node*>(p->left)), h(static_cast<Node*>(p->right)));
      p->bal_no = bf(p);
   }
   return p;
}
