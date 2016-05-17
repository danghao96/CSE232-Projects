#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<fstream>
using std::ifstream;

#include "class-07.h"
#include "wavefile.h"

int main (){
  Melody m("mary_had_a_little_lamb.txt", "my_wave.wav", 2000);
  m.fill_Note_vector();
  m.generate_wave_data();
  write_wav_data(m.ofs_, m.w_, m.samples_per_sec_, 1);
}
