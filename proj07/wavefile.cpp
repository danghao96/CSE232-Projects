#include <fstream>
using std::ofstream;
#include <string>
using std::string;;
#include<vector>
using std::vector;

// wfp, 2/26/16
// Generates wave file, single channel

void write_wav_data(
		    ofstream& out_stream,		    
		    std::vector<short> &buf,
		    int sample_rate,
		    short channels){
  
  // setup all the variables that WAV requires
  int buf_size = buf.size() * sizeof(short);
  int chunk_size = 36 + buf_size;
  int sub_chunk_size = 16;
  short audio_format = 1;
  int byte_rate = sample_rate * channels * sizeof(short);
  short block_align = channels * sizeof(short);
  short bits_per_sample = 8 * sizeof(short);
  
  // write the RIFF part
  out_stream.write("RIFF", 4);
  out_stream.write(reinterpret_cast<const char *>(&chunk_size), 4);
  out_stream.write("WAVE", 4);
  
  // write the format subchunk
  out_stream.write("fmt ", 4);
  out_stream.write(reinterpret_cast<const char *>(&sub_chunk_size), 4);
  out_stream.write(reinterpret_cast<const char *>(&audio_format), 2); 
  out_stream.write(reinterpret_cast<const char *>(&channels), 2);     
  out_stream.write(reinterpret_cast<const char *>(&sample_rate), 4);  
  out_stream.write(reinterpret_cast<const char *>(&byte_rate), 4); 
  out_stream.write(reinterpret_cast<const char *>(&block_align), 2);  // Frame size
  out_stream.write(reinterpret_cast<const char *>(&bits_per_sample), 2);
  
  // write the data chunk
  out_stream.write("data", 4);
  out_stream.write(reinterpret_cast<const char *>(&buf_size), 4);
  out_stream.write(reinterpret_cast<const char *>(buf.data()), buf_size);
}
