#include "Monoms.h"

istream& operator>>(istream& in, Monom& m)
{
  string str;
  in >> str;
  m.coef = 1.0;
  m.s = 0;
  
  int st = 0;
  int p_st = 0;
  bool ch = false;
  string t = "";

  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '^') {
      t = "";
      continue;
    }
    if (str[i] == 'x') {
      ch = true;
      p_st = st;
      st = 1;
    }
    if (str[i] == 'y') {
      ch = true;
      p_st = st;
      st = 2;
    }
    if (str[i] == 'z') {
      ch = true;
      p_st = st;
      st = 3;
    }
    if (!ch) {
      t += str[i];
    }
    else {
      if (p_st == 0) {
        if (t.size() > 0) {
          m.coef = stof(t);
        }
      }
      if (p_st > 0) {
        int pp = pow(p, p_st - 1);
        int t_int = stoi(t);
        if (t_int < 0) m.s_minus += t_int * pp *(-1);
        else 
          m.s += t_int * pp;
        i++;
      }
      t = "";
      ch = false;
    }
  }
  
  
  if (t.size() > 0) {
    if (st == 0) {
      m.coef = stof(t);
    }
    if (st > 0) {
      int pp = pow(p, st - 1);
      int t_int = stoi(t);
      if (t_int < 0) m.s_minus += t_int * pp * (-1);
      else
        m.s += t_int * pp;
    }
  }
  return in;
}

ostream& operator<<(ostream& out, Monom& m) {
  int t;
  if (m.coef > 0.0) out << "+";
  out << m.coef;
  t = m.getX(); if (t != 0) out << "x^" << m.getX();
  t = m.getY(); if (t != 0) out << "y^" << m.getY();
  t = m.getZ(); if (t != 0) out << "z^" << m.getZ();
  return out;
}
