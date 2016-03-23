/*
Hao Dang danghao@xserver
2016-03-03
functions-06.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string; using std::to_string;
#include <map>
using std::map;
#include <utility>
using std::pair;
#include <vector>
using std::vector;

#include "split.h"

pair<long, long> split_to_pair(string str_pair, char sep = ':'){
	//This function splits string of two integers seperated by sep into
	//a pair of two integers.
	//It returns the pair.
	long first, second;
	size_t sep_pos;
	sep_pos = str_pair.find(sep);		//get the position of sep.
	first = stol(str_pair.substr(0));			//get the first integer.
	second = stol(str_pair.substr(sep_pos+1));	//get the second integer.
	return {first, second};
}

void process_file(string filename, map<string, 
vector<pair<long,long>>>& encode_map, 
map<pair<long,long>, string>& decode_map){
	//This function processes the file. It will read the file and build
	//encode_map and decode_map with the file.
	static string good_chars 
	= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'";
	ifstream infile(filename);
	pair<long, long> value;
	long l_num = 0;
	
	while(!infile.eof()){
		//while loop to read each line from the file.
		string line;
		vector<string> words;
		getline(infile, line);
		split(line, words, good_chars);
		long w_num = 0;
		//call split function to split the line into words.
		for(string word : words){
			//for loop to read each word from the word list and get the
			//line number and word number(store in value) of that word. 
			//Then, store this word in encode_map and store the value in
			//decode_map.
			value = {l_num, w_num};
			encode_map[word].push_back(value);
			decode_map[value] = word;
			w_num++;
		}
		l_num++;
	}
}

string encode(string to_encode, map<string, 
vector<pair<long,long>>>& encode_map){
	//This function uses encode_map to encode the word to_encode.
	//It returns encoded string.
	string result;
	if(encode_map.find(to_encode) != encode_map.end()){
		//If the word to_encode is existed in the encode_map, find out
		//the corresponding value, and convert it to string in the form
		//"number:number".
		result = to_string(encode_map[to_encode][0].first) + ":" 
		+ to_string(encode_map[to_encode][0].second);
	}
	return result;
}

string decode(string to_decode, map<pair<long,long>, 
string>& decode_map){
	//This function uses decode_map to decode the string to_decode.
	//It returns decoded word.
	string result;
	pair<long, long> pair = split_to_pair(to_decode);
	//call split_to_pair to split to_decode into a pair of two integers.
	result = decode_map[pair];
	return result;
}
