#include<iostream>
using std::cout; using std::endl;
#include "class-08.h"

int main (){
  Image test("test.pgm");
  Image image_test;

  image_test = test.sharpen();
  image_test.write_image("temp.pgm");

  Image columns("columns.ascii.pgm");
  image_test = columns.sharpen();
  image_test.write_image("columns_sharp.pgm");
  image_test = columns.edge_detect();
  image_test.write_image("columns_edge_detect.pgm");
  image_test = columns.blur();
  image_test.write_image("columns_blurry.pgm");
  image_test = columns.emboss();
  image_test.write_image("columns_embossed.pgm");  
  
}
