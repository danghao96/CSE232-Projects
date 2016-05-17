/*
Hao Dang danghao@xserver
2016-03-23
class-08.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream; using std::ofstream;
#include <sstream>
using std::istringstream;
#include <iomanip>
using std::setw;
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "class-08.h"

Image::Image(string f_name){
	//This is a constructor for Image. This function will accept a string
	//works as the name of pgm file. Than, it will open the file and
	//construct the image type instance for the input image file.
	ifstream infile(f_name);
	string line, num_str;
	long temp;
	bool size_get = false, grey_get = false;
	while(getline(infile, line)){
		//while loop will read all line from file in.
		if(line.front() != '#' && line.front() != 'P'){
			//if statement ignores those lines that start with # or P. 
			istringstream iss(line);
			if(!size_get){
				//if the size of image is not got, readin the size.
				iss >> width_ >> height_;
				size_get = true;
			}else if(!grey_get){
				//if the max grey value of image is not got, readin it.
				iss >> max_val_;
				grey_get = true;
				//at this step, both size and grey should be got,
				//continue the loop.
				break;
			}
		}
	}
	
	while(getline(infile, line)){
		num_str += line + " ";
	}
	
	istringstream num_stream(num_str);	//convert string to stream.
	for(long y = 0; y < height_; y++){
		vector<long> row;	//initialize the row vector for a new row.
		for(long x = 0; x < width_; x++){
			//double loop make the table.
			num_stream >> temp;	//get the long value from stream.
			row.push_back(temp);
		}
		v_.push_back(row);
	}
}

Image::Image(Image& new_img){
	//This function is a constructor which construct a new Image using
	//exist Image.
	height_ = new_img.height_;
	width_ = new_img.width_;
	max_val_ = new_img.max_val_;
	v_ = new_img.v_;
}

void Image::write_image(string f_name){
	//This function write the Image instance into the pgm file. This
	//function requires a string work as the name of output file.
	ofstream outfile(f_name);
	outfile << "P2\n" << width_ << " " << height_ 
	<< "\n" << max_val_ << endl;
	
	for(long y = 0; y < height_; y++){
		for(long x = 0; x < width_; x++){
			//double for loop output each value in the table as a table.
			outfile << setw(3) << v_[y][x] << " ";
		}
		outfile << endl;
	}
}

void Image::convolve(Image& i, vector<vector<long>> mask, long w,
long h, long div, long whiten){
	//This function will do the convolve calculation for current Image.
	//Input: Image which will be modified and work as result image.
	//vector<vector<long>> work as mask of the calculation.
	//long w, h are size of mask. 
	//long div is the divisior for each value of result image.
	//long whiten is the number to add to each value of result image.
	//This function will not return anything, the input Image will work
	//as output.
	
	//initialize the value of Image i with corresponding value of this
	//Image.
	i.height_ = height_; i.width_ = width_; i.max_val_ = max_val_;
	i.v_.clear();
	
	for(long y = 0; y < height_; y++){
		vector<long> row;	//initialize the row vector for a new row.
		for(long x = 0; x < width_; x++){
			//double loop will go through each number of the Image to
			//calculate.
			long start_x = x - w/2, start_y = y - h/2;
			//calculate the upper-left point of matrix calculation.
			long temp=0;
			for(long i = start_y; i < start_y + h; i++){
				for(long j = start_x; j < start_x + w; j++){
					//double loop will do the matrix calculation of the
					//point x, y.
					if(i >= 0 && j >= 0 && i < height_ && j < width_){
						//if the point of small matrix is out of the
						//range of big matrix, ignore it(same as add 0).
						temp += v_[i][j] * mask[i-start_y][j-start_x];
					}
				}
			}
			//division and addition calculation.
			temp /= div;
			temp += whiten;
			//if the max value if out of range, reset it.
			if(temp > max_val_) temp = max_val_;
			if(temp < 0) temp = 0;
			
			row.push_back(temp);	//push_back result number into row.
		}
		i.v_.push_back(row);
		//when the calculation of a row finished, push_back the row in
		//vector to make table.
	}
}

Image Image::sharpen(){
	//do convolve calculation to sharpen image. This will return the new
	//Image.
	Image result;
	vector<vector<long>> mask = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
	(*this).convolve(result, mask, 3, 3);			//do calculation.
	return result;
}

Image Image::edge_detect(){
	//do convolve calculation to edge_detect image. This will return the
	//new Image.
	Image result;
	vector<vector<long>> mask = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
	(*this).convolve(result, mask, 3, 3, 1, 50);	//do calculation.
	return result;
}

Image Image::blur(){
	//do convolve calculation to blur image. This will return the new
	//Image.
	Image result;
	vector<vector<long>> mask = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	(*this).convolve(result, mask, 3, 3, 9);		//do calculation.
	return result;
}

Image Image::emboss(){
	//do convolve calculation to emboss image. This will return the new
	//Image.
	Image result;
	vector<vector<long>> mask = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};
	(*this).convolve(result, mask, 3, 3);			//do calculation.
	return result;
}
