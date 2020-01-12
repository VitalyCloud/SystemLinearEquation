#include "Rational.h"
#include <iostream>

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int number)
{
	numerator = number;
	denominator = 1;
}

Rational::Rational(int num, int denum)
{
	if (denum == 0) {
		denominator = 1;
		numerator = 0;
		std::cout << "CARE! DENUM = 0" << std::endl;
	}
	else if (num == 0) {
		numerator = 0;
		denominator = 1;
	}
	else {
		int sign = 1;
		if (num < 0) {
			sign *= -1;
			num *= -1;
		}
		if (denum < 0) {
			sign *= -1;
			denum *= -1;
		}
		long long tmp = gcd(num, denum);
		numerator = num / tmp * sign;
		denominator = denum / tmp;
	}
}

Rational::Rational(const Rational& other)
{
	numerator = other.getNumerator();
	if (other.denominator == 1) {
		denominator = 1;
	} 
	else {
		denominator = other.getDenominator();
	}
}

int Rational::getNumerator() const
{
	return numerator;
}

int Rational::getDenominator() const
{
	return denominator;
}

int Rational::sign() const
{
	bool flagNum = numerator > 0 ? true : false;
	bool flagDenum = denominator > 0 ? true : false;
	if (flagNum & flagDenum) {
		return true;
	}
	if (flagNum || flagDenum) {
		return false;
	}
	if (!flagDenum & !flagNum) {
		return true;
	}
    //WARNING
    return false;
}

Rational& Rational::operator=(const Rational& other)
{
	if (this == &other) {
		return *this;
	}
    
	numerator = other.getNumerator();
	denominator = other.getDenominator();
	return *this;
}

Rational& Rational::operator+=(const Rational& other)
{
	Rational tmp(this->getNumerator() * other.getDenominator()
		+ other.getNumerator() * this->getDenominator(),
		this->getDenominator() * other.getDenominator());
	*this = tmp;
	return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
	Rational tmp(this->getNumerator() * other.getDenominator()
		- other.getNumerator() * this->getDenominator(),
		this->getDenominator() * other.getDenominator());
	*this = tmp;
	return *this;
}

Rational& Rational::operator*=(const Rational& other)
{
   
    //bad work
//    numerator *= other.getNumerator();
//    denominator *= other.getDenominator();
//    return *this;
    
    Rational tmp(this->getNumerator()*other.getNumerator(),
                 this->getDenominator()*other.getDenominator());
    *this = tmp;
    return *this;
}

Rational& Rational::operator/=(const Rational& other)
{
	numerator *= other.getDenominator();
	denominator *= other.getNumerator();
	return *this;
}

Rational& Rational::pow(unsigned power)
{
	int verh = binpow(this->getNumerator(), power);
	int niz = binpow(this->getDenominator(), power);
	this->numerator = verh;
	this->denominator = niz;
	return *this;
}

double Rational::abs() {
	double absolute = (double)numerator / (double)denominator;
	if (absolute >= 0)
		return absolute;
	else
		return -absolute;
}



Rational operator+(const Rational& a, const Rational& b)
{
	return Rational(a.getNumerator() * b.getDenominator()
		+ b.getNumerator() * a.getDenominator(),
		a.getDenominator() * b.getDenominator());
}

Rational operator-(const Rational& a, const Rational& b)
{
	return Rational(a.getNumerator() * b.getDenominator()
		- b.getNumerator() * a.getDenominator(),
		a.getDenominator() * b.getDenominator());
}

Rational operator*(const Rational& a, const Rational& b)
{
	return Rational(a.getNumerator() * b.getNumerator(), a.getDenominator() * b.getDenominator());
}

Rational operator/(const Rational& a, const Rational& b)
{
	return Rational(a.getNumerator() * b.getDenominator(), a.getDenominator() * b.getNumerator());
}

bool operator==(const Rational& a, const Rational& b)
{
	return ((a.getNumerator() == b.getNumerator()) && (a.getDenominator() == b.getDenominator()));
}

bool operator!=(const Rational& a, const Rational& b)
{
	return !(a == b);
}

bool operator<(const Rational& a, const Rational& b)
{
	int lside = a.getNumerator() * b.getDenominator();
	int rside = a.getDenominator() * b.getNumerator();
	return (lside < rside);
}

bool operator<=(const Rational& a, const Rational& b)
{
	return (a < b) || (a == b);
}

bool operator>(const Rational& a, const Rational& b)
{
	int lside = a.getNumerator() * b.getDenominator();
	int rside = a.getDenominator() * b.getNumerator();
	return (lside > rside);
}

bool operator>=(const Rational& a, const Rational& b)
{
	return (a > b) || (a == b);
}

int binpow(int a, int n)
{
	int res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
		}
	return res;
}


std::ostream& operator<<(std::ostream& stream, const Rational& num)
{
	if (num.getDenominator() == 1) {
		stream << num.getNumerator();
	}
	else if (num.getNumerator() == 0) {
		stream << num.getNumerator();
	}
	else {
		stream << num.getNumerator() << "/" << num.getDenominator();
	}
	return stream;
}

//Vetal added function
Rational operator-(const Rational &a) {
    int numerator = a.getNumerator();
    int denumerator = a.getDenominator();
    numerator = numerator>=0 ? -numerator : std::abs(numerator);
    return Rational(numerator, denumerator);
}


