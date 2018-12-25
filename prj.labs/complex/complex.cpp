#include "complex.h"

Complex::Complex(const double real)
  : Complex(real, 0.0) {
}



Complex::Complex(const double real, const double imaginary)
  : re(real), im(imaginary) {
}



Complex& Complex::operator=(const Complex& obj) {
  if (this != &obj) {
    re = obj.re;
    im = obj.im;
  }
  return *this;
}



Complex& Complex::operator+=(const Complex& rhs) {
  re += rhs.re;
  im += rhs.im;
  return *this;
}



Complex operator+(const Complex& lhs, const Complex& rhs) {
  Complex sum(lhs);
  sum += rhs;
  return sum;
}



Complex& Complex::operator-=(const Complex& rhs) {
  re -= rhs.re;
  im -= rhs.im;
  return *this;
}



Complex operator-(const Complex& lhs, const Complex& rhs) {
  return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}



Complex& Complex::operator*=(const Complex& rhs) {
  double reold = re;
  re = re * rhs.re - im * rhs.im;
  im = reold * rhs.im + im * rhs.re;
  return *this;
}



Complex operator*(const Complex& lhs, const Complex& rhs) {
  Complex com(lhs);
  com *= rhs;
  return com;
}



Complex& Complex::operator/=(const Complex& rhs) {
  *this *= Complex(rhs.re, -rhs.im);
  this->re /= (rhs.re * rhs.re + rhs.im * rhs.im);
  this->im /= (rhs.re * rhs.re + rhs.im * rhs.im);
  return *this;
}



Complex operator/ (const Complex& lhs, const Complex& rhs) {
  Complex quot(lhs);
  quot /= rhs;
  return quot;
}



std::ostream& Complex::writeTo(std::ostream& ostrm) const {
  ostrm << leftBrace << re << separator << im << rightBrace;
  return ostrm;
}



std::istream& Complex::readFrom(std::istream& istrm) {
  char leftBrace(0);
  double real(0.0);
  char comma(0);
  double imaganary(0.0);
  char rightBrace(0);
  istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
  if (istrm.good()) {
    if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) &&
        (Complex::rightBrace == rightBrace)) {
      re = real;
      im = imaganary;
    }
    else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}