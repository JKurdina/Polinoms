#pragma once
#include<iostream>
#include <string>
#include "Monoms.h"

using namespace std;

struct Link {
  Monom monom;
  Link* next;
  Link(Monom _monom, Link* _next = nullptr) : monom(_monom), next(_next) {};
};

class Polinom {
  Link* start;
  Link* end;
public:
  Polinom();
  Polinom(const Polinom& p);
  ~Polinom();
  Polinom& operator=(const Polinom& p);
  Polinom operator+(const Polinom& p);
  Polinom operator-(const Polinom& p);
  Polinom operator*(const Polinom& p);
  bool operator ==(const Polinom& p);
  bool operator !=(const Polinom& p);
  void addLast(Monom monom);
  void add(Monom monom);
  void clean();
  double calculate(int x, int y, int z);
  friend ostream& operator<<(ostream& out, Polinom& p);
  friend istream& operator>>(istream& in, Polinom& p);
};