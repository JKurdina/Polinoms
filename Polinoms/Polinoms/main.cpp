#include <iostream>
#include "Monoms.h"
#include "Polinoms.h"
#include <sstream>

int main() {
  string monom = "x^-2y^-5z^-19";
  Monom m;
  istringstream m_in(monom);
  m_in >> m;
  cout << "Monom: ";
  cout << m << endl;
  
  string polinom = "x^(-2)y^0z^0-5x^(-6)y^2z^(-11)+3x^2y^4z^0";
  Polinom p;
  istringstream p_in(polinom);
  p_in >> p;
  cout << "Polinom: ";
  cout << p << endl;


  int x = 3;
  int y = 5;
  int z = 2;
  cout << "Calculate in point (" << x << ", " << y << ", " << z << "): ";
  cout << p.calculate(x, y, z) << endl;

  string polinom1 = "12.5x^(-2)y^0z^0";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;
  cout << "Polinom1: ";
  cout << p1 << endl;

  string polinom2 = "";
  Polinom p2;
  istringstream p_in2(polinom2);
  p2 = p + p1;
  p_in2 >> p2;
  cout << "Polinom2: ";
  cout << p2 << endl;




  return 0;
}