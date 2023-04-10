#include <iostream>
#include "Monoms.h"
#include "Polinoms.h"
#include <sstream>
#include <fstream>

int main() {
  /*string monom = "x^-2y^-5z^-19";
  Monom m;
  istringstream m_in(monom);
  m_in >> m;*/
  /*cout << "Monom: ";
  cout << m << endl;*/

  


  string polinom1 = "x^2y^3z^4+2x^5y^1z^1";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;
  cout << "Polinom1: ";
  cout << p1 << endl;


  /*string polinom2 = "";
  Polinom p2;
  istringstream p_in2(polinom2);
  p2 = p * p1;*/
  //p_in2 >> p2; //??? после выполнения операции присваивания, вызывается деструктор, который все удаляет
  /*cout << "Polinom2: ";
  cout << p2 << endl;*/

  Polinom p2;
  ifstream file_1("Polinom.txt");
  file_1 >> p2;
  cout << "Polinom from file: ";
  cout << p2 << endl;

 Polinom p4;
  p4 = p1 - p2;
  ofstream file_2("New_Polinom1.txt");
  file_2 << p4;
  file_2.close();
  cout << "Polinom 2: ";
  cout << p4 << endl;

  /*Polinom p1;
  string polinom1 = "";
  istringstream p_in1(polinom1);
  p_in1 >> p1;
  cout << p1 << endl;

  string polinom2 = "x^2y^3z^4+2x^5y^1z^1";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;
  cout << p2;*/
  


  return 0;
}