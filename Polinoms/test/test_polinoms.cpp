#include "Polinoms.h"

#include <gtest.h>


//TEST(Monoms, can_create_monom)
//{
//  ASSERT_NO_THROW(Monom m);
//}
//
//TEST(Monoms, can_create_copied_monom) 
//{
//  string monom = "5x^4y^3z^2";
//  Monom m;
//  istringstream m_in(monom);
//  m_in >> m;
//  ASSERT_NO_THROW(Monom m1(m));
//}
//
//TEST(Monoms, copied_monom_is_equal_to_source_one)
//{
//  string monom = "5x^4y^3z^2";
//  Monom m;
//  istringstream m_in(monom);
//  m_in >> m;
//  Monom m1(m);
//  EXPECT_EQ(5, m1.coef);
//  EXPECT_EQ(4, m1.getX());
//  EXPECT_EQ(3, m1.getY());
//  EXPECT_EQ(2, m1.getZ());
//}


TEST(Polinoms, can_create_polinom)
{
  ASSERT_NO_THROW(Polinom p);
}

TEST(Polinoms, can_create_copied_polinom)
{
  string polinom = "x^(-2)y^0z^0-5x^(-6)y^2z^(-11)";
  Polinom p;
  istringstream p_in(polinom);
  p_in >> p;
  ASSERT_NO_THROW(Polinom p1(p));
}

TEST(Polinoms, copied_polinom_is_equal_to_source_one)
{
  string polinom = "x^(-2)y^0z^0-5x^(-6)y^2z^(-11)";
  Polinom p;
  istringstream p_in(polinom);
  p_in >> p;
  Polinom p1(p);
  EXPECT_EQ(true, p == p1);
}

TEST(Polinoms, copied_polinom_has_its_own_memory) 
{
  string polinom = "x^(-2)y^0z^0-5x^(-6)y^2z^(-11)";
  Polinom p;
  istringstream p_in(polinom);
  p_in >> p;
  
  Polinom p1(p);

  string polinom2 = "x^(-2)y^0z^0";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;

  p = p + p2;

  EXPECT_EQ(true, p1 != p);
}

TEST(Polinoms, compare_equal_polinoms_return_true) 
{
  string polinom = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p;
  istringstream p_in(polinom);
  p_in >> p;

  string polinom1 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  EXPECT_EQ(true, p == p1);
}

TEST(Polinoms, can_add_polinoms) 
{
  string polinom1 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  string polinom2 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;

  Polinom p3;
  p3 = p1 + p2;

  string polinom4 = "2x^(-2)y^3z^4-10x^(-6)y^2z^(-11)";
  Polinom p4;
  istringstream p_in4(polinom4);
  p_in4 >> p4;

  EXPECT_EQ(true, p3 == p4);
}

TEST(Polinoms, can_subtract_polinoms)
{
  string polinom1 = "2x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  string polinom2 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;

  Polinom p3;
  p3 = p1 - p2;

  string polinom4 = "x^(-2)y^3z^4";
  Polinom p4;
  istringstream p_in4(polinom4);
  p_in4 >> p4;

  EXPECT_EQ(true, p3 == p4);
}

TEST(Polinoms, can_subtract_equal_polinoms)
{
  string polinom1 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  string polinom2 = "x^(-2)y^3z^4-5x^(-6)y^2z^(-11)";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;

  Polinom p3;
  p3 = p1 - p2;

  string polinom4 = "";
  Polinom p4;
  istringstream p_in4(polinom4);
  p_in4 >> p4;

  EXPECT_EQ(true, p3 == p4);
}

TEST(Polinoms, can_multiply_polinoms)
{
  string polinom1 = "x^2y^3z^4+2x^5y^1z^1";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  string polinom2 = "x^2y^3z^4-2x^5y^1z^1";
  Polinom p2;
  istringstream p_in2(polinom2);
  p_in2 >> p2;

  Polinom p3;
  p3 = p1 * p2;

  string polinom4 = "-4x^10y^2z^2+2x^7y^4z^5-2x^7y^4z^5+x^4y^6z^8";
  Polinom p4;
  istringstream p_in4(polinom4);
  p_in4 >> p4;

  EXPECT_EQ(true, p3 == p4);
}

TEST(Polinoms, can_calculate_value_in_point)
{
  string polinom1 = "x^2y^3z^4+2x^5y^1z^1";
  Polinom p1;
  istringstream p_in1(polinom1);
  p_in1 >> p1;

  int x = 2;
  int y = -3;
  int z = 4;

  double result = p1.calculate(x, y, z);
  EXPECT_EQ(-28416, result);
}


