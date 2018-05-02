#include "HugeInteger.h"

HugeInteger::HugeInteger() {
	signal = true;
}

HugeInteger::HugeInteger(string num) {
	int num_size = num.size();
	for (int i = num_size - 1; i > 0; i--) {
		digital.push_back(int(num[i] - '0'));
	}
	if (num[0] == '-') {
		signal = false;
	}
	else if (num[0] == '+') {
		signal = true;
	}
	else {
		signal = true;
		digital.push_back(int(num[0] - '0'));
	}
	deleteZero();
}

HugeInteger::HugeInteger(int num) {
	if (num < 0) {
		num = 0 - num;
		signal = false;
	}
	else {
		signal = true;
	}
	while (num != 0) {
		digital.push_back(num % 10);
		num /= 10;
	}
}

void HugeInteger::deleteZero() {
	int v_size = digital.size();
	for (int i = v_size - 1; i >= 0; i--) {
		if (digital[i] == 0) {
			digital.pop_back();
		}
		else {
			break;
		}
	}
}

HugeInteger HugeInteger::unsign_add(HugeInteger num) {
	HugeInteger result;
	vector<int>::iterator it1 = digital.begin();
	vector<int>::iterator it2 = num.digital.begin();
	int carry = 0;
	while (it1 != digital.end() || it2 != num.digital.end()) {
		int d1 = it1 != digital.end() ? *(it1++) : 0;
		int d2 = it2 != num.digital.end() ? *(it2++) : 0;
		int r = d1 + d2 + carry;
		carry = r / 10;
		result.digital.push_back(r % 10);
	}
	if (carry != 0) {
		result.digital.push_back(carry);
	}
	return result;
}

HugeInteger HugeInteger::unsign_subtract(HugeInteger num) {
	HugeInteger result;
	vector<int>::iterator it1 = digital.begin();
	vector<int>::iterator it2 = num.digital.begin();
	auto end = digital.end();
	if (!this->unsign_greater(num)) {
		it1 = num.digital.begin();
		it2 = digital.begin();
		end = num.digital.end();
		result.signal = false;
	}
	int borrow = 0;
	while (it1 != end) {
		int d1 = *(it1++);
		int d2 = it2 != num.digital.end() ? *(it2++) : 0;
		d1 += borrow;
		int r;
		if (d1 < d2) {
			r = d1 - d2 + 10;
			borrow = -1;
		}
		else {
			r = d1 - d2;
		}
		result.digital.push_back(r);
	}
	return result;
}

bool HugeInteger::unsign_greater(HugeInteger num) {
	if (digital.size() == num.digital.size()) {
		vector<int>::reverse_iterator it1 = digital.rbegin();
		vector<int>::reverse_iterator it2 = num.digital.rbegin();
		while (it1 != digital.rend()) {
			if (*it1 != *it2) {
				return *it1 > *it2;
			}
			it1++;
			it2++;
		}
		return false;
	}
	else {
		return digital.size() > num.digital.size();
	}
}

HugeInteger HugeInteger::opposite() {
	signal = !signal;
	return *this;
}

HugeInteger operator +(HugeInteger &num1, HugeInteger &num2) {
	HugeInteger unsign_result;
	if (num1.signal == num2.signal) {
		unsign_result = num1.unsign_add(num2);
	}
	else {
		unsign_result = num1.unsign_subtract(num2);
	}
	return num1.signal ? unsign_result : unsign_result.opposite();
}

HugeInteger operator -(HugeInteger &num1, HugeInteger &num2) {
	HugeInteger unsign_result;
	if (num1.signal == num2.signal) {
		unsign_result = num1.unsign_subtract(num2);
	}
	else {
		unsign_result = num1.unsign_add(num2);
	}
	return num1.signal ? unsign_result : unsign_result.opposite();
}

bool operator ==(HugeInteger &num1, HugeInteger &num2) {
	if (num1.signal == num2.signal && num1.digital.size() == num2.digital.size()) {
		vector<int>::iterator it1 = num1.digital.begin();
		vector<int>::iterator it2 = num1.digital.begin();
		while (it1 != num1.digital.end()) {
			if (*it1 != *it2) {
				return false;
			}
			it1++;
			it2++;
		}
		return true;
	}
	return false;
}

bool operator !=(HugeInteger &num1, HugeInteger &num2) {
	return !(num1 == num2);
}

bool operator >(HugeInteger &num1, HugeInteger &num2) {
	if (num1.signal == num2.signal) {
		bool unsign_result = num1.unsign_greater(num2);
		return num1.signal ? unsign_result : !unsign_result;
	}
	return num1.signal;
}

bool operator <(HugeInteger &num1, HugeInteger &num2) {
	return !(num1 >= num2);
}

bool operator >=(HugeInteger &num1, HugeInteger &num2) {
	return num1 == num2 || num1 > num2;
}

bool operator <=(HugeInteger &num1, HugeInteger &num2) {
	return num1 == num2 || num1 < num2;
}

ostream &operator<<(ostream & os, HugeInteger num)
{
	if (!num.signal) {
		os << '-';
	}
	vector<int>::reverse_iterator it = num.digital.rbegin();
	while (it != num.digital.rend()) {
		os << *it;
		it++;
	}
	return os;
}

HugeInteger::operator int() {
	int result = 0;
	vector<int>::reverse_iterator it = digital.rbegin();
	while (it != digital.rend()) {
		result *= 10;
		result += *it;
		it++;
	}
	if (!signal) {
		result = 0 - result;
	}
	return result;
}

bool HugeInteger::isEqualTo(HugeInteger &num) {
	return *this == num;
}

bool HugeInteger::isNotEqualTo(HugeInteger &num) {
	return *this != num;
}

bool HugeInteger::isGreaterThan(HugeInteger &num) {
	return *this > num;
}

bool HugeInteger::isLessTo(HugeInteger &num) {
	return *this < num;
}

bool HugeInteger::isGreaterThanOrEqualTo(HugeInteger &num) {
	return *this >= num;
}

bool HugeInteger::isLessThanOrEqualTo(HugeInteger &num) {
	return *this <= num;
}

bool HugeInteger::isZero() {
	return digital.empty();
}
