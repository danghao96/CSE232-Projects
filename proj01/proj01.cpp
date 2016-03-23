/*
Hao Dang danghao@xserver
2016-01-23
proj01.cpp

* This project is used to calculate the predicted population size based on
* the initial population and some other parameters.
* This program will ask for 4 parameters:
* 	the initial population size(p0), 
* 	the carrying capacity (K), 
* 	the time (t), 
* 	the Maltusian parameter (r).
* This program will return 2 values calculated by 2 formulas:
* 	the unrestricted population growth prediction.
* 	the restricted population growth prediction.
*/

#include <iostream> 	// iostream to receive input and general output.
#include <cmath>		// cmath to enable math calculation
#include <iomanip>		// iomanip to enable fixed and setprecision.

using std::cout; using std::cin; using std::endl;
using std::fixed; using std::setprecision; 

int main(){
	cout << "Give me P0, r, K, t (space separated):";
	double pt_unres, pt_res, p0, r, k, t;	// initialize the variables.
	cin >> p0 >> r >> k >> t;				// prompt user for inputs.
	
	// calculate the unrestricted population growth prediction.
	pt_unres = p0 * exp(r * t);
	
	// calculate the restricted population growth prediction.
	pt_res = (k * p0 * exp(r * t))/(k + p0 * (exp(r * t)-1));
	
	// print out the results.
	cout << fixed << setprecision(4) << "\nUnrestricted population is:" 
	<< pt_unres	<< "\nThe restricted population is:" << pt_res << endl;
}
