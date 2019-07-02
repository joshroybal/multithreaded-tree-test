// It would seem that one of the keys to the successful use of multithreading
// test applications is locking down the random number generator from any
// potential collisions. 6-28-2019
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <pthread.h>
#include "avl.hpp"

pthread_mutex_t lock;

const int NT = 1000;
const int NN = 1000;
int arr1[NN];
int arr2[NN];

int random(int);
void initialize(int[], int);
void shuffle(int[], int);
void perfect_shuffle(int[], int);
void displayResults(int, int, int, int, float);
void *foo(void *);
void *bar(void *);

int main()
{
   pthread_t thread1, thread2;

   initialize(arr1, NN);
   initialize(arr2, NN);
   pthread_create(&thread1, NULL, bar, NULL);
   pthread_create(&thread2, NULL, foo, NULL);
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL); 
   std::cout << "\nlog2(" << NN << ") = " << log2(NN) << std::endl;
   std::cout << "1.44*log2(" << NN << ") = " << 1.44F*log2(NN) << std::endl;   
   return 0;
}

int random(int n)
{
   return n * (rand() / 2147483647.0F);
}

void initialize(int arr[], int n)
{
   for (int i = 0; i < n; i++) arr[i] = i+1;
}

void shuffle(int arr[], int n)
{
   for (int i = 0; i < n; i++) {
      int idx = random(n);
      if (idx != i) {
         int tmp = arr[i];
         arr[i] = arr[idx];
         arr[idx] = tmp;
      }
   }
}

void perfect_shuffle(int arr[], int n)
{
   int tmp[n];

   for (int i = 0; i < n; i += 2) {
      tmp[i] = arr[i/2+n/2];
      tmp[i+1] = arr[i/2];
   }
   for (int i = 0; i < n; i++)
      arr[i] = tmp[i];
}

void displayResults(int nt, int nn, int min, int max, float avg)
{
   std::cout << "no. of trees = " << nt << std::endl;
   std::cout << "no. of nodes per tree = " << nn << std::endl;
   std::cout << "minimum = " << min << std::endl;
   std::cout << "maximum = " << max << std::endl;
   std::cout << "average = " << avg << std::endl;
   std::cout << "C = " << avg / log2(nn) << std::endl;
}

void *foo(void *args)
{
   int max = 0, min = NN + 1, s = 0;

   for (int i = 0; i < NT; i++) {
      initialize(arr2, NN);
      // critical section begin
      pthread_mutex_lock(&lock);
      srand(i+1);
      shuffle(arr2, NN);
      pthread_mutex_unlock(&lock);
      // critical section end
      BST* bst = new BST();
      for (int j = 0; j < NN; j++) bst->Insert(arr2[j]);
      int h = bst->Height();
      delete bst;
      if (h < min) min = h;
      if (h > max) max = h;
      s += h;
   }
   float avg = static_cast<float>(s) / static_cast<float>(NT);
   std::cout << "\nbinary search tree results" << std::endl;
   displayResults(NT, NN, min, max, avg);
}

void *bar(void *args)
{
   int max = 0, min = NN + 1, s = 0;

   for (int i = 0; i < NT; i++) {
      initialize(arr1, NN);
      // critical section begin
      pthread_mutex_lock(&lock);
      srand(i+1);
      shuffle(arr1, NN);
      pthread_mutex_unlock(&lock);
      // critical section end
      AVL* avl = new AVL();
      for (int j = 0; j < NN; j++) avl->Insert(arr1[j]);
      int h = avl->Height();
      delete avl;
      if (h < min) min = h;
      if (h > max) max = h;
      s += h;
   }
   float avg = static_cast<float>(s) / static_cast<float>(NT);
   std::cout << "\nAVL balanced binary search tree results" << std::endl;
   displayResults(NT, NN, min, max, avg);
}
