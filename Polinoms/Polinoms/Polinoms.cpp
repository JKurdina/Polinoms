#include "Polinoms.h"
#include <cstdlib>
#include <sstream>

Polinom::Polinom() {
  start = new Link(0);
  end = start;
  start->next = start;
}

Polinom::Polinom(const Polinom& p) {
  start = new Link(0);
  end = start;
  start->next = start;

  Link* tmp = p.start->next;
  while (tmp != p.start) {
    addLast(tmp->monom);
    tmp = tmp->next;
  }
}

Polinom:: ~Polinom() {
  while (start != end) {
    Link* new_start = start->next;
    end->next = new_start;
    delete start;
    start = new_start;
  }
  delete start;
}

Polinom& Polinom:: operator=(const Polinom& p) {
  if (start->next != start) {
    while (start != end) {
      Link* new_start = start->next;
      end->next = new_start;
      delete start;
      start = new_start;
    }
    delete start;
  }

  start = new Link(0);
  end = start;
  start->next = end;
  end->next = start;
  Link* tmp = p.start->next;
  while (tmp != p.start) {
    addLast(tmp->monom);
    tmp = tmp->next;
  }
  return *this;
}

void Polinom::addLast(Monom monom) {
  Link* tmp = new Link(monom, start);
  end->next = tmp;
  end = end->next;
  end->next = start;
}

void Polinom::add(Monom monom) {
  Link* tmp = start;
  while (tmp->next != start) {
    if (tmp->next->monom.s > monom.s) {
      Link* b = new Link(monom, tmp->next);
      tmp->next = b;
      return;
    }
    tmp = tmp->next;
  }

  Link* c = new Link(monom, start);
  tmp->next = c;
  end = c;
}

void Polinom:: clean() {
  Link* tmp;// = start;
  while (start->next != start) {
    tmp = start->next;
    start->next = tmp->next;
    delete tmp;
  }
}

double Polinom:: calculate(int x, int y, int z) {
  Link* tmp = start->next;
  double result = 0;
  while (tmp != start) {
    Monom monom = tmp->monom;
    double res = monom.coef;

    res *= pow(x, monom.getX());
    res *= pow(y, monom.getY());
    res *= pow(z, monom.getZ());

    result += res;
    tmp = tmp->next;
  }

  return result;
}

ostream& operator<<(ostream& out, Polinom& p) {
  Link* tmp = p.start->next;
  while (tmp != p.start) {
    out << tmp->monom << " ";
    tmp = tmp->next;
  }

  out << "$";
  return out;
}

istream& operator>>(istream& in, Polinom& p) {
  string str;
  in >> str;
  string t;
  p.clean();
  str += " ";
  bool flag = true;
  for (char c : str) {
    if (((c == ' ') || (c == '+') || (c == '-')) && flag) {
      if (t.size() > 0) {
        istringstream ss(t);
        Monom m;
        ss >> m;
        p.add(m);
      }
      t = "";
      if (c == '-') {
        t += "-";
      }
      if (c == ' ') {
        t += " - ";
      }
    }
    else if (c == '(') {
      flag = false;
    }
    else if (c == ')') {
      flag = true;
    }
    else {
      t += c;
    }
  }
  return in;
}

Polinom Polinom::operator+(const Polinom& p) {
  Polinom resultPolinom;
  Link* p_left = start->next;
  Link* p_right = p.start->next;

  while ((p_left != start) || (p_right != p.start)) {
    int new_s_left = p_left->monom.s - p_left->monom.s_minus;
    int new_s_right = p_right->monom.s - p_right->monom.s_minus;

    if (new_s_left > new_s_right) {
      resultPolinom.addLast(p_right->monom);
      p_right = p_right->next;
    }
    if (new_s_left < new_s_right) {
      resultPolinom.addLast(p_left->monom);
      p_left = p_left->next;
    }
    else {
      double new_coef = p_left->monom.coef + p_right->monom.coef;
      Monom new_monom(new_coef, p_left->monom.getX(), p_left->monom.getX(), p_left->monom.getX());
      resultPolinom.addLast(new_monom);
      p_right = p_right->next;
      p_left = p_left->next;
    }
  }

  return resultPolinom;
}