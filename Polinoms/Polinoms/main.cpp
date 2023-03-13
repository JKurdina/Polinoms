#include <iostream>
#include "Monoms.h"
#include "Polinoms.h"
#include <sstream>
#include <fstream>

int main() {
  string monom = "x^-2y^-5z^-19";
  Monom m;
  istringstream m_in(monom);
  m_in >> m;
  cout << "Monom: ";
  cout << m << endl;
  
  string polinom = "x^(-2)y^0z^0-5x^(-6)y^2z^(-11)";
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

  string polinom1 = "5x^(-2)y^0z^0+x^2y^2z^2";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;
  cout << "Polinom1: ";
  cout << p1 << endl;

  string polinom2 = "";
  Polinom p2;
  istringstream p_in2(polinom2);
  p2 = p * p1;
  //p_in2 >> p2; //??? после выполнения операции присваивания, вызывается деструктор, который все удаляет
  cout << "Polinom2: ";
  cout << p2 << endl;

  Polinom p3;
  ifstream file_1("Polinom.txt");
  file_1 >> p3;
  cout << "Polinom from file: ";
  cout << p3 << endl;

  Polinom p4;
  p4 = p + p3;
  ofstream file_2("New_Polinom.txt");
  file_2 << p4;
  file_2.close();



  return 0;
}