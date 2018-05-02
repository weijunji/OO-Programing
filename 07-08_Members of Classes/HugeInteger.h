#ifndef HUGE_INTEGER_H
#define HUGE_INTEGER_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class HugeInteger {
private:
	vector<int> digital;  // store the digital from low
	bool signal;  // true: +, false: -
	void deleteZero();  // delete no used zero from high 
	HugeInteger unsign_add(HugeInteger num);
	HugeInteger unsign_subtract(HugeInteger num);
	bool unsign_greater(HugeInteger num);

public:
	HugeInteger();
	HugeInteger(string num);
	HugeInteger(int num);
	HugeInteger opposite();
	friend HugeInteger operator +(HugeInteger &num1, HugeInteger &num2);
	friend HugeInteger operator -(HugeInteger &num1, HugeInteger &num2);
	friend bool operator ==(HugeInteger &num1, HugeInteger &num2);
	friend bool operator !=(HugeInteger &num1, HugeInteger &num2);
	friend bool operator >(HugeInteger &num1, HugeInteger &num2);
	friend bool operator <(HugeInteger &num1, HugeInteger &num2);
	friend bool operator >=(HugeInteger &num1, HugeInteger &num2);
	friend bool operator <=(HugeInteger &num1, HugeInteger &num2);
	operator int();
	friend ostream &operator <<(ostream &os, HugeInteger num);
	bool isEqualTo(HugeInteger &num);
	bool isNotEqualTo(HugeInteger &num);
	bool isGreaterThan(HugeInteger &num);
	bool isLessTo(HugeInteger &num);
	bool isGreaterThanOrEqualTo(HugeInteger &num);
	bool isLessThanOrEqualTo(HugeInteger &num);
	bool isZero();
};
#endif
