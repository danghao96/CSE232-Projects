/*
Hao Dang danghao@xserver
2016-01-26
proj02.cpp

This program will calculate the number of primes with in some range.

This program will prompt user input an integer indicate the number of 
test cases. Then, for each test case, the program will prompt user input
two numbers: the value x and the iteration number limit.

For each test case on a separate line, the two input values, x and the 
interation number limit, and the resulting Li(x) value.
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout; using std::endl; using std::cin;
using std::fixed; using std::setw; using std::setprecision;

double factorial(long n){
	/*
	This function calculates and returns the factorial of a number n.
	This function takes a single arugment long n and returns a 
	double, the factorial of n.
	*/
	long i;
	double result = 1;
	
	for(i = 1; i <= n; i++){
		// for loop to calculate the factorial of n iteratively.
		result *= i;
	}
	
	return result;
}

double term(long n){
	/*
	This function will calculate the terms.
	This function takes a single long n and returns a double, the result
	of the summation indicated in the term function section of the 
	series.
	*/
	long k, max;
	double result = 0;
	max = floor((n-1)/2);			// set the max value of the sum.
	
	for(k = 0; k <= max; k++){
		// for loop to calculate the sum.
		result += 1.0/(2.0*k+1.0);
	}
	
	return result;
}

int main(){
	/*
	Main function will call the factorial and term to finish the
	calculation of entire equation.
	*/
	int iters, case_total, i;
	long x, n;
	const double gam = 0.577215664901532;
	
	cin >> case_total;	
	// ask for the number of cases to determain the number of loops.
	
	for(i = 0; i < case_total; i++){
		// This is the main loop to make the calculate continuously.
		double result, sum_result = 0;
		cin >> x >> iters;	// prompt the the x and iters each time.

		for(n = 1; n <= iters; n++){
			// This loop will calculate the sum part of the equation.
			sum_result += ((pow(-1,n-1)*pow(log(x),n)) 
			/ (factorial(n)*pow(2,n-1))) 
			* term(n);
		}
		
		result = gam + log( log(x) ) + sqrt(x)*sum_result;
		// This is the equation.

		cout << fixed << setprecision(3) << "x:" << setw(10) << x 
		<< ", iters:" << setw(3) << iters << ", Li(x)=" << setw(13) 
		<< result << endl;
		// print out the result with appropriate format.
	}
}

