// FunctionFromTable class to create a function from a table of (x,y) values.
// Glen Cowan
// RHUL Physics
// November 2014

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "FunctionFromTable.h"

using namespace std;

FunctionFromTable::FunctionFromTable(string inputFileName, double scale){

  ifstream f;
  f.open( inputFileName.c_str() );
  if ( f.fail() ){
    cout << "Sorry, couldn't open input file" << endl;
    exit(1);
  }

  istringstream instream;       // Declare an input string stream
  string line;
  int lineNum = 0;
  while ( getline(f, line) ) {
    bool useLine = !( line.substr(0,1) == "#" || line.substr(0,1) == "!");
    if ( useLine ) {
      instream.clear();          // Reset from possible previous errors
      instream.str(line);        // Use line as source of input
      double x, y;
      lineNum++;
      instream >> x >> y;
      //cout << "initial y:  " << y << endl;
      y /= scale;
      //cout << "scaled y:  " << y << endl;
      m_x.push_back(x);
      m_y.push_back(y);
    }
  }

  f.close();

}

double FunctionFromTable::val(double x){

  // find pair of points between which x lies

  int length = this->len();
  double xMin = this->x(0);
  double xMax = this->x(length-1);

  double f = 0.;
  if (x <= xMin || x >= xMax) {
    f = 0.;
  }
  else {
    bool foundIt = false;
    int i = 0;
    while ( !foundIt && i < length-1 ) {
      if ( x >= this->x(i) && x < this->x(i+1) ) {
        foundIt = true;
	double slope = (this->y(i+1) - this->y(i)) / 
                       (this->x(i+1) - this->x(i));
        f = slope*(x - this->x(i)) + this->y(i);
      }
      i++;
    }
  }

  return f;

}

double FunctionFromTable::maxVal() {
  double fmax = this->y(0);
  for (int i=1; i<this->len(); i++){
    if ( this->y(i) > fmax ) {
      fmax = this->y(i);
    }
  }
  return fmax;
}
