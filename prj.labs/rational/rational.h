#ifndef RATIONAL_H
#define RATIONAL_H

#include <cstdint>
#include <iostream>

class Rational {
public:
	Rational() {};
	explicit Rational(const int32_t numerator);
	Rational(const int32_t numerator, const int32_t denominator);
	Rational& operator=(const Rational& obj);
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const { return !operator==(rhs); }
	Rational& operator+=(const Rational& rhs);
	Rational& operator+=(const int32_t rhs) { return operator+=(Rational(rhs)); }
	Rational& operator-=(const Rational& rhs);
	Rational& operator-=(const int32_t rhs) { return operator-=(Rational(rhs)); }
	Rational& operator*=(const Rational& rhs);
	Rational& operator*=(const int32_t rhs) { return operator*=(Rational(rhs)); }
	Rational& operator/=(const Rational& rhs);
	Rational& operator/=(const int32_t rhs) { return operator/=(Rational(rhs)); }
	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);
	int32_t nod(int32_t num1, int32_t num2);
	int32_t nok(int32_t num1, int32_t num2);
	void tryReduce();

private:
	int32_t num_{ 0 };
	int32_t denom_{ 1 };

	static const char leftBrace_{ '(' };
	static const char separator_{ '/' };
	static const char rightBrace_{ ')' };
};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.readFrom(istrm);
}

#endif