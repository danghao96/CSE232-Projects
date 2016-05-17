/*
Hao Dang danghao@xserver
Proj 11 | Sec 007
2016-04-23
class-11.h
*/

#ifndef RECEIPT_BAG
#define RECEIPT_BAG

#include<iostream>
using std::ostream;
#include<random>
using std::mt19937_64; using std::uniform_int_distribution;

// forward declaration
template<typename T>
class RBag;

/*
  Node struct has templated data_ field and an int receipt_ field
  The two-arg constructor fills in the data_ and receipt_ from its args
*/
template <typename T>
struct Node{
public:
  T data_;
  Node* next_;
  int receipt_;

  Node(){
	//Constructor with zero parameter.
	next_ = nullptr;
	receipt_ = 0;
  }
  
  Node (T data, int receipt){
	//Constructor with two parameters.
	data_ = data;
	next_ = nullptr;
	receipt_ = receipt; 
  }
  
  friend ostream& operator<<(ostream& out, Node& n){
	//<< operator for output.
	out << "Receipt: " << n.receipt_ << ", Data: " << n.data_ << endl;
	return out;
  };
  friend class RBag<T>;
};


/*
  RBag class. Has only a head_ to the first Node. Empty list has head_ == nullptr
  Both the random engine and uniform distribution are provided. When a random
  number is required elsewhere in the RBag, call dist_(reng_)
*/

template<typename T>
class RBag{
private:
  Node<T>* head_;
  mt19937_64 reng_;
  uniform_int_distribution<int> dist_;
  
public:
  RBag(){
	//Constructor with zero parameter.
	head_ = nullptr;
  }

  // rule of three
  RBag(const RBag& b){
	//Copy Constructor.
	head_ = new Node<T>((*b.head_).data_, (*b.head_).receipt_);
	//head_ pointer point to a new Node that constructed with the value
	//the same as b.head_;
		
	Node<T>* b_ptr = (*b.head_).next_;
	//Make a pointer points to the second Node in b.
	
	Node<T>* ptr = head_;	//Make a pointer points to the head_;
	
	while(b_ptr != nullptr){
	  //loop through all Node in b.
	  (*ptr).next_ = new Node<T>((*b_ptr).data_, (*b_ptr).receipt_);
	  //construct new Node for each node in b. and append it to this RBag.
	  
	  b_ptr = (*b_ptr).next_;
	  ptr = (*ptr).next_;
	}
	reng_ = b.reng_;
	dist_ = b.dist_;
  }
  
  RBag& operator=(RBag b){
	//=operator, same as copy constructor, return *this.
	head_ = new Node<T>((*b.head_).data_, (*b.head_).receipt_);
	//head_ pointer point to a new Node that constructed with the value
	//the same as b.head_;
	
	Node<T>* b_ptr = (*b.head_).next_;
	//Make a pointer points to the second Node in b.
	
	Node<T>* ptr = head_;	//Make a pointer points to the head_;
	
	while(b_ptr != nullptr){
	  //loop through all Node in b.
	  (*ptr).next_ = new Node<T>((*b_ptr).data_, (*b_ptr).receipt_);
	  //construct new Node for each node in b. and append it to this RBag.
	  
	  b_ptr = (*b_ptr).next_;
	  ptr = (*ptr).next_;
	}
	reng_ = b.reng_;
	dist_ = b.dist_;
	return *this;
  }
  
  ~RBag(){
	//Destructor. This will free all memory occupied by RBag.
	Node<T>* ptr = head_;
	while(ptr != nullptr){
	  //loop through every Node in the RBag.
	  head_ = (*head_).next_;
	  //point the head_ to next_ before it is deleted.
	  delete ptr;	//delete the first Node in RBag now.
	  ptr = head_;	//pointer point to the head_(which is the next_)
	}
  }
  
  // returns nullptr if not found, else returns pointer to the Node
  // and places the found Node at the front of the RBag linked list
  Node<T>* find(long receipt){
	//This will return the pointer point to the Node with given receipt,
	//and move that node to the front of RBag.
	Node<T>* result = head_;//this is the pointer to return.
	
	//this is the pointer points to the previous result.
	Node<T>* prev = head_;
	
	int i = 0;
	while(result != nullptr){
	  //loop through every Node.
	  if((*result).receipt_ == receipt){
		//if found, break the loop. Now, the result should point to the
		//correct Node.
		break;
	  } else {
		//otherwise, result points to next, prev points to next.
		if(i){ prev = (*prev).next_; }
		result = (*result).next_;
	  }
	  i++;
	}
	
	if(result != nullptr){
	  //if result is not nullptr, that means the Node is found.
	  if(head_ != result){
		//if it is not the head_, put it to head.
		(*prev).next_ = (*result).next_;
		(*result).next_ = head_;
		head_ = result;
	  }
	}
	return result;
  }

  // Make a new Node using dat and generating a random number receipt
  // then append to the front of the RBag linked list
  long append_front(T dat){
	//This will make a new Node with given data and append it to the 
	//front of RBag.
	long receipt = dist_(reng_);  //generate random number for receipt.
    Node<T>* n = new Node<T>(dat, receipt);	//make new Node.
    
    if (head_ != nullptr) { (*n).next_ = head_; }
    head_ = n;
    
	return receipt;
  }
  
  // Node already exists, append to the front of the RBag linked list
  long append_front(Node<T>* n){
	//This will append the given node to the front of RBag.
    if (head_ != nullptr) { (*n).next_ = head_; }
    head_ = n;
    
	return (*n).receipt_;
  }

  // if Node is not found, return false, else delete the found Node
  // and return true
  bool remove(long receipt){
	//This will remove a the node with the given receipt and free the
	//memory it used.
	Node<T> *ptr = head_;	//this pointer is point to the Node to remove.
	Node<T> *prev = head_;	//this points to the prev Node of ptr.
	int i = 0;
	while(ptr != nullptr){
	  //loop through every Node.
		
	  if((*ptr).receipt_ == receipt){
		//if found
		if(head_ == ptr){
		  //if the Node to delete is the first Node of RBag, point head_
		  //to next Node.
		  head_ = (*ptr).next_;
		} else {
		  //point the next_ of prev Node to next of current Node.
		  (*prev).next_ = (*ptr).next_;
		}
		delete ptr;  //free the memory.
		return true;
	  } else {
		//ptr point to next_, prev point to next_.
		if(i){ prev = (*prev).next_; }
		ptr = (*ptr).next_;
	  }
	  i++;
	}
	return false;
  }
  
  friend ostream& operator<<(ostream& out, RBag& b){
	//This will output all Node in RBag. This will use the operator<< of
	//Node.
	Node<T> *ptr = b.head_;
	while(ptr != nullptr){
	  //loop through all Node in RBag to output.
	  out << (*ptr) << endl;
	  ptr = (*ptr).next_;
	}
	return out;
  };
};
    
#endif
