/*
Hao Dang danghao@xserver
2016-02-09
proj04.cpp

*/

#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<string>
using std::string;
#include<vector>
using std::vector;

string fibo_string(string f0, string f1, unsigned int len){
	//This function will generate the fibo string using f0 and f1.
	int size_vec;
	string back_str;
	vector<string> vec_str{f0, f1};
	
	//while loop continues when the length of the last string in the 
	//vector is smaller than the required length.
	while(vec_str.back().size() < len){
		//while loop will generate the fibo string and append it to the
		//end of the vector.
		size_vec = vec_str.size();
		back_str = vec_str[size_vec-1] + vec_str[size_vec-2];
		vec_str.push_back(back_str);
	}
	return back_str.substr(0, len);
}

long find_substring(string fibo, string target){
	//This function will search the target from the fibo string and
	//return the time found.	
	int count = 0;
	int pos = fibo.find(target, 0);	//pre search the target.
	
	//if the target is not found, pos + 1 will be 0, the loop will stop.
	while(pos + 1){
		/* if the target is found in the pre search, the loop will be
		 * executed at least once, and the count will be added up 1.
		 * For each time the target is found in the loop, the count will
		 * be added up 1.
		 */
		pos = fibo.find(target, pos + 1);
		count++;
	}
	
	return count;
}

string lcs(string a_str, string b_str){
	//This function will find the longest common string of a_str and 
	//b_str.
	bool is_cs;
	string sub_str, *s_str, *l_str;
	string longest_cs;
	
	//if statement to find the shortest string and use a pointer point 
	//to it.
	if(a_str.size() < b_str.size()){
		s_str = &a_str;
		l_str = &b_str;
	}else{
		s_str = &b_str;
		l_str = &a_str;
	}
	
	for(unsigned int i = 0; i < (*s_str).size(); i++){
		//for loop used to loop every char in the string as the beginning
		//char of the substring.
		for(unsigned int len = 1; len < ((*s_str).size() - i); len++){
			//for loop to loop all possible length of the substring.
			sub_str = (*s_str).substr(i, len);//take the substring.
			is_cs = find_substring(*l_str, sub_str);
			//test if the substring is the common string of the longer 
			//string, if it is, is_cs will be non-zero integer(true).
			if(is_cs && (len >= longest_cs.size())){
				//if it is common string and longer or equal to the
				//previous longer string.
				longest_cs = sub_str;
			}
		}
	}
	
	return longest_cs;
}

int main () {
  long cases, start, finish, length;
  string f0, f1, target, f0f1_str;
  cin >> cases;
  for (int i=0; i < cases; i++){
    cin >> f0 >> f1 >> length >> start >> finish >> target;
    f0f1_str = fibo_string(f0,f1,length);

    // print the substring requested
    cout <<"Substring from "<< start<< " to " << finish << " is:"
	 << f0f1_str.substr(start,finish-start+1)<<endl;

    // print the cnt of the target in the fibo_string
    cout <<  "Found target "<< target << " " << find_substring(f0f1_str, target)
	 << " times" <<endl;

    // print the longest common substring of the fibo and reversed fibo string
    string f1f0_str = fibo_string(f1,f0,length);
    cout << "LCS of " << f0 << "," << f1
	 <<" fibo and " << f1 << ","<< f0
	 <<" fibo is:" << lcs(f0f1_str, f1f0_str) << endl;

  }
}
