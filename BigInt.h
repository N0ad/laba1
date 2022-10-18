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

	BigInt& operator+=(const BigInt& b) {
		std::string c = "";
		std::string st = b.data;
		int nxt = 0;
		int d, sum;
		BigInt res;
		if (b.min == min) {
			if (data.length() > st.length()) {
				for (int i = 0; i <= data.length() - st.length(); i++) {
					st = "0" + st;
				}
				data = "0" + data;
			}
			for (int i = 0; i < data.length(); i++) {
				sum = data[data.length() - i - 1] - '0';
				d = st[data.length() - i - 1] - '0';
				sum = sum + d + nxt;
				nxt = sum / 10;
				sum = sum % 10;
				c = lib[sum] + c;
			}
			while (1) {
				if ((c[0] == '0') && (c.length() != 1) {
					c.erase(0, 1);
				}
				else {
					break;
				}
			}
			res.data = c;
			res.min = min;
		}
		if (res.data == 0) {
			res.min = 0;
		}
		return res;
	};
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt& b) const {
		if ((b.data == data) && (b.min == min)) {
			return true;
		}
		else {
			return false;
		}
	};
	bool operator!=(const BigInt& b) const {
		if ((data != b.data) || (min != b.min)) {
			return true;
		}
		else {
			return false;
		}
	};
	bool operator<(const BigInt& b) const {
		if (min == b.min) {
			if (min == 1) {
				if (data.length() == b.data.length()) {
					if (data > b.data) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					if (data.length() > b.data.length()) {
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				if (data.length() == b.data.length()) {
					if (data < b.data) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					if (data.length()< b.data.length()) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		else {
			if (min == 1) {
				return true;
			}
			else {
				return false;
			}
		}
	};
	bool operator>(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if ((a == b) || (a < b)) {
			return false;
		}
		else {
			return true;
		}
	};
	bool operator<=(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if (a > b) {
			return false;
		}
		else {
			return true;
		}
	};
	bool operator>=(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if (a < b) {
			return false;
		}
		else {
			return true;
		}
	};

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


