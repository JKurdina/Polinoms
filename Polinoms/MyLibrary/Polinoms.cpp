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
    this->addLast(tmp->monom);
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
    int new_s = tmp->next->monom.s - tmp->next->monom.s_minus;
    if (new_s > monom.s - monom.s_minus) {
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

void Polinom::clean() {
  Link* tmp;// = start;
  while (start->next != start) {
    tmp = start->next;
    start->next = tmp->next;
    delete tmp;
  }
}

double Polinom::calculate(int x, int y, int z) {
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

Polinom Polinom::operator+(const Polinom& pl) {
  Polinom resultPolinom;
  Link* p_left = start->next;
  Link* p_right = pl.start->next;
 

  while ((p_left != start) && (p_right != pl.start)) {
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
      if (new_coef == 0) {
        p_right = p_right->next;
        p_left = p_left->next;
        continue;
      }

      Monom new_monom;
      if (p_left->monom.getX() > 0) new_monom.s += p_left->monom.getX();
      else new_monom.s_minus += p_left->monom.getX() * (-1);

      if (p_left->monom.getY() > 0) new_monom.s += p_left->monom.getY() * p;
      else new_monom.s_minus += p_left->monom.getY() * p * (-1);

      if (p_left->monom.getZ() > 0) new_monom.s += p_left->monom.getZ() * p * p;
      else new_monom.s_minus += p_left->monom.getZ() * p * p * (-1);

      new_monom.coef = new_coef;
      resultPolinom.addLast(new_monom);
      p_right = p_right->next;
      p_left = p_left->next;
    }
  }

  if (p_left == start) {
    while (p_right != pl.start) {
      resultPolinom.addLast(p_right->monom);
      p_right = p_right->next;
    }
  }

  if (p_right == pl.start) {
    while (p_left != start) {
      resultPolinom.addLast(p_left->monom);
      p_left = p_left->next;
    }
  }

  return resultPolinom;
}

Polinom Polinom::operator-(const Polinom& pl) {
  Polinom resultPolinom;
  Link* p_left = start->next;
  Link* p_right = pl.start->next;

  while ((p_left != start) && (p_right != pl.start)) {
    int new_s_left = p_left->monom.s - p_left->monom.s_minus;
    int new_s_right = p_right->monom.s - p_right->monom.s_minus;

    if (new_s_left > new_s_right) {
      p_right->monom.coef = p_right->monom.coef * (-1);
      resultPolinom.addLast(p_right->monom);
      p_right = p_right->next;
    }
    if (new_s_left < new_s_right) {
      resultPolinom.addLast(p_left->monom);
      p_left = p_left->next;
    }
    else {
      double new_coef = p_left->monom.coef - p_right->monom.coef;
      if (new_coef == 0) {
        p_right = p_right->next;
        p_left = p_left->next;
        continue;
      }
      Monom new_monom;
      if (p_left->monom.getX() > 0) new_monom.s += p_left->monom.getX();
      else new_monom.s_minus += p_left->monom.getX() * (-1);

      if (p_left->monom.getY() > 0) new_monom.s += p_left->monom.getY() * p;
      else new_monom.s_minus += p_left->monom.getY() * p * (-1);

      if (p_left->monom.getZ() > 0) new_monom.s += p_left->monom.getZ() * p * p;
      else new_monom.s_minus += p_left->monom.getZ() * p * p * (-1);

      new_monom.coef = new_coef;
      resultPolinom.addLast(new_monom);
      p_right = p_right->next;
      p_left = p_left->next;
    }
  }

  if (p_left == start) {
    while (p_right != pl.start) {
      p_right->monom.coef = p_right->monom.coef * (-1);
      resultPolinom.addLast(p_right->monom);
      p_right = p_right->next;
    }
  }

  if (p_right == pl.start) {
    while (p_left != start) {
      resultPolinom.addLast(p_left->monom);
      p_left = p_left->next;
    }
  }

  return resultPolinom;
}

Polinom Polinom::operator*(const Polinom& pl) {
  Polinom resultPolinom;
  Link* p_left = start->next;
  Link* p_right = pl.start->next;

  while (p_left != start) {

    Link* tmp = p_right;
    while (tmp != pl.start) {
      double new_coef = p_left->monom.coef * tmp->monom.coef;
      int new_x = p_left->monom.getX() + tmp->monom.getX();
      int new_y = p_left->monom.getY() + tmp->monom.getY();
      int new_z = p_left->monom.getZ() + tmp->monom.getZ();

      Monom new_monom;
      if (new_x > 0) new_monom.s += new_x;
      else new_monom.s_minus += new_x * (-1);

      if (new_y > 0) new_monom.s += new_y * p;
      else new_monom.s_minus += new_y * p * (-1);

      if (new_z > 0) new_monom.s += new_z * p * p;
      else new_monom.s_minus += new_z * p * p * (-1);

      new_monom.coef = new_coef;
      resultPolinom.add(new_monom);
      tmp = tmp->next;
    }
    p_left = p_left->next;

  }
  Polinom resultPolinom2;
  Link* tmp2 = resultPolinom.start->next;
  
  while (tmp2 != resultPolinom.start) {
    double new_coef = tmp2->monom.coef;
    Monom new_monom;
    new_monom.s = tmp2->monom.s;
    new_monom.s_minus = tmp2->monom.s_minus;
    

 
    while (tmp2->monom.s + tmp2->monom.s_minus == tmp2->next->monom.s + tmp2->next->monom.s_minus) {
      new_coef += tmp2->next->monom.coef;
      tmp2 = tmp2->next;

    }
    tmp2 = tmp2->next;
    if (new_coef == 0.0) continue;
    new_monom.coef = new_coef;
    resultPolinom2.add(new_monom);
  }
  return resultPolinom2;
}

bool Polinom::operator==(const Polinom& p) {
  Link* tmp_right = p.start->next;
  Link* tmp_left = start->next;


  while (tmp_right != start && tmp_left != start) {
    if (tmp_left->monom.coef == tmp_right->monom.coef &&
      tmp_left->monom.getX() == tmp_right->monom.getX() &&
      tmp_left->monom.getY() == tmp_right->monom.getY() &&
      tmp_left->monom.getZ() == tmp_right->monom.getZ()) {
      tmp_left = tmp_left->next;
      tmp_right = tmp_right->next;
    }
    else return false;
  }


if (tmp_right == p.start && tmp_left != start)
return false;
else if (tmp_right != p.start && tmp_left == start)
return false;
return true;
}

bool Polinom::operator!=(const Polinom& p) {
  Link* tmp_right = p.start->next;
  Link* tmp_left = start->next;


  while (tmp_right != start && tmp_left != start) {
    if (tmp_left->monom.coef == tmp_right->monom.coef &&
      tmp_left->monom.getX() == tmp_right->monom.getX() &&
      tmp_left->monom.getY() == tmp_right->monom.getY() &&
      tmp_left->monom.getZ() == tmp_right->monom.getZ()) {
      tmp_left = tmp_left->next;
      tmp_right = tmp_right->next;
    }
    else return true;
  }


  if (tmp_right == p.start && tmp_left != start)
    return true;
  else if (tmp_right != p.start && tmp_left == start)
    return true;
  return false;
}

