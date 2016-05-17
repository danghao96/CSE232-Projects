#ifndef WAVEFILE
#define WAVEFILE

#include <string>
using std::string;
#include<vector>
using std::vector;
#include<fstream>
using std::ofstream;

void write_wav_data(
    ofstream& s,
    vector<short> &buf,
    int sample_rate,
    short channels);

#endif
