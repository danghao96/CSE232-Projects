/*
Hao Dang danghao@xserver
2016-03-16
class-07.cpp

*/

#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream; using std::ofstream;
#include <string>
using std::string;
#include <cmath>

#include "class-07.h"

void split(string to_split, vector<double>& digits, string good_chars){
	//This function is directly copyed from last project.
	size_t pos_good = 0, pos_bad = 0;
	while(true){
		string digit_str;
		double digit;
		pos_good = to_split.find_first_of(good_chars, pos_bad);
		pos_bad = to_split.find_first_not_of(good_chars, pos_good+1);
		if(pos_good == string::npos){
			break;
		}
		digit_str = to_split.substr(pos_good, pos_bad - pos_good);
		digit = stod(digit_str);
		digits.push_back(digit);
	}
}

Note make_note(string oct_pch_dur){
	//This function will create a Note and return it.
	//This function requires a string and split the string and make the 
	//note and return it.
	double freq, dur;
	const double x = 440;
	vector<double> opd;
	split(oct_pch_dur, opd, "0123456789");//split the string into vector
	
	//calculate the frequence.
	double o = opd[0]-4;
	double m_12 = (opd[1]-9) / 12;
	freq = x * pow(2, o + m_12);
	
	dur = opd[2];	//get the duration.
	Note result(freq, dur);	//make note.
	return result;
}

Melody::Melody(string notes_file_name, string wav_file_name, long a_beat){
	//This function is a construction of Melody.
	ofs_.open(wav_file_name);
	ifs_.open(notes_file_name);
	one_beat_ = a_beat;
}

void Melody::fill_Note_vector(){
	//This function read the file ifs_ and construct the Melody.
	string sample_rate_str;
	string volume_str;
	string oct_pch_dur;
	//Read the first line of ifs_ and save the value in samples_per_sec_
	getline(ifs_, sample_rate_str);
	samples_per_sec_ = stol(sample_rate_str);
	
	//Read the second line of ifs_ and save the value in volume_.
	getline(ifs_, volume_str);
	volume_ = stol(volume_str);
	
	while(true){
		//while loop read the subsequent lines from ifs_.
		getline(ifs_, oct_pch_dur);
		if(ifs_.eof()) break;//if reach the end of file, break the loo[.
		Note temp = make_note(oct_pch_dur);
		//call function make_note to make the note from the string.
		v_.push_back(temp);//save the note in vector v_.
	}
}

void Melody::generate_wave_data(){
	//This function will generate the wave data.
	for(Note n : v_){
		//for loop read each note from vector v_.
		long sample_count = n.dur_ * one_beat_;
		double one_increment, sample;
		const double TwoPI = 2.0 * (atan(1.0) * 4.0);
		for (int val=0; val<sample_count; val++){
			//for loop generates sample_count samples for each note.
			one_increment = n.freq_ * (1.0 * val / samples_per_sec_);
			sample = sin( one_increment * TwoPI ) * volume_;
			//calculate sample.
			w_.push_back(sample);//save sample in vector w_.
		}
	}
}



