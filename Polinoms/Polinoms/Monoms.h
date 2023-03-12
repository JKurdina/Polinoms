#pragma once
#include<iostream>
#include <string>


using namespace std;

const int p = 20;
struct Monom {
  int s;
  int s_minus;
  double coef;
  Monom(double coef = 1.0, int x = 0, int y = 0, int z = 0) {
    this->coef = coef;
    s = x + y * p + z * p * p;
    s_minus = x + y * p + z * p * p;
  }

  int getX() {return s % p + s_minus % p * (-1);}
  int getY() {return (s / p) % p + (s_minus / p) % p * (-1);}
  int getZ() {return (s / p / p) + (s_minus / p / p) * (-1);}

  friend istream& operator>>(istream& in, Monom& m);
  friend ostream& operator<<(ostream& out, Monom& m);
};

