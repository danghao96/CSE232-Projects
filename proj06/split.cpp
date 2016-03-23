/*
Hao Dang danghao@xserver
2016-03-03
split.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

void split(string line, vector<string>&words, string good_chars){
	//This function finds words in the line that consist of good_chars.
	//It will read in a line and a string good_chars, then, it will
	//store those words in a vector words.
	size_t pos_good = 0, pos_bad = 0;
	while(true){
		//while loop to continuously look for good characters and bad
		//characters, then, get the string between good character and
		//bad character which means that string is the word we are
		//looking for. 
		string word, lword;
		pos_good = line.find_first_of(good_chars, pos_bad);
		pos_bad = line.find_first_not_of(good_chars, pos_good+1);
		if(pos_good == string::npos){
			//If good character is not found, which means all good words
			//are found. Break the loop.
			break;
		}
		word = line.substr(pos_good, pos_bad - pos_good);
		for(char ch : word){
			lword += tolower(ch);
		}
		words.push_back(lword);
	}
}
