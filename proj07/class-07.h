#ifndef WAVE_CLASS
#define WAVE_CLASS

#include<vector>
using std::vector;
#include<string>
using std::string;
#include<fstream>
using std::ifstream; using std::ofstream;

struct Note {
  double freq_;
  double dur_;

  Note() : freq_(0) , dur_(0) {};
  Note(double f, double d) : freq_(f), dur_(d) {};
};

struct Melody {
  vector<Note> v_;              // vector of Notes from the input file
  vector<short> w_;             // vector of samples to turn into wav file
  ofstream ofs_;                // a binary output file, the wav file
  ifstream ifs_;                // a text input file, the Notes file
  long one_beat_;             // how many samples per one beat (a quarter note).
  long samples_per_sec_;        // from the Notes file
  long volume_;                 // from the Notes file

  Melody(string notes_file_name,
	 string wav_file_name,
	 long a_beat); // samples in a quarter note (typically 1/4 of sample rate)
  void fill_Note_vector();
  void generate_wave_data();
};





#endif
