#include "rational.h"

Rational::Rational(const int32_t numerator)
	: Rational(numerator, 1) {
}

Rational::Rational(const int32_t numerator, const int32_t denominator){
	if (0 == denominator) throw std::invalid_argument("Zero denumenator in Rational");
	num = numerator;
	denom = denominator;
	if (denom < 0) {
		denom *= -1;
		num *= -1;
	}
	tryReduce();
}

Rational& Rational::operator=(const Rational& obj) {
	if (this != &obj) {
		num = obj.num;
		denom = obj.denom;
	}
	return *this;
}

bool Rational::operator==(const Rational& rhs) const {
	return (num == rhs.num)&&(denom == rhs.denom);
}

Rational& Rational::operator+=(const Rational& rhs) {
	num = (rhs.denom * num + denom * rhs.num)/nod(denom, rhs.denom);
	denom = nok(denom, rhs.denom);
	tryReduce();
	return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum += rhs;
	return sum;
}

Rational& Rational::operator-=(const Rational& rhs) {
	num = (rhs.denom * num - denom * rhs.num) / nod(denom, rhs.denom);
	denom = nok(denom, rhs.denom);
	tryReduce();
	return *this;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational dif(lhs);
	dif -= rhs;
	return dif;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	denom *= rhs.denom;
	tryReduce();
	return *this;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational com(lhs);
	com *= rhs;
	return com;
}

Rational& Rational::operator/=(const Rational& rhs) {
	num *= rhs.denom;
	denom *= rhs.num;
	if (denom < 0) {
		denom *= -1;
		num *= -1;
	}
	tryReduce();
	return *this;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational quot(lhs);
	quot /= rhs;
	return quot;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
	ostrm << leftBrace << num << separator << denom << rightBrace;
	return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm) {
	char leftBrace(0);
	int32_t numerator(0);
	char sep(0);
	int32_t denominator(1);
	char rightBrace(0);
	istrm >> leftBrace >> numerator >> sep >> denominator >> rightBrace;
	if (istrm.good()) {
		if ((Rational::leftBrace == leftBrace) && (Rational::separator == sep) &&
			(Rational::rightBrace == rightBrace)) {
			if (0 == denominator) throw std::invalid_argument("Zero denumenator in Rational");
			num = numerator;
			denom = denominator;
			if (denom < 0) {
				denom *= -1;
				num *= -1;
			}
			tryReduce();
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

int32_t Rational::nod(int32_t num1, int32_t num2) {
	if (num2 > num1) {
		int32_t z = num1;
		num1 = num2;
		num2 = z;
	}
	int32_t w(0);
	while (num2 > 0) {
		w = num1 % num2;
		num1 = num2;
		num2 = w;
	}
	return num1;
}

int32_t Rational::nok(int32_t num1, int32_t num2) {
	return num1 * num2 / nod(num1, num2);
}

void Rational::tryReduce() {
	int32_t nod1 = nod(abs(num), denom);
	if (nod1 != 1) {
		num /= nod1;
		denom /= nod1;
	}
}