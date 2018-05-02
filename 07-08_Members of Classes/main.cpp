#include "HugeInteger.h"
#include <iostream>
#undef NDEBUG 
#include<assert.h>

HugeInteger num1 = HugeInteger("-000001234567890");
HugeInteger num2 = HugeInteger("0000012345678900987654321");
HugeInteger num3 = HugeInteger(1234567890);
HugeInteger num4 = HugeInteger(-12345);

void test_operator_out() {
	cout << "operator << from string:\n" << num1 << '\n' << num2 << endl;
	cout << "operator << from int:\n" << num3 << '\n' << num4 << endl;
}

void test_operator_int() {
	cout << "operator int test:\n" << int(num1) << endl;
	assert(num1 == -1234567890);
}

void test_equalTo() {
	HugeInteger num = HugeInteger(-1234567890);
	assert(!(num1 == num3));
	assert(num1 == num);
	assert(!num1.isEqualTo(num3));
	assert(num1.isEqualTo(num));
}

void test_notEqualTo() {
	assert(num1 != num3);
	assert(num1.isNotEqualTo(num3));
}

void test_add() {
	// call unsign_add
	assert(HugeInteger(999999) + HugeInteger(2) == HugeInteger(1000001));
	assert(HugeInteger(999) + HugeInteger(0) == HugeInteger(999));
	assert(HugeInteger(-999) + HugeInteger(-2) == HugeInteger(-1001));
	// call unsign_subtract
	assert(HugeInteger(1000) + HugeInteger(-1) == HugeInteger(999));
	assert(HugeInteger(-1000) + HugeInteger(1) == HugeInteger(-999));
	assert(HugeInteger(-1000) + HugeInteger(0) == HugeInteger(-1000));
}

void test_subtract() {
	// call unsign_add
	assert(HugeInteger(999) - HugeInteger(-2) == HugeInteger(1001));
	assert(HugeInteger(-999) - HugeInteger(0) == HugeInteger(-999));
	assert(HugeInteger(-999) - HugeInteger(2) == HugeInteger(-1001));
	// call unsign_subtract
	assert(HugeInteger(1) - HugeInteger(999) == HugeInteger(-998));
	assert(HugeInteger(-1000) - HugeInteger(-1) == HugeInteger(-999));
	assert(HugeInteger(0) - HugeInteger(999) == HugeInteger(-999));
}

void test_greater() {
	assert(!(HugeInteger(999) > HugeInteger(999)));
	assert(HugeInteger(999) > HugeInteger(0));
	assert(HugeInteger(-998) > HugeInteger(-999));
}

void test_isZero() {
	HugeInteger zero = HugeInteger("-000");
	assert(zero.isZero());
	assert(!HugeInteger(-1).isZero());
}

void test_others() {
	// all of these are based on == > + -
	// isGreaterThan and so on are based on the operator, so not test them
	assert(HugeInteger(1) < HugeInteger(2));
	assert(HugeInteger(1) <= HugeInteger(2));
	assert(HugeInteger(3) >= HugeInteger(2));
	assert(HugeInteger(1) != HugeInteger(2));
}

int main()
{
	test_operator_out();
	test_operator_int();
	test_equalTo();
	test_notEqualTo();
	test_add();
	test_subtract();
	test_greater();
	test_isZero();
	test_others();
    return 0;
}
