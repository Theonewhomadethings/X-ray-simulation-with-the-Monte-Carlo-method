//functionfromtable class

#ifndef FUNCTIONFROMTABLE_H
#define FUNCTIONFROMTABLE_H

#include <string>
#include <vector>

using namespace std;

class FunctionFromTable {
  public:
    FunctionFromTable(string file, double s = 1.);
    double  val(double x);
    int     len() { return m_x.size(); }
    double  x(int i) { return m_x[i]; }
    double  y(int i) { return m_y[i]; }
    double  maxVal();
  private:
    vector<double> m_x;
    vector<double> m_y;
};

#endif
