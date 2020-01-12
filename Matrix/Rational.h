#ifndef Rational_h
#define Rational_h

#include <stdio.h>
#include <iostream>

class Rational {
    int numerator, denominator;
    long long gcd(long long a, long long b) {
        while (a != b) {
            if (a > b) {
                a -= b;
            }
            else {
                b -= a;
            }
        }
        return a;
    }
public:
    Rational();
    Rational(int number);
    Rational(int numerator, int denominator);
    Rational(const Rational& other);
    
    int getNumerator() const;
    int getDenominator() const;
    int sign() const;
    
    Rational& operator=(const Rational& other);
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);
    Rational& pow(unsigned power);
    
    
    
    //Vetal Added functions
	double abs();
    
private:
};

Rational operator+(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);

bool operator==(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);
bool operator<=(const Rational& a, const Rational& b);
bool operator> (const Rational& a, const Rational& b);
bool operator>=(const Rational& a, const Rational& b);
int binpow(int a, int n);

//Vetal Added functions
Rational operator-(const Rational &a);

std::ostream& operator<<(std::ostream& stream, const Rational& num);


#endif /* Rational_h */
