#include <iostream>
#include "FunctionFromTable.h"

using namespace std;

int main(){

  double scale = 1.e12;     // scale factor
  FunctionFromTable edist("energy_spectrum.txt", scale);

  while ( true ){
    double x;
    cout << "enter x:  ";
    cin >> x;
    double y = edist.val(x);
    cout << "y = " << y << endl;
  }

  return 0;

}
