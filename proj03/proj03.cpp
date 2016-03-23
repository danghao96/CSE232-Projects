/*
Hao Dang danghao@xserver
2016-02-02
proj03.cpp

This program is going to find out how many narcissistic numbers are in
a giving range.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;

void order_parameters(int &first, int &second){
	/*
	This function is used to excange the value of first and second if 
	the value of first is greater than the value of second.
	Arguments: Two integers first and second passed by reference. 
	Returns: No returns.
	*/
	
	if( first > second ){
		int temp = first;
		first = second;
		second = temp;
	}
}

bool narc_num(int num, int power){
	/*
	This function is used to determain if a number is a narcissistic 
	number of the giving power.
	Arguments: Two integers num and power. 
	Returns: bool value. Return is true if num is a narcissistic number
	of order power. False otherwise.
	*/
	
	long div = num, rem = 0, sum = 0;
	bool result = false;
	
	while( div ){
		// while loop to add up the power of each digit of the number.
		rem = div % 10;	// get the last digit of the number.
		sum += pow(rem, power);		// add up the power of the digit.
		div /= 10;		// divide by 10 to delete the last digit.
	}
	
	if( sum == num ){
		result = true;
	}
	
	return result;
}

int check_range(int first, int last, int power){
	/*
	This function is used to check how many narcissistic numbers are in
	the giving range.
	Arguments: 3 integers first, last and power.
		first, the first number in the range of numbers to be checked.
		last, the last number in the range of numbers to be checked.
		power, the power (order) of the narcissistic number.
	Returns: int value. Return the number of NN's found in the given 
	range.
	*/
	
	int count = 0;
	
	for( int i=first; i <= last; i++ ){
		// loop to check each number in the range.
		if(narc_num(i, power)){
			// call narc_num to check if the number is NN of power.
			count++;
			cout << i << " is a narcissistic number of order:" 
			<< power << endl;
		}
	}
	
	return count;
}

int main(){
	/*
	This function will first read in the number of cases you want to 
	check.
	For each case, this function will read three numbers representing:
		first, beginning of the range
		last end of the range
			Calls order_parameters to get first and last in the correct 
			order (first should be smaller than last).
		The order to be checked
	For each case call check_range.
	At the end of each case, print the number of NN's found in the range.
	*/
	int case_num, first, last, order, nn_count;
	cin >> case_num;
	for( int i = 0; i < case_num; i++ ){
		// loop for each case.
		cin >> first >> last >> order;
		order_parameters(first, last);	
		nn_count = check_range(first, last, order);
		
		cout << "Saw " << nn_count << " order " << order 
		<< " narc numbers in the range " << first << " to " << last 
		<< "\n" << endl;
	}
}

