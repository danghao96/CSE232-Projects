#include<iostream>
using std::cout; using std::endl;

#include "class-11.h"


int main (){
  RBag<long> b;
  b.append_front(10);
  long rcpt = b.append_front(30);
  b.append_front(20);
  Node<long>* n = new Node<long>(40,100);
  b.append_front(n);
  
  
  cout << b << endl;
  auto ptr = b.find(rcpt);

  cout << *ptr << endl;
  cout << b << endl;

  ptr = b.find(1);
  
  if (ptr == nullptr)
    cout << "Not found" << endl;
  else
    cout << *ptr << endl;

  b.remove(rcpt);
  cout << b << endl;
  
}
  
