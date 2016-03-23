/*
Hao Dang danghao@xserver
2016-02-18
proj05.cpp

This function set provideds 4 functions.
Function filter_string will filter the inputed string.
Function read_key will read one line from the file and store the integer
from the line in a vector.
Function encode will encode the inputed string.
Function decode will decode the inputed integers saved in a string.
*/

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
using std::to_string;
#include <sstream>
using std::istringstream;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <random>
using std::mt19937_64;
using std::uniform_int_distribution;

void str_to_vec(string str, vector<long> &v){
	//This function reads integers from string and save them in vector.
	//This function reads in a string and a vector passed by reference.
	long temp;
	size_t pos;
	while(str.size()){
		//While loop repeatedly extract integers from the string and
		//store them in the vector, then, it will rease the integer from
		//the string.
		temp = stol(str, &pos);
		v.push_back(temp);
		str.erase(0, pos);
	}
}

string filter_string(string s){
	//This function filters the string. It will return a string that 
	//containing all the alphabetic character in lower case form.
	//Non alphabetic characters will be removed.
	string result;
	for(char c : s){
		//Repeatedly test each characters in the string and change the
		//alphabetic characters to lower and save those characters in
		//the result string.
		if(isalpha(c)){
			result += tolower(c);
		}
	}
	return result;
}

void read_key(ifstream &in_file, vector<long> &shift_key){
	//This function reads a single line from the provided ifstream
	//in_file and store the integer from the readed line into provided
	//vector.

	string str;
	getline(in_file, str);
	str_to_vec(str, shift_key);
	
	/* NOT SUCCEED, JUST A THOUGHT.
	string temp_str;
	long temp_l;
	char sep = ' ';
	while(temp_str){
		getline(in_file, temp_str, sep);
		temp_l = stol(temp_str);
		shift_key.push_back(temp_l);
	}
	*/
	
	/*
	string str;
	getline(in_file, str);
	istringstream iss(str);
	int n = 0;
	while(iss >> n){
		shift_key.push_back(n);
	}
	*/
}

string encode(string to_encode, vector<long>& shifts, mt19937_64 &reng, 
uniform_int_distribution<long>& dist){
	//This function encode the string with the vector shifts as the key.
	//It will take a string to encode, a vector as the key, and a random
	//number engine. It will return the encdede form of the string, which
	//is a list of integers that saved in a string.
	string filtered = filter_string(to_encode);//filter the input string.
	int temp, rand;
	string result;
	vector<long> str_indexed;
	
	for(unsigned int i = 0; i < filtered.size(); i++){
		//for loop will repeatedly encode each character of the string.
		rand = dist(reng);
		temp = (filtered[i]-'a') + shifts[i%shifts.size()] + 26*rand;
		result += to_string(temp) + " ";
	}
	
	return result;
}

string decode(string to_decode, vector<long>& shifts){
	//This function will decoded a list of entegers saved in a string.
	//If will take a string which is a list of integer that seperated by
	//space to decode, and a vector as a key. It will return a string as
	//the decoded string.
	vector<long> str_indexed;
	string result;
	str_to_vec(to_decode, str_indexed);//take out the value from string.
	
	for(unsigned int i = 0; i < str_indexed.size(); i++){
		//for loop will repeatedly encode each integer from the vector 
		//and save the result in a string.
		str_indexed[i] = (str_indexed[i] - shifts[i%shifts.size()]) % 26;
		result += str_indexed[i] + 'a';
	}
	
	return result;
}
