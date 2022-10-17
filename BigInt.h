#include <string>
#include <vector>
#include <utility>
#include <iostream>
#pragma once
class BigInt {
private:
	char lib[11] = "0123456789";
public:
	BigInt() = default;
	BigInt(int inp) {
		data = "";
		int a = inp;
		if (inp < 0) {
			min = 1;
		}
		else {
			min = 0;
		}
		while (1) {
			data = data + lib[a % 10];
			if ((a < 10) && (a > -9)) {
				break;
			}
			a = a / 10;
		}
	};
	BigInt(std::string inp) {
		int a;
		for (int i = 0; i < inp.length(); i++) {
			a = 0;
			for (int j = 0; j < 10; j++) {
				if (inp[i] == lib[j]) {
					a = 1;
					break;
				}
			}
			if (a == 0) {
				throw std::invalid_argument("Input data isn't integer!");
			}
		}
	}; // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt& inp) {
		min = inp.min;
		data = "" + inp.data;
	};
	~BigInt();

	std::string data;
	int min;

	BigInt& operator=(const BigInt& a) {
		min = a.min;
		data = "" + a.data;
	};  //возможно присваивание самому себе!

	BigInt operator~() const;

	BigInt& operator++(); //a++ 
	const BigInt operator++(int) const; //++a
	BigInt& operator--();
	const BigInt operator--(int) const;

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes	
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);


