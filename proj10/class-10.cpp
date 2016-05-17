/*
Hao Dang danghao@xserver
Sec 007 | Proj 10
2016-04-13
class-10.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <algorithm>
using std::copy;

#include "class-10.h"

void TextBuffer::grow(){
	//This function will grow the buffer too times as before.
	
	//Build a temporary buffer with double capacity as origional buffer.
	size_t capacity = 2 * capacity_;
	char *buf = new char[capacity];
	
	//Copy characters before cursor of old buffer to temporary buffer.
	copy(buf_, buf_ + cursor_, buf);
	
	//Copy characters after back of old buffer to temporary buffer.
	size_t back = capacity - (capacity_ - back_);
	copy(buf_ + back_ + 1, buf_ + capacity_, buf + back + 1);
	
	//swap temporary buffer and origional buffer.
	capacity_ = capacity;
	back_ = back;
	std::swap(buf, buf_);
	
	delete [] buf;		//delete temporary buffer.
}

void TextBuffer::swap(TextBuffer& tb){
	//This function swap two TextBuffer.
	std::swap(this->buf_, tb.buf_);
	std::swap(this->size_, tb.size_);
	std::swap(this->capacity_, tb.capacity_);
	std::swap(this->cursor_, tb.cursor_);
	std::swap(this->back_, tb.back_);
}

TextBuffer::TextBuffer(size_t s){
	//This is a constructor with size. This will construct a TextBuffer
	//with the capacity equal to given size.
	size_ = 0;
	capacity_ = s;
	cursor_ = 0;
	back_ = s - 1;
	buf_ = new char[capacity_];
}

TextBuffer::TextBuffer(TextBuffer& tb){
	//This is a copy constructor. Copy everything from given buffer.
	
	//copy everything from tb to this.
	size_ = tb.size_;
	capacity_ = tb.capacity_;
	cursor_ = tb.cursor_;
	back_ = tb.back_;
	
	buf_ = new char[capacity_];
	copy(tb.buf_, tb.buf_ + tb.capacity_, buf_);
}

TextBuffer& TextBuffer::operator=(TextBuffer tb){
	//This is a copy constructor. Copy everything from given buffer.
	//This will also return the constructed TextBuffer.
	
	//copy everything from tb to this.
	size_ = tb.size_;
	capacity_ = tb.capacity_;
	cursor_ = tb.cursor_;
	back_ = tb.back_;
	
	buf_ = new char[capacity_];	
	copy(tb.buf_, tb.buf_ + tb.capacity_, buf_);	//copy buf_
	
	this->swap(tb);
	
	return *this;
}

TextBuffer::~TextBuffer(){
	//This is a destructor.
	delete [] buf_;
}

bool TextBuffer::isfull(){
	//Test if the buffer is full. return true if it is full. otherwise
	//return false.
	if (cursor_ == back_) {
		return true;
	} else {
		return false;
	}
}

bool TextBuffer::isempty(){
	//Test if the buffer is empty. return true if it is full. otherwise
	//return false.
	if (size_) {
		return true;
	} else {
		return false;
	}
}

void TextBuffer::insert(char c){
	//This function will do the insertion to the TextBuffer.
	if (isfull()) {
		//if the buffer is full, grow it.
		grow();
	}
	size_++;
	buf_[cursor_] = c;
	cursor_++;
}

bool TextBuffer::del(){
	//This function will do the deletion to the TextBuffer.
	//This function return if the deletion is successful.
	bool result = false;
	if (cursor_) {
		//only delete when cursor is not at the first position.
		cursor_--;
		size_--;
		result = true;
	}
	return result;
}

bool TextBuffer::left(){
	//This function will move the cursor one position left.
	//This function return if the move is successful.
	bool result = false;
	if (cursor_) {
		//only move the cursor left when it is not at the first position.
		cursor_--;
		buf_[back_] = buf_[cursor_];
		back_--;
		result = true;
	}
	return result;
}

bool TextBuffer::right(){
	//This function will move the cursor one position right.
	//This function return if the move is successful.
	bool result = false;
	if (back_ != capacity_ - 1) {
		//only move the cursor right when it is not at the last position.
		buf_[cursor_] = buf_[back_ + 1];
		cursor_++;
		back_++;
		result = true;
	}
	return result;
}

ostream& operator<<(ostream& out, TextBuffer &tb){
	//This is the output operator method. It will output the TextBuffer.
	out << "sz:" << tb.size_ << ",cap:" << tb.capacity_ << ",cur:" 
	<< tb.cursor_ << ",bk:" << tb.back_ << endl;
	
	//output content of buf_.
	for(size_t i = 0; i < tb.capacity_; i++){
		out << tb.buf_[i] << ",";
	}
	out << endl;
	
	//output text in buffer.
	for(size_t i = 0; i < tb.cursor_; i++){
		out << tb.buf_[i];
	}
	out << "|";
	for(size_t i = tb.back_ + 1; i < tb.capacity_; i++){
		out << tb.buf_[i];
	}
	out << endl;

	return out;
}
